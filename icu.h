/*--------------------------------------------------------------------------------------------------------------------------
 * file name  : icu.h
 * Author     : OUN
 * Created on : Dec 5, 2020
 * description: ICU header file driver
 --------------------------------------------------------------------------------------------------------------------------*/

#ifndef ICU_H_
#define ICU_H_

/*-----------------------------------------------------INCLUDES------------------------------------------------------------*/

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*----------------------------------------------------DFINATIONS-----------------------------------------------------------*/


/*-------------------------------------------------TYPES DECLARATION-------------------------------------------------------*/
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

typedef enum{
	FALLING,RISING
}Icu_EdgeType;

typedef struct{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_ConfigType;



/*-----------------------------------------------FUNCTION DECLARATIONS-----------------------------------------------------*/

void Icu_init(const Icu_ConfigType *Config_Ptr);
void Icu_setCallBack(void(*a_ptr)(void));
void Icu_setEdgeDetectionType(const Icu_EdgeType edgeType);
uint16 Icu_getInputCaptureValue(void);
void Icu_clearTimerValue(void);
void Icu_deInit(void);


#endif /* ICU_H_ */
