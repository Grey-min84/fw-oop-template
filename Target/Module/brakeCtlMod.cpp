#include "brakeCtlMod.h"


void BrakeCtlModule::RcvByteHnd(u8 inB) {


}



eModCommSts BrakeCtlModule::ModuleCtl(u32 flag, std::function<u32(void)> fpFuncTick) {

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








u16 BrakeCtlModule::Heartbeat_PktMake(){
    

}




void BrakeCtlModule::RcvPktParsing(u8 cmd, u8* buf){


}













void BrakeCtlModule::BrakeCtl(u8 _ucCmd, u16 _usPressure, u32 _uiResv) {


}










void BrakeModTest::FullBrake(){

}

void BrakeModTest::ReleaseBrake(){

}

void BrakeModTest::ControlPressure(u16 pressure){

}

void BrakeModTest::MotorCtl(u8 onOff, u8 dir, u16 duty){

}

void BrakeModTest::ShowInfo(){

}
