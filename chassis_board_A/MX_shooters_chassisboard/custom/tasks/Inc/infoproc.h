#ifndef infoproc_H
#define infoproc_H

#include "stdint.h"
#include "roboconfig.h"
#include "chasctrl.h"

void ctrlmestochas_unpack(ChasInfo *chinfo,ChasInfo *chlinfo,uint8_t rx[8]);
void curmestochas_unpack(ChasInfo *chinfo,uint8_t rx[8]);
extern uint8_t GIMB_READY;
#endif 
