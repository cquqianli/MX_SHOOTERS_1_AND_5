#include "main.h"

CapsInfo capsinfo=scapsinfo_default_config;

void capsinfo_unpack(CapsInfo *caps,uint8_t rx[8])
{
	caps->inputvoltage=((int16_t)(rx[0]|rx[1]<<8))/100.f;
	caps->capsvoltage=((int16_t)(rx[2]|rx[3]<<8))/100.f;
	caps->inputcurrent=((int16_t)(rx[4]|rx[5]<<8))/100.f;
	caps->tarpower=((int16_t)(rx[6]|rx[7]<<8))/100.f;
}

void capsctrl()
{
	for(;;)
	{
		int16_t capsmes[4]={0,0,0,0};
		if(chasinfo.cur.powerbuffer<50)
			capsmes[0]=chasinfo.cur.powerlimit*100.f;
		else
			capsmes[0]=chasinfo.cur.powerlimit*1.5f*100.f;
//		capsmes[0]=8000.f;
		CAN_send(0x210,hcan1,capsmes);
		osDelayUntil(100);
	}
}
