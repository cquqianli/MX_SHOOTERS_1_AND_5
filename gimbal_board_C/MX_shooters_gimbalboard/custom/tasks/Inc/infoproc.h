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
	float zrelangle;
}RoboCurInfo;

extern RoboCtrlInfo roboctrlinfo;
extern RoboCurInfo robocurinfo;

extern int16_t mestogimb[2],curmestochas[4],ctrlmestochas[4],mestocan1_0x1ff[4],mestocan2_0x1ff[4],mestocan1_0x200[4],mestocan2_0x200[4];

void mestocan1_0x1ff_pack(int16_t mespacked[4]);

void mestocan2_0x1ff_pack(int16_t mespacked[4]);

void mestocan1_0x200_pack(int16_t mespacked[4]);

void mestocan2_0x200_pack(int16_t mespacked[4]);

void mestocan1_0x2ff_pack(int16_t mespacked[4]);

void mestocan2_0x2ff_pack(int16_t mespacked[4]);

void zero_pack(int16_t mespacked[4]);

#endif 
