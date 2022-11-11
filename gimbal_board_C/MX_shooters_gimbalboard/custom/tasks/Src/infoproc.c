#include "main.h"

int16_t mestogimb[2]={0,},curmestochas[4]={0,},ctrlmestochas[4]={0,},mestocan1_0x1ff[4]={0,},mestocan2_0x1ff[4]={0,},mestocan1_0x200[4]={0,},mestocan2_0x200[4]={0,};

RoboCtrlInfo roboctrlinfo=roboctrl_default_config;
RoboCurInfo robocurinfo;

int ta=0;
int tb=0;

void rc_rbctrl_status_compl(RC_DATA *rc_data,RC_DATA *rc_last_data,KEY *key,KEY *last_key,RoboCtrlInfo *rbinfo)
{
	//weapon
	static uint16_t rfcount;
	
	
	
	if(rc_data->rc.s[0]==0x01&&rc_data->rc.s[1]==0x01)
	{
		rbinfo->weap.status=0x00;
	}
	if(rc_data->rc.s[0]==0x01&&(rc_data->rc.s[1]==0x02&&rc_last_data->rc.s[1]==0x03))
	{
		rbinfo->weap.status=0x01;
		ta++;
	}
	if((rc_data->rc.s[0]==0x01&&(rc_data->rc.s[1]==0x02&&rc_last_data->rc.s[1]==0x02))||(rc_data->mouse.press_l==1&&rc_last_data->mouse.press_l==1))
		rfcount++;
	else  
		rfcount=0;
	if(rfcount==taskfreq/maxshootfreq)
	{
		rbinfo->weap.status=0x01;
		rfcount=0;
	}
	
	if(key->key_r==1&&rbinfo->weap.maglid!=0x00)
	{
		rbinfo->weap.maglid=0x01;
	}
	else if(rbinfo->weap.maglid!=0x10)
	{
		rbinfo->weap.maglid=0x11;
	}
	//gimbal
	if(rc_data->rc.s[0]==0x03&&rc_data->rc.s[1]==0x01)
	{
		rbinfo->gimb.status=0x00;
	}
	if((rc_data->rc.s[0]==0x03&&rc_data->rc.s[1]==0x02)||rc_data->mouse.press_l==0x01)
	{
		rbinfo->gimb.status=0x01;
	}
	//chassis
	if(rc_data->rc.s[0]==0x02&&rc_data->rc.s[1]==0x01)
	{
		rbinfo->chas.status=(rbinfo->chas.status>>4)<<4;
	}
	if(rc_data->rc.s[0]==0x02&&rc_data->rc.s[1]==0x02)
	{
		rbinfo->chas.status|=0x1;
	}
	
	if(((rc_data->rc.s[0]==0x02&&rc_data->rc.s[1]==0x03&&rc_last_data->rc.s[1]!=0x03)))
	{
		uint8_t st=((rbinfo->chas.status<<4));
		st=(st>>4);
		rbinfo->chas.status=(((rbinfo->chas.status>>4)+0x01)<<4)|st;
		if((rbinfo->chas.status>>4)>0x02)
			rbinfo->chas.status=st;
		
	}
	else if(key->key_ctrl==1)
	{
		rbinfo->chas.status=((rbinfo->chas.status<<4)>>4)|0x20;
	}
	else if(key->key_shift==1)
	{
		rbinfo->chas.status=((rbinfo->chas.status<<4)>>4)|0x10;
	}

	
	//motoroff
	if(rc_data->rc.s[0]==0x03&&rc_data->rc.s[1]==0x03)
	{
		rbinfo->gimb.status=0xFF;
		rbinfo->chas.status=0xFF;
	}
}
void rc_rbctrl_movedata_compl(RC_DATA *rc_data,RC_DATA *rc_last_data,KEY *key,KEY *last_key,RoboCtrlInfo *rbinfo)
{
	//weapon
	
	//gimbal
	float yawanglec=rc_data->mouse.x-rc_data->rc.ch[0]/660.f/taskfreq*6;
	float pitanglec=rc_data->mouse.y+rc_data->rc.ch[1]/660.f/taskfreq*2;
	if(pitanglec+rbinfo->gimb.pitangle<pitmaxangle&&pitanglec+rbinfo->gimb.pitangle>pitminangle)
	{
		rbinfo->gimb.pitangle+=pitanglec;
	}
	else if(pitanglec+rbinfo->gimb.pitangle>pitmaxangle)
		rbinfo->gimb.pitangle=pitmaxangle;
	else if(pitanglec+rbinfo->gimb.pitangle<pitminangle)
		rbinfo->gimb.pitangle=pitminangle;
	rbinfo->gimb.yawangle=anglecircle(rbinfo->gimb.yawangle+yawanglec);
	
	//chassis
	
	rbinfo->chas.xspeed=key->key_d*500.f-key->key_a*500.f+rc_data->rc.ch[3]/660.f*500.f;
	rbinfo->chas.yspeed=key->key_w*500.f-key->key_s*500.f+rc_data->rc.ch[2]/660.f*500.f;
//	if(key->key_q==1&&last_key->key_q==0)
//		rbinfo->chas.zrelangle=anglecircle(45+rbinfo->chas.zrelangle);
//	if(key->key_e==1&&last_key->key_e==0)
//		rbinfo->chas.zrelangle=anglecircle(45-rbinfo->chas.zrelangle);
	
	rbinfo->chas.zrelangle=rc_data->rc.ch[4];
	
	
}

void ctrlmestochas_pack(RoboCtrlInfo *rbinfo,int16_t mespacked[4])
{
	mespacked[0]=(int16_t)rbinfo->chas.status;	
	mespacked[1]=(int16_t)rbinfo->chas.xspeed;
	mespacked[2]=(int16_t)rbinfo->chas.yspeed;
	mespacked[3]=(int16_t)rbinfo->chas.zrelangle;
}

void curmestochas_pack(RoboCurInfo *rbcurinfo,int16_t mespacked[4])
{
	mespacked[0]=(int16_t)rbcurinfo->xspeed;	
	mespacked[1]=(int16_t)rbcurinfo->yspeed;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}

void mestocan1_0x1ff_pack(int16_t mespacked[4])
{

	mespacked[0]=(int16_t)0x0000;	
	//mespacked[1]=(int16_t)(-yawspeedpid.output);
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
	mespacked[0]=(int16_t)fricspeedpid[0].output;	
	mespacked[1]=(int16_t)fricspeedpid[1].output;
	//mespacked[2]=-(int16_t)pitspeedpid.output;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan1_0x2ff_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)0x0000;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan2_0x2ff_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)0x0000;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void zero_pack(int16_t mespacked[4])
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
//		mpucanbaud_set(1000000,8,hcan1);
//		mpucanreportfreq_set(500,8,hcan1,angledata);
//		mpucanreportfreq_set(500,8,hcan1,speeddata);
//		mpucanreportfreq_set(500,8,hcan1,accdata);
		

		rc_rbctrl_status_compl(&RC_Data,&RC_Last_Data,&Key,&Last_Key,&roboctrlinfo);
		rc_rbctrl_movedata_compl(&RC_Data,&RC_Last_Data,&Key,&Last_Key,&roboctrlinfo);	
		RC_Last_Data=RC_Data;
		
		ctrlmestochas_pack(&roboctrlinfo,ctrlmestochas);
		CAN_send(0x123,hcan1,ctrlmestochas);
		osDelayUntil(taskperi);
		curmestochas_pack(&robocurinfo,curmestochas);
		CAN_send(0x321,hcan1,curmestochas);

	}
}
