#include "powerCtlMod.h"


void PowerCtlModule::RcvByteHnd(u8 inB) {


}



eModCommSts PowerCtlModule::ModuleCtl(u32 flag, std::function<u32(void)> fpFuncTick) {

    u32 currTick = fpFuncTick();
    u16 usLen = 0;

    // State manage
    switch(ucCommSts){
        case eModCommSts::IDLE:
            break;

        case eModCommSts::SEND_MSG:
            break;
        
        case eModCommSts::CHK_ACK:
            break;

        case eModCommSts::ACK_OK:
            break;

        case eModCommSts::WAIT_SESS:
            break;

        case eModCommSts::EXPIRE_SESS:
            break;


        // exception handle
        case eModCommSts::TIMEOUT:
            break;

        case eModCommSts::SKIP_DEV:
            break;

        case eModCommSts::URGENT_ERROR:
            break;

        default:    return eModCommSts::UNKNOWN_STS;

    }

    return eModCommSts::UNKNOWN_STS;

}







void PowerCtlModule::RcvPktParsing(u8 cmd, u8* buf){


}





u16 PowerCtlModule::Heartbeat_PktMake(){
    
   return 0;
}
