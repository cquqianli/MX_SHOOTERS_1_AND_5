#include "main.h"

MPU_Data mpudata;
MPU_Data mpulastdata;
static CAN_TxHeaderTypeDef  CAN_tx;
static uint8_t              CAN_tx_message[8];
uint8_t MPU_ready=0;
void axis_angle_toquat(float axis[3],float angle,float q[4])
{
	q[0]=cos(angle/360*2*PI);
	q[1]=sin(angle/360*2*PI)*axis[0];
	q[2]=sin(angle/360*2*PI)*axis[1];
	q[3]=sin(angle/360*2*PI)*axis[2];
}

void quat_inverse(float q[4],float q_[4])
{
	float modu=0;
	for(uint8_t i=0;i<4;i++)
	{
		modu=pow(q[i],2);
	}
	modu=sqrt(modu);
	for(uint8_t i=0;i<4;i++)
	{
		q_[i]=q[i]*modu;
	}
}

void quat_mult(float qa[4],float qb[4],float qout[4])
{
	qout[0]=qa[0]*qb[0]-qa[1]*qb[1]-qa[2]*qb[2]-qa[3]*qb[3];
	qout[1]=qa[0]*qb[1]+qa[1]*qb[0]+qa[2]*qb[3]-qa[3]*qb[2];
	qout[2]=qa[0]*qb[2]-qa[1]*qb[3]+qa[2]*qb[0]+qa[3]*qb[1];
	qout[3]=qa[0]*qb[3]+qa[1]*qb[2]-qa[2]*qb[1]+qa[3]*qb[0];
}

void quar_rota_calc(float axis[3],float angle,float p[4])
{
	float ptemp[2][4]={{0,0,0,0},{0,0,0,0}};
	float qtemp[2][4]={{0,0,0,0},{0,0,0,0}};
	axis_angle_toquat(axis,angle,qtemp[0]);
	quat_inverse(qtemp[0],qtemp[1]);
	quat_mult(qtemp[0],p,ptemp[0]);
	quat_mult(ptemp[0],qtemp[1],ptemp[1]);
	for(uint8_t i=0;i<4;i++)
	{
		p[i]=ptemp[1][i];
	}
}

void mpu_Quat_reci(uint8_t raw_data[8],MPU_Data *mdata)
{
	mdata->q[0]=((int16_t)(raw_data[0]<<8)|(raw_data[1]))/10000.f;
	mdata->q[1]=((int16_t)(raw_data[2]<<8)|(raw_data[3]))/10000.f;
	mdata->q[2]=((int16_t)(raw_data[4]<<8)|(raw_data[5]))/10000.f;
	mdata->q[3]=((int16_t)(raw_data[6]<<8)|(raw_data[7]))/10000.f;
}
void mpu_acc_reci(uint8_t raw_data[8],MPU_Data *mdata)
{
	mdata->accx=((int16_t)(raw_data[1]<<8)|(raw_data[0]))/1000.f;
	mdata->accy=((int16_t)(raw_data[3]<<8)|(raw_data[2]))/1000.f;
}

void mpu_spe_reci(uint8_t raw_data[8],MPU_Data *mdata)
{
	mdata->pitspeed=-((int16_t)(raw_data[5]<<8)|(raw_data[4]))/10.f;
	mdata->yawspeed=-((int16_t)(raw_data[1]<<8)|(raw_data[0]))/10.f;
}
void mpu_ang_reci(uint8_t raw_data[8],MPU_Data *mdata)
{
	mdata->yawangle=((int16_t)(raw_data[5]<<8)|(raw_data[4]))/100.f;
	mdata->pitangle=-((int16_t)(raw_data[3]<<8)|(raw_data[2]))/100.f;
	MPU_ready=1;
}

void mpu_angle_calc(MPU_Data *mdata)
{
	quar_rota_calc(mdata->instangle[0],90.f,mdata->q);
	quar_rota_calc(mdata->instangle[1],90.f,mdata->q);
	mdata->yawangle = atan2f(2.0f*(mdata->q[0]*mdata->q[3]+mdata->q[1]*mdata->q[2]), 2.0f*(mdata->q[0]*mdata->q[0]+mdata->q[1]*mdata->q[1])-1.0f);
  mdata->pitangle = asinf(-2.0f*(mdata->q[1]*mdata->q[3]-mdata->q[0]*mdata->q[2]));	
}

void mpucanbaud_set(int32_t baudrate,int16_t id,CAN_HandleTypeDef hcanx)
{
    uint32_t send_mail_box;
    CAN_tx.StdId = 0x600|id;
    CAN_tx.IDE = CAN_ID_STD;
    CAN_tx.RTR = CAN_RTR_DATA;
    CAN_tx.DLC = 0x08;
    CAN_tx_message[0] = 0x23;
    CAN_tx_message[1] = 0x00 ;
    CAN_tx_message[2] = 0x21;
    CAN_tx_message[3] = 0x00;
    CAN_tx_message[4] = baudrate ;
    CAN_tx_message[5] = baudrate >> 8;
    CAN_tx_message[6] = baudrate >> 16;
    CAN_tx_message[7] = baudrate >> 24;
		HAL_CAN_AddTxMessage(&hcanx, &CAN_tx, CAN_tx_message, &send_mail_box);
}

void mpucanid_set(int32_t tarid,int16_t id,CAN_HandleTypeDef hcanx)
{
    uint32_t send_mail_box;
    CAN_tx.StdId = 0x600|id;
    CAN_tx.IDE = CAN_ID_STD;
    CAN_tx.RTR = CAN_RTR_DATA;
    CAN_tx.DLC = 0x08;
    CAN_tx_message[0] = 0x23;
    CAN_tx_message[1] = 0x00 ;
    CAN_tx_message[2] = 0x21;
    CAN_tx_message[3] = 0x00;
    CAN_tx_message[4] = tarid ;
    CAN_tx_message[5] = tarid >> 8;
    CAN_tx_message[6] = tarid >> 16;
    CAN_tx_message[7] = tarid >> 24;
		HAL_CAN_AddTxMessage(&hcanx, &CAN_tx, CAN_tx_message, &send_mail_box);
}

void mpucanreportfreq_set(int32_t freq,int16_t id,CAN_HandleTypeDef hcanx,int8_t dataname)
{
    uint32_t send_mail_box;
    CAN_tx.StdId = 0x600|id;
    CAN_tx.IDE = CAN_ID_STD;
    CAN_tx.RTR = CAN_RTR_DATA;
    CAN_tx.DLC = 0x08;
    CAN_tx_message[0] = 0x2B;
    CAN_tx_message[1] = dataname ;
    CAN_tx_message[2] = 0x18;
    CAN_tx_message[3] = 0x05;
    CAN_tx_message[4] = (1000/freq) ;
    CAN_tx_message[5] = (1000/freq) >> 8;
    CAN_tx_message[6] = 0x00;
    CAN_tx_message[7] = 0x00;
		HAL_CAN_AddTxMessage(&hcanx, &CAN_tx, CAN_tx_message, &send_mail_box);
}


