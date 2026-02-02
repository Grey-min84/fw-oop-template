#ifndef __BRAKE_CTL_MODE_H__
#define __BRAKE_CTL_MODE_H__
#include "board_config.h"
#include "halfDupl_master.hpp"
#include "module_interface.hpp"


enum class eBCM_ErrCode{
    HEALTH = 0,
    BOARD_RESET  ,
    RELEASE_FAIL,
    PUSH_FAIL,
};




class BrakeCtlModule;


class BrakeModTest{
public:
    void Init(BrakeCtlModule* _pxModule){
        pxModule = _pxModule;

    }

    void FullBrake();
    void ReleaseBrake();
    void ControlPressure(u16);
    void ShowInfo();
    void MotorCtl(u8, u8, u16); // On/Off, Dir, power_level

    bool bIsLogOn;
    
private:
    BrakeCtlModule* pxModule;

};




class BrakeCtlModule : IBrake, IRs485Device{
public:

    BrakeCtlModule() {
        uiWaitPeriod = 50;
        ucCommSts = eModCommSts::IDLE;
    }

    void Init(u32 period){uiWaitPeriod = period;}
    void InitTest(){m_xTest.Init(this); }

    void RcvPktParsing(u8 cmd, u8* buf);
    u16 Heartbeat_PktMake();

    /* ********************** Implement IRs485Device ******************* */
    eModCommSts ModuleCtl(u32 flag, std::function<u32(void)> fpFuncTick) override;
    void RcvByteHnd(u8) override;
    /* ***************************************************************** */
    
    
    // /* ************************** Implement IBrake ********************* */
    bool ChkUserBrakePush() override;
    void BrakeCtl(u8 _ucCmd, u16 _usPressure, u32 _uiResv) override;
    // /* ****************************************************************** */


    /* ************************************* BrakeUnitTest Support ******************************* */
    BrakeModTest* GetTestObj(){return &m_xTest;}
    /* ********************************************************************* */

    eBCM_ErrCode eErrorSts;
private:

    u8 m_aucSendBuf[256];
    u32 uiWaitPeriod;
    
    u32 uiTickLast;



    BrakeModTest m_xTest;


};


#endif
