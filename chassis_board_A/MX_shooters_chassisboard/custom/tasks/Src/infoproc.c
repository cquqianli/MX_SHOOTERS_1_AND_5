#include "main.h"

int16_t mestocan1_0x1ff[4]={0,},mestocan2_0x1ff[4]={0,},mestocan1_0x200[4]={0,},mestocan2_0x200[4]={0,},curmestogimb[4]={0,},zero_pack[4]={0,0,0,0};
uint8_t GIMB_READY=0;
void chasinfo_compl(ChasInfo *ch,MotorInfo *yinfo)
{
	ch->cur.zrelangle=anglecircle(yinfo->curmotorinfo.angle-yinfo->parameter.installationangle-180.f);
	ch->cur.zspeed=yinfo->curmotorinfo.speed;
	get_chassis_power_and_buffer(&ch->cur.power,&ch->cur.powerbuffer,&ch->cur.powerlimit);
	switch(ch->status>>4)
	{
		case 0 :
		{
			ch->tar.powerlimit=ch->cur.powerlimit;
		}break;
		case 1 :
		{
			ch->tar.powerlimit=ch->cur.powerlimit*2;
		}break;
		case 2 :
		{
			ch->tar.xspeed=ch->tar.xspeed/2;
			ch->tar.yspeed=ch->tar.yspeed/2;
		}break;
	}
	
	//ch->tar.zrelangle=anglecircle(ch->tar.zrelangle+(ch->status<<4>>4)* taskperi/1000.f*(rotspeedPPV*cos(4.f*ch->cur.zrelangle/360.f*2.f*PI)+rotspeedSV));
	
	
}

void ctrlmestochas_unpack(ChasInfo *chinfo,ChasInfo *chlinfo,uint8_t rx[8])
{
	chinfo->status=rx[1];	
	chinfo->tar.xspeed=((int16_t)(rx[2]<<8|rx[3]));
	chinfo->tar.yspeed=((int16_t)(rx[4]<<8|rx[5]));
//	float tempxy[2]={chinfo->tar.xspeed,chinfo->tar.yspeed};
//	float anglematrix[2][2]={{cos(chinfo->cur.zrelangle/360.f*2.f*PI),sin(chinfo->cur.zrelangle/360.f*2.f*PI)}, \
//													 {-sin(chinfo->cur.zrelangle/360.f*2.f*PI),cos(chinfo->cur.zrelangle/360.f*2.f*PI)}};
//	
//	chinfo->tar.xspeed=tempxy[0]*anglematrix[0][0]+tempxy[1]*anglematrix[0][1];
//	chinfo->tar.yspeed=tempxy[0]*anglematrix[1][0]+tempxy[1]*anglematrix[1][1];
	chinfo->tar.zrelangle=((int16_t)(rx[6]<<8|rx[7]));
	if(ABS(chinfo->tar.xspeed-chlinfo->tar.xspeed)>500)
		chinfo->tar.xspeed=chlinfo->tar.xspeed;
	if(ABS(chinfo->tar.yspeed-chlinfo->tar.yspeed)>500)
		chinfo->tar.yspeed=chlinfo->tar.yspeed;
	if(ABS(chinfo->tar.zrelangle-chlinfo->tar.zrelangle)>500)
		chinfo->tar.zrelangle=chlinfo->tar.zrelangle;
}

void curmestochas_unpack(ChasInfo *chinfo,uint8_t rx[8])
{
	chinfo->cur.xspeed=rx[0]<<8|rx[1];	
	chinfo->cur.yspeed=rx[2]<<8|rx[3];
	
}

void curmestogimb_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)chasinfo.cur.zrelangle*100.f;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan1_0x1ff_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)0x0000;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan2_0x1ff_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)0x0000;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan1_0x200_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)0x0000;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan2_0x200_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)wheelspeedpid[0].output;	
	mespacked[1]=(int16_t)wheelspeedpid[1].output;
	mespacked[2]=(int16_t)wheelspeedpid[2].output;
	mespacked[3]=(int16_t)wheelspeedpid[3].output;
}


void infoproc(void)
{
	for(;;)
	{
		if(chasinfo.status!=0xFF)
		{
			chasinfo_compl(&chasinfo,&yawinfo);
			curmestogimb_pack(curmestogimb);
			CAN_send(0x234,hcan1,curmestogimb);
			osDelayUntil(taskperi);
			//mestocan1_0x1ff_pack(mestocan1_0x1ff);
			//mestocan2_0x1ff_pack(mestocan2_0x1ff);
			//CAN_send(0x1ff,hcan2,mestocan2_0x1ff);
			//mestocan1_0x200_pack(mestocan1_0x200);
			mestocan2_0x200_pack(mestocan2_0x200);
			CAN_send(0x200,hcan2,mestocan2_0x200);
			
			//CAN_send(0x1ff,hcan1,mestocan1_0x1ff);
			//CAN_send(0x200,hcan1,mestocan1_0x200);
		}
		else
		{
			CAN_send(0x1ff,hcan1,zero_pack);
			osDelayUntil(taskperi);
			CAN_send(0x200,hcan1,zero_pack);
			osDelayUntil(taskperi);
			CAN_send(0x1ff,hcan2,zero_pack);
			osDelayUntil(taskperi);
			CAN_send(0x200,hcan2,zero_pack);
		}
		
	}
}
