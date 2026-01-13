#ifndef __ICAN_H__
#define __ICAN_H__

#include "typeSimple.h"
#include <functional>

#define MAX_NR_OF_CAN_DEVICE        (16)
#define STM32_MAX_CAN_BUS       (2)

class CANDevice;

class ICANBus{
public:
    virtual void InitDriver() = 0;
    virtual bool OpenCANBus() = 0;
    virtual ICANBus* GetBus() = 0;

    virtual void RcvTask() = 0;
    virtual void SendTask() = 0;

    u8 g_ucDeviceUsedCnt;
    std::array<CANDevice*, MAX_NR_OF_CAN_DEVICE> m_CANDeviceList;
    //CANDevice* m_CANDeviceList[MAX_NR_OF_CAN_DEVICE];

protected:
    u8 m_pucCanRxData[8];
	u8 m_pucCanTxData[8];
	u8 m_ucCanRecvFlag;

    static u8 g_ucBusUsedCnt;
    static std::array<ICANBus*, STM32_MAX_CAN_BUS> m_CANBusList;
};



class CANDevice{
public:
    void InitCANDevice(u32 l_uiCanId, u32 l_uiIdMask) ;
    //void RegisterCallback(void* _user, std::function<void(void*, u32, u8*, u8)> _cb) {
    
    void RegisterRcvMsgCallback(void* _user, void(*_cb)(void*, u32, u8*, u8)) {
        cb = _cb;
        m_vUser = _user;
    }



    void SendMessage(u8* ) ;
    u8 ReadMessage(u8*, u32, u32(*fpGetTick)(void)) ;
    void EnrollBus(ICANBus*) ;

    void CheckRcv(u32 uiStdId, u8* pucRcvData);

    u8 m_pucTxData[8];
	u8 m_ucTxFlag;
    u32 m_uiTxId;

private:
    
	u32 m_uiIdMask;
	u8 m_pucRxData[8];
	u8 m_ucRxFlag;
    void* m_vUser;
    //std::function<void(void*, u32, u8*, u8)> cb;
    void(*cb)(void*, u32, u8*, u8);
    //void(*cb)(u8*, u8);
	
	
};



#endif
