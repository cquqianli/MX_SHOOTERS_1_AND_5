#include "main.h"

MPU_Data mpudata;
MPU_Data mpulastdata;

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
	mdata->q[0]=(float)((raw_data[0]<<8)|(raw_data[1]))/10000.f;
	mdata->q[1]=(float)((raw_data[2]<<8)|(raw_data[3]))/10000.f;
	mdata->q[2]=(float)((raw_data[4]<<8)|(raw_data[5]))/10000.f;
	mdata->q[3]=(float)((raw_data[6]<<8)|(raw_data[7]))/10000.f;
}
void mpu_acc_reci(uint8_t raw_data[8],MPU_Data *mdata)
{
	mdata->accx=(float)((raw_data[0]<<8)|(raw_data[1]));
	mdata->accy=(float)((raw_data[2]<<8)|(raw_data[3]));
}
void mpu_spe_reci(uint8_t raw_data[8],MPU_Data *mdata)
{
	mdata->yawspeed=(float)((raw_data[0]<<8)|(raw_data[1]));
	mdata->pitspeed=(float)((raw_data[2]<<8)|(raw_data[3]));
}

void mpu_angle_calc(MPU_Data *mdata)
{
	quar_rota_calc(mdata->instangle[0],90.f,mdata->q);
	quar_rota_calc(mdata->instangle[1],90.f,mdata->q);
	mdata->yawangle = atan2f(2.0f*(mdata->q[0]*mdata->q[3]+mdata->q[1]*mdata->q[2]), 2.0f*(mdata->q[0]*mdata->q[0]+mdata->q[1]*mdata->q[1])-1.0f);
  mdata->pitangle = asinf(-2.0f*(mdata->q[1]*mdata->q[3]-mdata->q[0]*mdata->q[2]));	
}

