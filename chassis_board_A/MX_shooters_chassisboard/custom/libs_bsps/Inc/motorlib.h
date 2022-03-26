#ifndef ctrltask_H
#define ctrltask_H

#include "pid.h"
#include "stm32f4xx.h"

#define PIDoutercyclerate 2

#define asinwave 0x01
#define atriwave 0x02
#define stepwave 0x03

#define speedupcps 0

float kictrl(PID_regulator *pid,float effctarea);



typedef struct _Motor_Info
{
	struct
	{
		
		float angle_limit[2];//角度限制，无限制则为{-180，180}，代码内使用单位度
		float speed_limit[2];//速度限制，查询电机电调套装手册，代码内使用单位rpm
		float current_limit[2];//电流限制，查询电机电调套装手册，代码内使用单位A
		float reductiongearratio;//电机及其所在机构构成的减速倍率，减速时代码内此值应大于一
		float inpositioncurrent;//撞限位的电流值，使用单位A
		float installationangle;//安装角度，即电机归零时的角度，针对增量式编码器（3508/2006）和绝对值编码器（6020）有不同的使用方法
		int16_t pidoutcycrate;
	}parameter;
	
	struct
	{
		float angle;
		float speed;
		float currentsum;
		float pidcount;
		float anglechanged;
		float temp_angle[2];

	}tempdata;//用于解算角度的临时参数
	
	struct
	{
		float angle;
		float speed;
		float current;//2006直接反馈转矩常系数为一，3508反馈转矩电流
	}tarmotorinfo;//记录电机目标参数
	
	struct
	{
		float angle;
		float speed;
		float current[5];
	}curmotorinfo;//记录电机目标角度
	
}MotorInfo;

typedef struct _wave_HandleTypeDef
{
	uint8_t wavetpye;
	float waveperiod;
	float taskperiod;
	float amplitude;
}wave_HandleTypeDef;

typedef struct
{
	float data;   									//输入数据
	float lastdata;   									//记录上次数据
	float k;								//期望k（/ms）
	float sampleperi;//ms
	float outdata;
}kshaper_handle;

void gearmotor_angledecoder(MotorInfo *Motor);
void gearmotor_angledecoder_sum(MotorInfo *Motor);
void motaspid_calc(MotorInfo *minfo,PID_regulator *anglepid,PID_regulator *speedpid);
void canrxtomotinfo(MotorInfo *minfo,uint8_t rx[8]);
void motcurrentsensor(MotorInfo *minfo);
void k_shaper(kshaper_handle *kdata);
float anglecircle(float angle);
float anglelimit(float angle,float anglemax,float anglemin);

#define Defaul_3508_Parameter \
{\
		{-180.f,180.f},\
		{-450.f,450.f},\
		{-10.f,10.f},\
		0,\
		19.2,\
		0,\
		0,\
}\



#define Defaul_TempData \
{\
		0,\
		0,\
		0,\
		0,\
		0,\
		{0,0},\
		0,\
}\

#define Defaul_TarMotorCtrlInfo \
{\
		0,\
		0,\
		0,\
}\

#define Defaul_CurMotorCtrlInfo \
{\
		0,\
		0,\
		0,\
}\

#define Default_2006_Config \
{\
	Defaul_2006_Parameter,\
	Defaul_TempData,\
	Defaul_TarMotorCtrlInfo,\
	Defaul_CurMotorCtrlInfo,\
}\

#endif
