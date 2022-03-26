#include "main.h"

MotorInfo fricinfo[2],triginfo,magainfo;
PID_regulator fricspeedpid[2],triganglepid,trigspeedpid,magaanglepid,magaspeedpid;

void weapmotinfo_compl(MotorInfo fr[2],	\
												MotorInfo *tr, \
												MotorInfo *ma, \
												RoboCtrlInfo *rbinfo)
{
	if(rbinfo->weap.status!=0x00)
	{
		fr[0].tarmotorinfo.speed=fricshootspeed*fricdirection;		
		fr[1].tarmotorinfo.speed=-fr[0].tarmotorinfo.speed;
	}
	
	if(rbinfo->weap.status==0x01)
	{
		tr->tarmotorinfo.angle+=360.f/forknum;
		rbinfo->weap.status=0x10;
	}
	
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
	fspid[0].tar=fr[0].tarmotorinfo.speed;
	
	fspid[1].tar=fr[1].tarmotorinfo.speed;
	fspid[1].tar=fr[1].tarmotorinfo.speed;
	
	PID_calc(&fspid[0],1);
	PID_calc(&fspid[1],1);
	
	motaspid_calc(tr,tapid,tspid);
};

void weapctrl(void)
{
	for(;;)
	{
		weapmotinfo_compl(fricinfo,&triginfo,&magainfo,&roboctrlinfo);
		weapmotpid_calc(fricinfo,&triginfo,fricspeedpid,&triganglepid,&trigspeedpid,&magaanglepid,&magaspeedpid);
		osDelay(2);
	}
}
