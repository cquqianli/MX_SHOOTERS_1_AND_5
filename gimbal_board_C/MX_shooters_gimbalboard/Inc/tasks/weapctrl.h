#ifndef weapctrl_H
#define weapctrl_H

#include "motorlib.h" 

extern MotorInfo fricinfo[2],triginfo,magainfo;
extern PID_regulator fricspeedpid[2],triganglepid,trigspeedpid,magaanglepid,magaspeedpid;

#endif
