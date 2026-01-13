#include "analog_filter.h"





void BubbleSort(int32_t *l_iDataArray, uint16_t l_iCnt)
{
	int i, j;
	int l_fW;

	//bubble sort r
	for (i = (l_iCnt - 1); i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (l_iDataArray[j] > l_iDataArray[j + 1]) // wrong order? - swap them
			{
				l_fW = l_iDataArray[j];
				l_iDataArray[j] = l_iDataArray[j + 1];
				l_iDataArray[j + 1] = l_fW;
			}
		}
	}
}

void BubbleSort_float(float *l_fDataArray, uint16_t l_iCnt)
{
	int i, j;
	float l_fW;

	//bubble sort r
	for (i = (l_iCnt - 1); i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (l_fDataArray[j] > l_fDataArray[j + 1]) // wrong order? - swap them
			{
				l_fW = l_fDataArray[j];
				l_fDataArray[j] = l_fDataArray[j + 1];
				l_fDataArray[j + 1] = l_fW;
			}
		}
	}
}


void InitAverageFilter(PAVG_FILTER_VAR l_pstVar, float l_iCoeff)
{
	l_pstVar->m_Coeff = l_iCoeff;
	l_pstVar->m_PreValue = 0;
}


int32_t AverageFilter(PAVG_FILTER_VAR l_pstVar, int32_t l_iNewValue)
{
	int32_t l_iRet = 0;
	
	l_iRet = (l_pstVar->m_Coeff*l_iNewValue + (1.0f-l_pstVar->m_Coeff)*l_pstVar->m_PreValue ) ;
	l_pstVar->m_PreValue = l_iRet;

	return l_iRet;
}



void InitMedianFilterVar(MedianFilter_t *l_pstVar, uint16_t l_usCount)
{
	if(l_usCount >= MAX_MEDIAN_FILTER_COUNT)
	{
		l_usCount = MAX_MEDIAN_FILTER_COUNT;
	}

	l_pstVar->m_BuffCount = l_usCount;
	l_pstVar->m_BuffIndex = 0;

	memset(l_pstVar->m_Buff, 0, sizeof(uint32_t) * MAX_MEDIAN_FILTER_COUNT);
	memset(l_pstVar->m_BuffCopy, 0, sizeof(uint32_t) * MAX_MEDIAN_FILTER_COUNT);
}


int32_t MedianFilter(MedianFilter_t *l_pstVar, int32_t l_iNewValue)
{
	int32_t l_iRet = 0;
	uint16_t l_usCenterIndex;

	l_usCenterIndex = l_pstVar->m_BuffCount/2;

	//if(l_pstVar->m_Buff != (void*)0 )
	{
		l_pstVar->m_Buff[ l_pstVar->m_BuffIndex ] = l_iNewValue;
		memcpy((void*)l_pstVar->m_BuffCopy, (void*)l_pstVar->m_Buff, l_pstVar->m_BuffCount*sizeof(int32_t));
		BubbleSort(l_pstVar->m_BuffCopy, l_pstVar->m_BuffCount );
		l_iRet = l_pstVar->m_BuffCopy[l_usCenterIndex];
		l_pstVar->m_BuffIndex++;
		if( l_pstVar->m_BuffIndex >= l_pstVar->m_BuffCount )
			l_pstVar->m_BuffIndex = 0;
	}

	return l_iRet;
}





void InitMedianFilterVar_float(MedianFilter_float_t *l_pstVar, uint16_t l_usCount)
{
	if(l_usCount >= MAX_MEDIAN_FILTER_COUNT)
	{
		l_usCount = MAX_MEDIAN_FILTER_COUNT;
	}

	l_pstVar->m_BuffCount = l_usCount;
	l_pstVar->m_BuffIndex = 0;

	memset(l_pstVar->m_Buff, 0, sizeof(uint32_t) * MAX_MEDIAN_FILTER_COUNT);
	memset(l_pstVar->m_BuffCopy, 0, sizeof(uint32_t) * MAX_MEDIAN_FILTER_COUNT);
}


float MedianFilter_float(MedianFilter_float_t *l_pstVar, float l_fNewValue)
{
	float l_fRet = 0;
	uint16_t l_usCenterIndex;

	l_usCenterIndex = l_pstVar->m_BuffCount/2;

	//if(l_pstVar->m_Buff != (void*)0 )
	{
		l_pstVar->m_Buff[ l_pstVar->m_BuffIndex ] = l_fNewValue;
		memcpy((void*)l_pstVar->m_BuffCopy, (void*)l_pstVar->m_Buff, l_pstVar->m_BuffCount*sizeof(int32_t));
		BubbleSort_float(l_pstVar->m_BuffCopy, l_pstVar->m_BuffCount );
		l_fRet = l_pstVar->m_BuffCopy[l_usCenterIndex];
		l_pstVar->m_BuffIndex++;
		if( l_pstVar->m_BuffIndex >= l_pstVar->m_BuffCount )
			l_pstVar->m_BuffIndex = 0;
	}

	return l_fRet;
}





uint8_t InitMoveAvgFilter_float(MovFAvgFilter_t* pstMovAvg, int32_t iSampleCnt){

	memset(pstMovAvg->m_fDataBuf, 0, sizeof(float)*MOV_AVG_SAMPLE_MAX);
	pstMovAvg->m_fSum = 0.0f;
	pstMovAvg->m_iIndex = 0;

	if(iSampleCnt < 1 || iSampleCnt > MOV_AVG_SAMPLE_MAX){
		return 1;
	}

	pstMovAvg->m_iSampleCnt = iSampleCnt;

	return 0;
}


float MoveAvgFilter_float(MovFAvgFilter_t* pstMovAvg, float fValue){

	float l_fMoveFilterAvg = 0.0f;


	// 마지막 데이터 빼기
	pstMovAvg->m_fSum -= pstMovAvg->m_fDataBuf[pstMovAvg->m_iIndex];

	pstMovAvg->m_fDataBuf[pstMovAvg->m_iIndex] = fValue;

	// 데이터 넣기
	pstMovAvg->m_fSum += pstMovAvg->m_fDataBuf[pstMovAvg->m_iIndex];
	
	pstMovAvg->m_iIndex++;


	if(pstMovAvg->m_iIndex > pstMovAvg->m_iSampleCnt - 1) 
		pstMovAvg->m_iIndex = 0 ;


	l_fMoveFilterAvg = pstMovAvg->m_fSum / (float)pstMovAvg->m_iSampleCnt;


	return l_fMoveFilterAvg ;

}
