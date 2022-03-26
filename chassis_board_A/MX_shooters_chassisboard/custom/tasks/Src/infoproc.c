#include "main.h"

int16_t mestocan1_0x1ff[4]={0,},mestocan2_0x1ff[4]={0,},mestocan1_0x200[4]={0,},mestocan2_0x200[4]={0,};

void chasinfo_compl(ChasInfo *ch,MotorInfo *yinfo)
{
	ch->cur.zrelangle=yinfo->curmotorinfo.angle-yinfo->parameter.installationangle;
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
			ch->tar.powerlimit=ch->cur.powerlimit/2;
		}break;
	}
	
	
}

void ctrlmestochas_unpack(ChasInfo *chinfo,uint8_t rx[8])
{
	chinfo->status=rx[1];	
	chinfo->tar.xspeed=rx[2]<<8|rx[3];
	chinfo->tar.yspeed=rx[4]<<8|rx[5];
	chinfo->tar.zrelangle=rx[6]<<8|rx[7];
}

void curmestochas_unpack(ChasInfo *chinfo,uint8_t rx[8])
{
	chinfo->cur.xspeed=rx[0]<<8|rx[1];	
	chinfo->cur.yspeed=rx[2]<<8|rx[3];
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
	mespacked[0]=(int16_t)0x0000;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}


void infoproc(void)
{
	for(;;)
	{
		chasinfo_compl(&chasinfo,&yawinfo);
		mestocan1_0x1ff_pack(mestocan1_0x1ff);
		mestocan2_0x1ff_pack(mestocan2_0x1ff);
		mestocan1_0x200_pack(mestocan1_0x200);
		mestocan2_0x200_pack(mestocan2_0x200);
		
		CAN_send(0x1ff,hcan1,mestocan1_0x1ff);
		CAN_send(0x200,hcan1,mestocan1_0x200);
		CAN_send(0x1ff,hcan2,mestocan2_0x1ff);
		CAN_send(0x200,hcan2,mestocan2_0x200);
		osDelay(2);
	}
}
