#include "misc.h"


float TwoPointLine(float x1, float y1, float x2, float y2, float x)
{
	float y = 0.0f ;
    y = (((y2-y1)/(x2-x1)) * (x-x1)) + y1 ;
    return y ;
}


float FirstOrderFunc(float slide, float y_offset, float input){

	return (slide * input) + y_offset;
}


void DivideFields(char (*strDest)[16], char* srcStr, int sizeStr)
{
	int i = 0;
	int l_dIndex = 0;
	int l_dCurser = 0;

	// 여기에서 l_strField

	for (i = 0; i < sizeStr; i++)
	{
		if (srcStr[i] == ',' || srcStr[i] == '*')
		{
			strDest[l_dIndex][l_dCurser] = 0;		// 맨 마지막에 0을 넣어서 이전값이 영향을 미치지 않도록 처리.
			//*(strDest + l_dIndex*16 + l_dCurser) = 0;
			l_dIndex++;
			l_dCurser = 0;
		}
		else
		{
			strDest[l_dIndex][l_dCurser] = srcStr[i];
			//*(strDest + l_dIndex*16 + l_dCurser) = srcStr[i];
			l_dCurser++;
		}
	}
}