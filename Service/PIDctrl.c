/**
 *@file PIDCtrl.c
 *@date 2019. 12. 29
 *@author JH.Park
 */
#include "string.h"
#include "stdlib.h"
#include "PIDCtrl.h"
#include <stdint.h>


void InitPIDCtrlVarInt(PPID_CTRL_VAR_INT l_pPIDCtrl)
{
	memset(l_pPIDCtrl, 0, sizeof(PID_CTRL_VAR_INT));

	l_pPIDCtrl->m_Kp = PID_PRECISION;
	l_pPIDCtrl->m_MaxErrorSum = PID_DEFAULT_MAXERRORSUM_INT;
}

void SetPIDGainInt(PPID_CTRL_VAR_INT l_pstPIDCtrl, int32_t l_iKp, int32_t l_iKi, int32_t l_iKd, int32_t l_iKa)
{
	l_pstPIDCtrl->m_Kp = l_iKp;
	l_pstPIDCtrl->m_Ki = l_iKi;
	l_pstPIDCtrl->m_Kd = l_iKd;
	l_pstPIDCtrl->m_Ka = l_iKa;
}

void SetPIDConfigVarInt(PPID_CTRL_VAR_INT l_pstPIDCtrl, int32_t l_iMaxErrorSum, int32_t l_iMaxOutput, int32_t l_iMinOutput)
{
	l_pstPIDCtrl->m_MaxErrorSum = l_iMaxErrorSum;
	l_pstPIDCtrl->m_MaxOutput = l_iMaxOutput;
	l_pstPIDCtrl->m_MinOutput = l_iMinOutput;
}

int CalcuatePIDOutputInt(PPID_CTRL_VAR_INT l_pPIDCtrl, int l_iError)
{
	int l_iErrorDiff, l_iOutput, l_iRet;

	l_iErrorDiff = l_iError - l_pPIDCtrl->m_PreError;

	l_pPIDCtrl->m_ErrorSum += l_iError;

	l_iOutput = ( (l_iError*l_pPIDCtrl->m_Kp) + (l_pPIDCtrl->m_ErrorSum*l_pPIDCtrl->m_Ki) + (l_iErrorDiff*l_pPIDCtrl->m_Kd) )/PID_PRECISION;

	if( l_iOutput > l_pPIDCtrl->m_MaxOutput )
	{
		l_iRet = l_pPIDCtrl->m_MaxOutput;
	}
	else if( l_iOutput < l_pPIDCtrl->m_MinOutput )
	{
		l_iRet = l_pPIDCtrl->m_MinOutput;
	}
	else
		l_iRet = l_iOutput;

	if( l_pPIDCtrl->m_ErrorSum > l_pPIDCtrl->m_MaxErrorSum)
		l_pPIDCtrl->m_ErrorSum = l_pPIDCtrl->m_MaxErrorSum;
	else if( l_pPIDCtrl->m_ErrorSum < -l_pPIDCtrl->m_MaxErrorSum)
		l_pPIDCtrl->m_ErrorSum = -l_pPIDCtrl->m_MaxErrorSum;

	l_pPIDCtrl->m_PreError = l_iError;

	return l_iRet;
}



void InitPIDCtrlVarFloat(PPIDCtrlFloat_t l_pPIDCtrl)
{
	memset(l_pPIDCtrl, 0, sizeof(PIDCtrlFloat_t));

	l_pPIDCtrl->m_Kp = 1.0f;
	l_pPIDCtrl->m_MaxErrorSum = PID_DEFAULT_MAXERRORSUM_FLOAT;
}

void SetPIDGainFloat(PPIDCtrlFloat_t l_pstPIDCtrl, float l_fKp, float l_fKi, float l_fKd, float l_fKa)
{

	l_pstPIDCtrl->m_Kp = l_fKp;
	l_pstPIDCtrl->m_Ki = l_fKi;
	l_pstPIDCtrl->m_Kd = l_fKd;

	l_pstPIDCtrl->m_Kw = l_fKa;
	l_pstPIDCtrl->m_ErrorSum = 0;
	l_pstPIDCtrl->m_PreError = 0;
}

void SetPIDConfigVarFloat(PPIDCtrlFloat_t l_pstPIDCtrl, float l_fMaxErrorSum, float l_fMaxOutput, float l_fMinOutput)
{
	l_pstPIDCtrl->m_MaxErrorSum = l_fMaxErrorSum;
	l_pstPIDCtrl->m_MaxOutput = l_fMaxOutput;
	l_pstPIDCtrl->m_MinOutput = l_fMinOutput;
}

float CalcuatePIDOutputFloat(PPIDCtrlFloat_t l_pPIDCtrl, float l_fError)
{
	float l_fErrorDiff, l_fOutput, l_fRet;

	l_fErrorDiff = l_fError - l_pPIDCtrl->m_PreError;

	l_pPIDCtrl->m_ErrorSum += l_fError;

	l_fOutput = ( (l_fError*l_pPIDCtrl->m_Kp) + (l_pPIDCtrl->m_ErrorSum*l_pPIDCtrl->m_Ki) + (l_fErrorDiff*l_pPIDCtrl->m_Kd) );

	if( l_fOutput > l_pPIDCtrl->m_MaxOutput )
	{
		l_fRet = l_pPIDCtrl->m_MaxOutput;
	}
	else if( l_fOutput < l_pPIDCtrl->m_MinOutput )
	{
		l_fRet = l_pPIDCtrl->m_MinOutput;
	}
	else
		l_fRet = l_fOutput;

	if( l_pPIDCtrl->m_ErrorSum > l_pPIDCtrl->m_MaxErrorSum)
		l_pPIDCtrl->m_ErrorSum = l_pPIDCtrl->m_MaxErrorSum;
	else if( l_pPIDCtrl->m_ErrorSum < -l_pPIDCtrl->m_MaxErrorSum)
		l_pPIDCtrl->m_ErrorSum = -l_pPIDCtrl->m_MaxErrorSum;

	l_pPIDCtrl->m_PreError = l_fError;

	return l_fRet;
}



