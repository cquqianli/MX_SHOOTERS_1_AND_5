#ifndef mpu_H
#define mpu_H
#include "stdint.h"

typedef struct
{
	float q[4];
	
	float yawangle;
	float pitangle;
	float yawspeed;
	float pitspeed;
	float accx;
	float accy;
	float instangle[2][3];
	
}MPU_Data;

void mpu_Quat_reci(uint8_t raw_data[8],MPU_Data *mdata);
void mpu_acc_reci(uint8_t raw_data[8],MPU_Data *mdata);
void mpu_spe_reci(uint8_t raw_data[8],MPU_Data *mdata);
void mpu_angle_calc(MPU_Data *mdata);

extern MPU_Data mpudata;
extern MPU_Data mpulastdata;
#endif
