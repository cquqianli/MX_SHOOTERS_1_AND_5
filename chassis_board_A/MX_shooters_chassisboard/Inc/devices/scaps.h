#ifndef capsctrl_H
#define capsctrl_H

#include "stdint.h"

typedef struct _Caps_Info
{
	float inputvoltage;
	float capsvoltage;
	float inputcurrent;
	float tarpower;
	
}CapsInfo;

void capsinfo_unpack(CapsInfo *caps,uint8_t rx[8]); 
extern CapsInfo capsinfo;
#endif
