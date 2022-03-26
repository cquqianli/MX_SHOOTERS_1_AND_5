#ifndef chasctrl_H
#define chasctrl_H

#include "stdint.h"
#include "motorlib.h"



typedef struct _Chas_Info
{

	
	uint8_t status;   //0x00:follow 0x01:rotate 
											//0x10:speedup_follow 0x11speedup_rotate
											//0x20:speedup_follow 0x21speedup_rotate
	struct
	{
		float xspeed;
		float yspeed;
		float zspeed;
		float zrelangle;
		
		float powerlimit;
	}tar;
	
	struct
	{
		float xspeed;
		float yspeed;
		float zspeed;
		float zrelangle;

		float power; 
		float powerlimit;
		float powerbuffer;
	}cur;
	
}ChasInfo;

extern float yawzeroangle[2];
extern ChasInfo chasinfo;
extern MotorInfo wheelinfo[4],yawinfo;
void yawzero_clac(MotorInfo *yinfo,ChasInfo *ch,float yza[2]);

#endif 
