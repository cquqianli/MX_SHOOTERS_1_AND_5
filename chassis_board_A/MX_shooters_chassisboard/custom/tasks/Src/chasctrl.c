#include "main.h"

ChasInfo chasinfo=chasis_default_config,chaslastinfo=chasis_default_config;
MotorInfo wheelinfo[4]={wheel_default_config,wheel_default_config,wheel_default_config,wheel_default_config},yawinfo=yawinfo_default_config;
PID_regulator wheelspeedpid[4]={wheel_default_pid,wheel_default_pid,wheel_default_pid,wheel_default_pid},spinpid=spin_default_pid;
float yawzeroangle[2];
//kshaper_handle xyspeed[2];

/* 
			//=======\\				   //=======\\
	  \\3\\	    	\\________//       //2//
  	\\3\\——||-  |++++++++++|  -||——//2//
	  \\3\\——||-  |++++++++++|  -||——//2//
	  \\3\\   ||___|++++++++++|___||  //2//
			 __	±±±±±±±±±±±±±±±±±±±±±±±± __
			|=|	|--\ |--\ /--\  /\  |--\ |=|
			|=|	|  | |  | |    /  \ |  | |=|
			|=| |--< |--< |    |==| <--/ |=|
			|=|	|  | |  | |    /  \ |\ 	 |=|
			|=|	|--/ |--/ \--//    \| \_ |=|
			 ——	±±±±±±±±±±±±±±±±±±±±±±±± ——
	  //4//  ||   |++++++++++|   ||  \\1\\
	  //4//——||-  |++++++++++|  -||——\\1\\
	  //4//——||-  |±±±±±±±±±±|  -||——\\1\\
	  //4//	  	  ||        ||       \\1\\
	 \\==========//          \\==========//
 还没想好怎么写，先给带火画个新B（u）B（ing）CAR的底盘吧
 
作者：LPGUAIA
日期：2021.7.11
*/


void yawzero_clac(MotorInfo *yinfo,ChasInfo *ch,float yza[2],uint16_t GPIO_Pin)
{
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_Pin)==GPIO_PIN_SET)
	{
		yza[0]=yinfo->curmotorinfo.angle;
		yza[1]=0;
	}
	else if(HAL_GPIO_ReadPin(GPIOD,GPIO_Pin)==GPIO_PIN_RESET)
	{
		yza[1]=yinfo->curmotorinfo.angle;
		yinfo->parameter.installationangle=(yza[1]+yza[0])/2.f;
		//ch->cur.zrelangle=yinfo->curmotorinfo.angle-yinfo->parameter.installationangle;
		yza[0]=0;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	yawzero_clac(&yawinfo,&chasinfo,yawzeroangle,GPIO_Pin);
}

void zangletozspeed_calc(ChasInfo *ch,PID_regulator *sppid)
{
	
//	sppid->tar=ch->tar.zrelangle;
//	sppid->cur=ch->cur.zrelangle;
//	sppid->outputMax=rotspeedSV+rotspeedPPV;
//	PID_angle_calc(sppid,1,180);
	ch->tar.zspeed=-ch->tar.zrelangle;
}

void xyztowheelspeed_calc(ChasInfo *ch,MotorInfo whinfo[4])
{
	

	whinfo[0].tarmotorinfo.speed = - ch->tar.xspeed - ch->tar.yspeed + ch->tar.zspeed;
	whinfo[1].tarmotorinfo.speed = - ch->tar.xspeed + ch->tar.yspeed + ch->tar.zspeed;
	whinfo[2].tarmotorinfo.speed = ch->tar.xspeed + ch->tar.yspeed + ch->tar.zspeed;
	whinfo[3] .tarmotorinfo.speed= ch->tar.xspeed - ch->tar.yspeed + ch->tar.zspeed;
//		whinfo[0].tarmotorinfo.speed = - ch->tar.xspeed - ch->tar.yspeed ;
//		whinfo[1].tarmotorinfo.speed = - ch->tar.xspeed + ch->tar.yspeed ;
//		whinfo[2].tarmotorinfo.speed = ch->tar.xspeed + ch->tar.yspeed ;
//		whinfo[3] .tarmotorinfo.speed= ch->tar.xspeed - ch->tar.yspeed ;
}

void wheelspeedpid_calc(MotorInfo whinfo[4],PID_regulator wspid[4] )
{
	for(int8_t i=0;i<4;i++)
	{
		wspid[i].tar=whinfo[i].tarmotorinfo.speed;
		wspid[i].cur=whinfo[i].curmotorinfo.speed;
		PID_calc(&wspid[i],1);
	}
}

void powerlimit(MotorInfo whinfo[4],ChasInfo *ch,CapsInfo *caps,PID_regulator wspid[4])
{
	float wheelpower=0;
	float wheelcureentsum=0;
	float pidcurrentsum=0;
	for(int8_t i=0;i<4;i++)
	{
		wheelcureentsum+=ABS(whinfo[i].curmotorinfo.current[0]);
	}
	wheelpower=wheelcureentsum*caps->capsvoltage;
	if(caps->capsvoltage<=12)
		ch->tar.powerlimit=ch->cur.powerlimit*0.75f;
	
	if(ch->tar.powerlimit<wheelpower)
	{
		for(int8_t i=0;i<4;i++)
		{
			pidcurrentsum+=ABS(wspid[i].output);
		}
		for(int8_t i=0;i<4;i++)
		{
			wspid[i].output=wspid[i].output/pidcurrentsum*ch->tar.powerlimit/caps->capsvoltage;
		}
	}

}

void chasctrl()
{
	for(int8_t i=0;i<4;i++)
	{
		wheelspeedpid[i].kp=40;
		wheelspeedpid[i].ki=0.000;
		wheelspeedpid[i].kd=1;
	}
	spinpid.kp=5;
	
	spinpid.kd=0;
	for(;;)
	{
		zangletozspeed_calc(&chasinfo,&spinpid);
		xyztowheelspeed_calc(&chasinfo,wheelinfo);
		wheelspeedpid_calc(wheelinfo,wheelspeedpid);
		powerlimit(wheelinfo,&chasinfo,&capsinfo,wheelspeedpid);
		osDelayUntil(taskperi);
	}
}
