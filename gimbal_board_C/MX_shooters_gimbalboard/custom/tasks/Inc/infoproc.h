#ifndef infoproc_H
#define infoproc_H

#include "stdint.h"
#include "roboconfig.h"
#include "motorlib.h"
#include "canbus.h"

typedef struct _Robo_Info
{
	struct
	{
		uint8_t status; //0x00:off 0x01:loading 0x10:ready 
	}weap;//
	
	struct
	{
		uint8_t status; //0x00:manual 0x01:auto
		float pitangle;
		float yawangle;
	}gimb;//
	
	struct
	{

		uint8_t status;   //0x00:follow 0x01:rotate 
											//0x10:speedup_follow 0x11speedup_rotate
											//0x20:speedup_follow 0x21speedup_rotate
		float xspeed;
		float yspeed;
		float zrelangle;

	}chas;//
	
}RoboCtrlInfo;




#endif 
