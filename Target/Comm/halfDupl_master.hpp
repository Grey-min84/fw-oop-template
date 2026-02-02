#ifndef __HALF_DUPLEX_MASTER_H__
#define __HALF_DUPLEX_MASTER_H__
#include "portHAL_STM32.h"
#include "drv_rs485.h"


#define NETWORK_ERR_CRC     (0x00000001)
#define NETWORK_ERR_TIMEOUT (0x00000001 << 1)


#define PERMIT_CRC_ERR_CNT      (10)

#define RESTORE_TRY_TIMEOUT_CNT (5)
#define PERMIT_TIMEOUT_CNT      (10)


#define ADD_ERROR_CODE(X, CODE, TYPE)           (X = (TYPE)((u32)X | (u32)CODE))
#define CLEAR_ERROR_CODE(X, CODE, TYPE)         (X = (TYPE)((u32)X & (~(u32)CODE)))



#define ADD_CRC_ERROR(X, TYPE)        \
    do {                                \
         (X = (TYPE)((u32)X | (u32)eModNetErr::CRC_WRONG)); \
         m_uiCrcErrCnt++;               \
    }while(0)


#define ADD_TIMEOUT_ERROR(X, TYPE)              \
    do {                                        \
         (X = (TYPE)((u32)X | (u32)eModNetErr::TIMEOUT)); \
         m_uiTimeoutCnt++;               \
    }while(0)



#define CLEAR_NETWORK_ERROR(X, TYPE) \
    do { \
        (X) = (TYPE)((u32)(X) & ~(NETWORK_ERR_CRC | NETWORK_ERR_TIMEOUT)); \
        m_uiCrcErrCnt = 0; \
        m_uiTimeoutCnt = 0; \
    } while (0)



enum class eHDuplMasterSts{
    Idle = 0,
    Send,
    WaitAck,
    AckOk,
};



enum class eModCommSts{
    IDLE = 0,

    // Normal Stage
    SEND_MSG,
    CHK_ACK,
    ACK_OK,
    ACK_ABNORMAL,
    WAIT_SESS,
    EXPIRE_SESS,

    // AbNormal Stage with restorable
    CRC_ERR,
    TIMEOUT,
    RESTORE,


    // AbNormal Stage with NOT restorable
    SKIP_DEV = 0x80,

    URGENT_ERROR,

    UNKNOWN_STS = 0xFF,
};



enum class eModNetErr{
    NO_ERR = 0,

    // usual Err
    CRC_WRONG = NETWORK_ERR_CRC,
    TIMEOUT = NETWORK_ERR_TIMEOUT,

    // Serious Err
    CRC_WRONG_FRQ,
    TIMEOUT_CONSEQ,
    LOST_DEV,
};





class IRs485Device{
public:
    virtual eModCommSts ModuleCtl(u32 flag, std::function<u32(void)> fpFuncTick) = 0;
    virtual void RcvByteHnd(u8) = 0;

    DrvRs485* m_ptrPort;
    eModCommSts ucCommSts;
    eModNetErr m_eNetworkErr;
    eModNetErr m_eNetworkErr_pre;

    u32 m_uiTimeoutCnt;
    u32 m_uiCrcErrCnt;
};




typedef struct SlaveList_tag{
public:
    u8 Id;
    IRs485Device* pxDevice;
    struct SlaveList_tag* next;
}SlaveList_t;




class HalfDuplMaster{
public:
    HalfDuplMaster() {
 
    }

    void Init(DrvRs485* _port){
        m_port = _port;

    }

    eModCommSts Process(std::function<u32(void)> fpFuncTick, std::function<void(u32)> funcDelay){


        // check rcv byte from remote slave device
        while(m_port->IsData_Available()){

            u8 rcvB = 0;

            m_port->ReadByte(&rcvB);

            //copy or share rcvB to current slave instance rcvHandle
            m_pxCurrSlave->RcvByteHnd(rcvB);
        }

        eModCommSts rtn = m_pxCurrSlave->ModuleCtl(0, fpFuncTick);

        m_pxCurrSlave->m_eNetworkErr_pre = m_pxCurrSlave->m_eNetworkErr;

        switch(rtn){
            case eModCommSts::IDLE:
                break;

            case eModCommSts::EXPIRE_SESS:
            case eModCommSts::SKIP_DEV:
                GoToNextDev();  
                break;

            case eModCommSts::RESTORE:
                RestorPort(funcDelay);
                break;

            case eModCommSts::URGENT_ERROR:
            	GoToNextDev();
                // TODO : Error Propagation & Emergency stop process start
                break;

            default:
                break;
        }

        return rtn;
        
    }

    

    void SetDeviceList(SlaveList_t* list) {
        deviceList = list;
        m_pxCurrSlave = deviceList->pxDevice;
        m_pxCurrSlave->m_ptrPort = m_port;  
    }


private:

    DrvRs485* m_port;


    u8 m_supportWaitSendDone = 0;


    IRs485Device* m_pxCurrSlave;
    SlaveList_t* deviceList;


    void GoToNextDev(){

        m_pxCurrSlave->m_ptrPort = nullptr;

        
        deviceList = deviceList->next;
        m_pxCurrSlave = deviceList->pxDevice;

        if(m_pxCurrSlave->ucCommSts != eModCommSts::SKIP_DEV && m_pxCurrSlave->ucCommSts != eModCommSts::URGENT_ERROR)
            m_pxCurrSlave->ucCommSts = eModCommSts::IDLE;

        m_pxCurrSlave->m_ptrPort = m_port; 
    }


    void RestorPort(std::function<void(u32)> funcDelay){
        m_port->FlowCtl(0);
        m_port->StopCommRx();
        funcDelay(5);
        
        m_port->PortReset();
        funcDelay(100);

        m_port->StopCommRx();
        funcDelay(5);
        m_port->Reset_RcvHnd();

        GoToNextDev();
        PRINT_DBG("Module Network timeout is over 10 count\r\nPort Init!\r\n");
    }


    //static void OnISR_DMASendDone(void* args);
};


#endif
