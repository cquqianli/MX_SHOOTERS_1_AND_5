#include "main.h"

MotorInfo pitinfo=pitinfo_default_config,yawinfo=yawinfo_default_config;
PID_regulator pitanglepid=pit_angle_pid,pitspeedpid=pit_speed_pid,	\
													yawanglepid=yaw_angle_pid,yawspeedpid=yaw_speed_pid;



void gimbmotinfo_compl(MotorInfo *pit,	\
												MotorInfo *yaw, \
												RoboCtrlInfo *rbinfo)
{
	pit->tarmotorinfo.angle=rbinfo->gimb.pitangle;
	pit->tarmotorinfo.speed=pitmaxspeed;

	
	yaw->tarmotorinfo.angle=rbinfo->gimb.yawangle;
	yaw->tarmotorinfo.speed=yawmaxspeed;

}

void gimbmotpid_calc(MotorInfo *pit, \
								 		MotorInfo *yaw, \
										MPU_Data *mpdata, \
									 	PID_regulator *papid, \
								 		PID_regulator *pspid, \
								 		PID_regulator *yapid, \
								 		PID_regulator *yspid)
{
	
	if(pit->tempdata.pidcount<pit->parameter.pidoutcycrate&&pit->tempdata.pidcount>=0)
		pit->tempdata.pidcount++;
	else
		pit->tempdata.pidcount=0;
	
	if(yaw->tempdata.pidcount<yaw->parameter.pidoutcycrate&&yaw->tempdata.pidcount>=0)
		yaw->tempdata.pidcount++;
	else
		yaw->tempdata.pidcount=0;
	
	if(pit->tempdata.pidcount==pit->parameter.pidoutcycrate)
	{
		
		papid->tar=pit->tarmotorinfo.angle;
		papid->cur=mpdata->pitangle;
		papid->outputMax=pit->tarmotorinfo.speed;
		PID_angle_calc(papid,1,180);
		pit->tempdata.pidcount=0;
	}
	
	if(yaw->tempdata.pidcount==yaw->parameter.pidoutcycrate)
	{
		
		yapid->tar=yaw->tarmotorinfo.angle;
		yapid->cur=mpdata->yawangle;
		yapid->outputMax=yaw->tarmotorinfo.speed;
		PID_angle_calc(yapid,1,180);
		yaw->tempdata.pidcount=0;
	}
		
		yspid->tar=yapid->output;
		yspid->cur=mpdata->yawspeed;
		PID_calc(yspid,1);
	
		pspid->tar=papid->output;
		pspid->cur=mpdata->pitspeed;
		PID_calc(pspid,1);
}

void gimbctrl(void)
{
	pitanglepid.kp=5;
	pitanglepid.ki=0;
	pitanglepid.kd=0;
	pitspeedpid.kp=80;
	pitspeedpid.ki=0.005;
	pitspeedpid.kd=5;
	
	yawanglepid.kp=15;
	yawanglepid.ki=0;
	yawanglepid.kd=3;
	yawspeedpid.kp=200;
	yawspeedpid.ki=0.08;
	yawspeedpid.kd=5;
	for(;;)
	{
		gimbmotinfo_compl(&pitinfo,&yawinfo,&roboctrlinfo);
		gimbmotpid_calc(&pitinfo,&yawinfo,&mpudata,&pitanglepid,&pitspeedpid,&yawanglepid,&yawspeedpid);
		
		if(roboctrlinfo.gimb.status!=0xFF)
		{	
			mestocan1_0x1ff_pack(mestocan1_0x1ff);
			
		}
		else
	  {
			zero_pack(mestocan1_0x1ff);
		}
		CAN_send(0x1ff,hcan1,mestocan1_0x1ff);
		osDelayUntil(taskperi);
	}
		
}
