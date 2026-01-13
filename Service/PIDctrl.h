/**
 *@file PIDCtrl.h
 *@date 2019. 12. 29
 *@author JH.Park
 */

#ifndef _PIDCTRL_H_
#define _PIDCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#define USE_INTEGER_PID (1)



#define PID_PRECISION 10000 
#define PID_DEFAULT_MAXERRORSUM_INT 100000

/* PID control value */
typedef struct _PID_CONTROL_VAR_INT_
{
	int m_Kp;
	int m_Ki;
	int m_Kd;
	int m_Ka;
	int m_ErrorSum;
	int m_PreError;
	int m_MaxErrorSum;
	int m_MaxOutput;
	int m_MinOutput;
}PID_CTRL_VAR_INT, *PPID_CTRL_VAR_INT;

void InitPIDCtrlVarInt(PPID_CTRL_VAR_INT l_pPIDCtrl);
void SetPIDGainInt(PPID_CTRL_VAR_INT l_pstPIDCtrl, int32_t l_iKp, int32_t l_iKi, int32_t l_iKd, int32_t l_iKa);
void SetPIDConfigVarInt(PPID_CTRL_VAR_INT l_pstPIDCtrl, int32_t l_iMaxErrorSum, int32_t l_iMaxOutput, int32_t l_iMinOutput);
int CalcuatePIDOutputInt(PPID_CTRL_VAR_INT l_pPIDCtrl, int l_iError);




#define PID_DEFAULT_MAXERRORSUM_FLOAT 1000.0f
/* PID control value */
#pragma pack(push,1)
typedef struct _PID_CONTROL_VAR_FLOAT
{
	float m_Kp;
	float m_Ki;
	float m_Kd;
	float m_Kw;
	float m_windUpThr;
	float m_ErrorSum;
	float m_PreError;
	float m_MaxErrorSum;
	float m_MaxOutput;
	float m_MinOutput;
}PIDCtrlFloat_t, *PPIDCtrlFloat_t;
#pragma pack(pop)

void InitPIDCtrlVarFloat(PPIDCtrlFloat_t l_pPIDCtrl);
void SetPIDGainFloat(PPIDCtrlFloat_t l_pstPIDCtrl, float l_fKp, float l_fKi, float l_fKd, float l_fKa);
void SetPIDConfigVarFloat(PPIDCtrlFloat_t l_pstPIDCtrl, float l_fMaxErrorSum, float l_fMaxOutput, float l_fMinOutput);
float CalcuatePIDOutputFloat(PPIDCtrlFloat_t l_pPIDCtrl, float l_fError);



#ifdef __cplusplus
}
#endif

#endif
/* _PIDCTRL_H_ */
