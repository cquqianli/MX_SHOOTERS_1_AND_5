#include "main.h"

MotorInfo pitinfo,yawinfo;
PID_regulator pitanglepid,pitspeedpid,yawanglepid,yawspeedpid;



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
	for(;;)
	{
		gimbmotinfo_compl(&pitinfo,&yawinfo,&roboctrlinfo);
		gimbmotpid_calc(&pitinfo,&yawinfo,&mpudata,&pitanglepid,&pitspeedpid,&yawanglepid,&yawspeedpid);
		osDelay(2);
	}
		
}
