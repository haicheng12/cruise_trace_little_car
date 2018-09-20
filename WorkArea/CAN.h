#ifndef _CAN_h_
#define _CAN_h_
#include "sys.h"

#define abs(x) ((x)>0? (x):(-(x)))

typedef struct
{
	
	union
	{
		u8 DATA_8[2];
		u16 DATA_16;
	}Front;
	
}PS_TYPE;													//��紫��������


void CAN1_Configuration(void);


#endif




