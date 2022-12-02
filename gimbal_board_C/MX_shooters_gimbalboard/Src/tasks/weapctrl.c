#include "main.h"

MotorInfo fricinfo[2]={fric_default_config,fric_default_config},triginfo=trig_default_config,magainfo=maga_default_config;
PID_regulator fricspeedpid[2]={fric_default_pid,fric_default_pid},triganglepid=trig_angle_pid,trigspeedpid=trig_speed_pid,magaanglepid=maga_angle_pid,magaspeedpid=maga_speed_pid;



void weapmotinfo_compl(MotorInfo fr[2],	\
												MotorInfo *tr, \
												MotorInfo *ma, \
												RoboCtrlInfo *rbinfo)
{
	if(rbinfo->weap.status!=0x00||(RC_Data.rc.s[1]==3&&RC_Data.rc.s[0]==1))
	{
		fr[0].tarmotorinfo.speed=fricshootspeed*fricdirection;		
		fr[1].tarmotorinfo.speed=-fr[0].tarmotorinfo.speed;
	}
	else
	{
		fr[0].tarmotorinfo.speed=0;		
		fr[1].tarmotorinfo.speed=0;
	}
	
	if(rbinfo->weap.status==0x01)
	{
		tr->tarmotorinfo.angle-=360.f/forknum;
		rbinfo->weap.status=0x10;
		
	}
	#ifdef infa
	if(rbinfo->weap.maglid==0x01)
	{
		if(ma->tempdata.currentsum/5.f<=ma->parameter.inpositioncurrent)
		{
			ma->tarmotorinfo.angle+=magaspeed/60.f*360.f/taskfreq*magadirection;
		}
		else 
		{
			ma->tarmotorinfo.angle=ma->tempdata.angle;
			rbinfo->weap.maglid=0x00;
		}
	}
	
	if(rbinfo->weap.maglid==0x11)
	{
		if(ma->tempdata.currentsum/5.f<=ma->parameter.inpositioncurrent)
		{
			ma->tarmotorinfo.angle-=magaspeed/60.f*360.f/taskfreq*magadirection;
		}
		else 
		{
			ma->tarmotorinfo.angle=ma->tempdata.angle;
			rbinfo->weap.maglid=0x10;
		}
	}
	#endif
	
	
}

void weapmotpid_calc(MotorInfo fr[2],	\
											MotorInfo *tr, \
											PID_regulator fspid[2], \
											PID_regulator *tapid, \
											PID_regulator *tspid,
											PID_regulator *mapid, \
											PID_regulator *mspid)
{
	fspid[0].tar=fr[0].tarmotorinfo.speed;
	fspid[0].cur=fr[0].curmotorinfo.speed;
	fspid[1].tar=fr[1].tarmotorinfo.speed;
	fspid[1].cur=fr[1].curmotorinfo.speed;
	PID_calc(&fspid[0],1);
	PID_calc(&fspid[1],1);

	motaspid_calc(tr,tapid,tspid);
};

void weapctrl(void)
{
	fricspeedpid[0].kp=0;
	fricspeedpid[0].ki=0;
	fricspeedpid[0].kd=0;
	fricspeedpid[1].kp=0;
	fricspeedpid[1].ki=0;
	fricspeedpid[1].kd=0;
	
	triganglepid.kp=0;
	triganglepid.ki=0;
	triganglepid.kd=0;
	trigspeedpid.kp=0;
	trigspeedpid.ki=0;
	trigspeedpid.kd=0;
	
	
	
	for(;;)
	{
		weapmotinfo_compl(fricinfo,&triginfo,&magainfo,&roboctrlinfo);
		weapmotpid_calc(fricinfo,&triginfo,fricspeedpid,&triganglepid,&trigspeedpid,&magaanglepid,&magaspeedpid);
		if(roboctrlinfo.gimb.status!=0xFF)
		{	
			mestocan2_0x200_pack(mestocan2_0x200);
		
			
		}
		else
		{
			zero_pack(mestocan2_0x200);

		}
		CAN_send(0x200,hcan2,mestocan2_0x200);
		osDelayUntil(taskperi);
	}
}
