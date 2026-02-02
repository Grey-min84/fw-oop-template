#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__
#include "typeSimple.h"



enum class eBCM_OperationMode{
	User = 0,
	HostCtl,
	Host_FailSafe,
	Motor_Manual = 10,
	Aging_Test = 11,
	Board_Reset = 20,
};



class IBrake{
public:
    // Brake Control Interface
    virtual bool ChkUserBrakePush() = 0;
    virtual void BrakeCtl(u8 _ucCmd, u16 _usPressure, u32 _uiResv) = 0;
};



class ISteer{
public:
    // Steer Control Interface
    virtual float GetSteerAngle(void) = 0;
    virtual u8 GetSteerCtlStatus() = 0;

};




class IDrive{
public:
    // Drive Control Interface
    virtual float GetVehicleSpd() = 0;
    virtual void CtlCommand( float _fVel, float _fAcc) = 0;
};





class ILidar{
public:
    // Drive Control Interface
    virtual void OperationCtl(bool, u8) = 0;
    virtual bool GetDistance(float*) = 0;
    virtual u32 GetErrorCode( ) = 0;

};


#endif