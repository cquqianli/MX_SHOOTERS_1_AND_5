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
		uint8_t maglid;//0x00:opened 0x01:opening 0x10:closed 0x11:closing 
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
											//0x20:speeddown_follow 0x21speeddown_rotate
		float xspeed;
		float yspeed;
		float zrelangle;

	}chas;//
	
}RoboCtrlInfo;

typedef struct _Robo_cur_Info
{
	float xspeed;
	float yspeed;
	
}RoboCurInfo;

extern RoboCtrlInfo roboctrlinfo;

#endif 
