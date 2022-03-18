#include "main.h"

int16_t mestogimb[2]={0,},mestochas[4]={0,};

RoboCtrlInfo roboctrlinfo=roboctrl_default_config;

void mestogimb_rbctrl_compl(int16_t mes[2],RoboCtrlInfo *rbinfo)
{
	
}

void rc_rbctrl_status_compl(RC_DATA *rc_data,RC_DATA *rc_last_data,KEY *key,KEY *last_key,RoboCtrlInfo *rbinfo)
{
	//weapon
	if(rc_data->rc.s[0]==0x01&&rc_data->rc.s[1]==0x01)
	{
		rbinfo->weap.status=0x00;
	}
	if(rc_data->rc.s[0]==0x01&&(rc_data->rc.s[1]==0x03&&rc_last_data->rc.s[1]==0x02))
	{
		rbinfo->weap.status=0x01;
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
	float yawanglec=rc_data->mouse.x+rc_data->rc.ch[0];
	float pitanglec=rc_data->mouse.y+rc_data->rc.ch[1];
	if(pitanglec+rbinfo->gimb.pitangle<pitmaxangle&&pitanglec+rbinfo->gimb.pitangle>pitminangle)
	{
		rbinfo->gimb.pitangle+=pitanglec;
	}
	rbinfo->gimb.yawangle+=yawanglec;
	
	//chassis
	
	rbinfo->chas.xspeed=key->key_d*500-key->key_a*500+rc_data->rc.ch[2];
	rbinfo->chas.yspeed=key->key_w*500-key->key_s*500+rc_data->rc.ch[3];
	if(key->key_q==1&&last_key->key_q==0)
		rbinfo->chas.zrelangle+=45;
	if(key->key_e==1&&last_key->key_e==0)
		rbinfo->chas.zrelangle-=45;
	
	rbinfo->chas.zrelangle=rc_data->rc.ch[4]/660.f*300.f+ \
												 (rbinfo->chas.status<<4>>4)* \
												 anglecircle(taskperi*(rotspeedPPV*cos(4.f*rbinfo->chas.zrelangle/360*2.f*PI)+rotspeedPPV+rotspeedSV+rbinfo->chas.zrelangle));
	
	
}

void mestochas_pack(RoboCtrlInfo *rbinfo,int16_t mespacked[4])
{
	mespacked[0]=rbinfo->chas.status;
	
	#ifdef hero
	mespacked[0]=rbinfo->weap.status<<8|rbinfo->chas.status; //0x00:off 0x01:loading 0x10:ready for heros
	#endif
	mespacked[1]=(int16_t)rbinfo->chas.xspeed;
	mespacked[2]=(int16_t)rbinfo->chas.yspeed;
	mespacked[3]=(int16_t)rbinfo->chas.zrelangle;

}

void infoproc(void)
{
	for(;;)
	{
		mestogimb_rbctrl_compl(mestochas,&roboctrlinfo);
		rc_rbctrl_status_compl(&RC_Data,&RC_Last_Data,&Key,&Last_Key,&roboctrlinfo);
		rc_rbctrl_movedata_compl(&RC_Data,&RC_Last_Data,&Key,&Last_Key,&roboctrlinfo);
		mestochas_pack(&roboctrlinfo,mestochas);
		CAN_send(0x123,hcan1,mestochas);
	}
}
