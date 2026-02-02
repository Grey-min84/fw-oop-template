#ifndef __POWER_CTL_MODULE_H__
#define __POWER_CTL_MODULE_H__

#include "board_config.h"
#include "halfDupl_master.hpp"

enum class ePCM_ErrCode{
    HEALTH = 0,
    BOARD_RESET ,
};



class PowerCtlModule : public IRs485Device{
public:

    PowerCtlModule() {
        uiWaitPeriod = 50;
        ucCommSts = eModCommSts::IDLE;
    }

    void Init(u32 period){uiWaitPeriod = period;    }

    void UpdateHostHeartbeat();
    
    /* ********************* Implement GRModuleCommon ****************** */
    eModCommSts ModuleCtl(u32 flag, std::function<u32(void)> fpFuncTick) override;
    void RcvByteHnd(u8) override;
    /* ***************************************************************** */

    u16 Heartbeat_PktMake();
    void RcvPktParsing(u8 cmd, u8* buf);


    ePCM_ErrCode eErrorSts;

private:

    u8 m_aucSendBuf[256];
    u32 uiWaitPeriod;
    
    u32 uiTickLast;
    u32 m_uiSendCnt;


};


#endif
