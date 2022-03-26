#include "main.h"

int16_t mestogimb[2]={0,},curmestochas[4]={0,},ctrlmestochas[4]={0,},mestocan1_0x1ff[4]={0,},mestocan2_0x1ff[4]={0,},mestocan1_0x200[4]={0,},mestocan2_0x200[4]={0,};

RoboCtrlInfo roboctrlinfo=roboctrl_default_config;
RoboCurInfo robocurinfo;


void rc_rbctrl_status_compl(RC_DATA *rc_data,RC_DATA *rc_last_data,KEY *key,KEY *last_key,RoboCtrlInfo *rbinfo)
{
	//weapon
	static uint16_t rfcount;
	
	if(rc_data->rc.s[0]==0x01&&rc_data->rc.s[1]==0x01)
	{
		rbinfo->weap.status=0x00;
	}
	if(rc_data->rc.s[0]==0x01&&(rc_data->rc.s[1]==0x03&&rc_last_data->rc.s[1]==0x02))
	{
		rbinfo->weap.status=0x01;
	}
	if((rc_data->rc.s[0]==0x01&&(rc_data->rc.s[1]==0x03&&rc_last_data->rc.s[1]==0x03))||(rc_data->mouse.press_l==1&&rc_last_data->mouse.press_l==1))
		rfcount++;
	else  
		rfcount=0;
	if(rfcount==taskfreq/maxshootfreq)
		rbinfo->weap.status=0x01;
	
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
		rbinfo->chas.status=0x00;
	}
	if(rc_data->rc.s[0]==0x02&&rc_data->rc.s[1]==0x03)
	{
		rbinfo->chas.status=0x01;
	}
	if(key->key_shift==1||((rc_data->rc.s[0]==0x02&&rc_data->rc.s[1]==0x02)))
	{
		rbinfo->chas.status|=0x10;
	}
	else if(key->key_ctrl==1)
	{
		rbinfo->chas.status|=0x20;
	}
}
void rc_rbctrl_movedata_compl(RC_DATA *rc_data,RC_DATA *rc_last_data,KEY *key,KEY *last_key,RoboCtrlInfo *rbinfo)
{
	//weapon
	
	//gimbal
	float yawanglec=rc_data->mouse.x+rc_data->rc.ch[0]/660.f*yawmaxspeed/taskfreq;
	float pitanglec=rc_data->mouse.y+rc_data->rc.ch[1]/660.f*pitmaxspeed/taskfreq;
	if(pitanglec+rbinfo->gimb.pitangle<pitmaxangle&&pitanglec+rbinfo->gimb.pitangle>pitminangle)
	{
		rbinfo->gimb.pitangle+=pitanglec;
	}
	rbinfo->gimb.yawangle=anglecircle(rbinfo->gimb.yawangle+yawanglec);
	
	//chassis
	
	rbinfo->chas.xspeed=key->key_d*500-key->key_a*500+rc_data->rc.ch[2];
	rbinfo->chas.yspeed=key->key_w*500-key->key_s*500+rc_data->rc.ch[3];
	if(key->key_q==1&&last_key->key_q==0)
		rbinfo->chas.zrelangle=anglecircle(45+rbinfo->chas.zrelangle);
	if(key->key_e==1&&last_key->key_e==0)
		rbinfo->chas.zrelangle=anglecircle(45-rbinfo->chas.zrelangle);
	
	rbinfo->chas.zrelangle=rc_data->rc.ch[4]/660.f*300.f+ \
												 (rbinfo->chas.status<<4>>4)* \
												 anglecircle(taskperi*(rotspeedPPV*cos(4.f*rbinfo->chas.zrelangle/360*2.f*PI)+rotspeedPPV+rotspeedSV+rbinfo->chas.zrelangle));
	
	
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
	mespacked[0]=(int16_t)yawspeedpid.output;	
	mespacked[1]=(int16_t)pitspeedpid.output;
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
	mespacked[0]=(int16_t)trigspeedpid.output;	
	mespacked[1]=(int16_t)0x0000;
	mespacked[2]=(int16_t)0x0000;
	mespacked[3]=(int16_t)0x0000;
}
void mestocan2_0x200_pack(int16_t mespacked[4])
{
	mespacked[0]=(int16_t)fricspeedpid[0].output;	
	mespacked[1]=(int16_t)fricspeedpid[1].output;
	mespacked[2]=(int16_t)magaspeedpid.output;
	mespacked[3]=(int16_t)0x0000;
}


void infoproc(void)
{
	for(;;)
	{
		rc_rbctrl_status_compl(&RC_Data,&RC_Last_Data,&Key,&Last_Key,&roboctrlinfo);
		rc_rbctrl_movedata_compl(&RC_Data,&RC_Last_Data,&Key,&Last_Key,&roboctrlinfo);
		ctrlmestochas_pack(&roboctrlinfo,ctrlmestochas);
		curmestochas_pack(&robocurinfo,curmestochas);
		mestocan1_0x1ff_pack(mestocan1_0x1ff);
		//mestocan2_0x1ff_pack(mestocan2_0x1ff);
		//mestocan1_0x200_pack(mestocan1_0x200);
		mestocan2_0x200_pack(mestocan2_0x200);
		CAN_send(0x123,hcan1,ctrlmestochas);
		CAN_send(0x321,hcan1,curmestochas);
		CAN_send(0x1ff,hcan1,mestocan1_0x1ff);
		//CAN_send(0x200,hcan1,mestocan1_0x200);
		//CAN_send(0x1ff,hcan2,mestocan2_0x1ff);
		CAN_send(0x200,hcan2,mestocan2_0x200);
		osDelay(2);
	}
}
