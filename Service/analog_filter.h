#ifndef __ANALOG_FILTER_H__
#define __ANALOG_FILTER_H__
#include "typeSimple.h"

#define MAX_MEDIAN_FILTER_COUNT 7
#define PI 3.141592f

#define MOV_AVG_SAMPLE_MAX		256


/* Average Filter Variables */
typedef struct _AVERAGE_FILTER_VAR_
{
	float m_Coeff;
	int32_t m_PreValue;
}AVG_FILTER_VAR, *PAVG_FILTER_VAR;

/* Median Filter Variables */
typedef struct _MEDIAN_FILTER_VAR_
{
	uint32_t m_BuffIndex;
	uint32_t m_BuffCount;
	int32_t m_Buff[MAX_MEDIAN_FILTER_COUNT];
	int32_t m_BuffCopy[MAX_MEDIAN_FILTER_COUNT];
}MedianFilter_t;


typedef struct _MEDIAN_FILTER_FLOAT_VAR_
{
	uint32_t m_BuffIndex;
	uint32_t m_BuffCount;
	float m_Buff[MAX_MEDIAN_FILTER_COUNT];
	float m_BuffCopy[MAX_MEDIAN_FILTER_COUNT];
}MedianFilter_float_t;



typedef struct _MOV_FAVG_FILTER_{
	int32_t m_iSampleCnt;
	float m_fSum;
	float m_fDataBuf[MOV_AVG_SAMPLE_MAX];
	int32_t m_iIndex;
}MovFAvgFilter_t;








#ifdef __cplusplus
extern "C" {
#endif
void InitAverageFilter(PAVG_FILTER_VAR l_pstVar, float l_iCoeff);
int32_t AverageFilter(PAVG_FILTER_VAR l_pstVar, int32_t l_NewValue);

void InitMedianFilterVar(MedianFilter_t *l_pstVar, uint16_t l_usCount);
int32_t MedianFilter(MedianFilter_t *l_pstVar, int32_t l_NewValue);

void InitMedianFilterVar_float(MedianFilter_float_t *l_pstVar, uint16_t l_usCount);
float MedianFilter_float(MedianFilter_float_t *l_pstVar, float l_fNew);


void BubbleSort(int32_t *l_iDataArray, uint16_t l_iCnt);



uint8_t InitMoveAvgFilter_float(MovFAvgFilter_t* pstMovAvg, int32_t iSampleCnt);
float MoveAvgFilter_float(MovFAvgFilter_t* pstMovAvg, float fValue);
#ifdef __cplusplus
}
#endif


#endif