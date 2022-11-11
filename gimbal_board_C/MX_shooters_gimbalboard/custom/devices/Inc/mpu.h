#ifndef mpu_H
#define mpu_H
#include "stdint.h"
#include "can.h"

#define angledata 0x02
#define speeddata 0x01
#define accdata 0x00


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
void mpu_ang_reci(uint8_t raw_data[8],MPU_Data *mdata);
void mpu_angle_calc(MPU_Data *mdata);

void mpucanbaud_set(int32_t baudrate,int16_t id,CAN_HandleTypeDef hcanx);
void mpucanid_set(int32_t tarid,int16_t id,CAN_HandleTypeDef hcanx);
void mpucanreportfreq_set(int32_t freq,int16_t id,CAN_HandleTypeDef hcanx,int8_t dataname);


extern MPU_Data mpudata;
extern MPU_Data mpulastdata;
extern uint8_t MPU_ready;
#endif
