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
	} weap;//云台发射端
	
	struct
	{
		uint8_t status; //0x00:manual 0x01:auto
		float pitangle;
		float yawangle;
	}gimb;//云台的角度
	
	struct
	{

		uint8_t status;   //0x00:follow 0x01:rotate 
											//0x10:speedup_follow 0x11speedup_rotate
											//0x20:speeddown_follow 0x21speeddown_rotate
		float xspeed;
		float yspeed;
		float zrelangle;

	}chas;//底盘的x速度，y速度，z轴角速度（应该，有待确认）
	
} RoboCtrlInfo;//全局变量，其他地方都可以读取

typedef struct _Robo_cur_Info
{
	float xspeed;
	float yspeed;
	float zrelangle;
}RoboCurInfo; //这个不是和robo_info里面的chas 一样吗，还少了一个status

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
