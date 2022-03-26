#include "main.h"

CapsInfo capsinfo;

void capsinfo_unpack(CapsInfo *caps,uint8_t rx[8])
{
	caps->inputvoltage=rx[0]|rx[1]<<8;
	caps->capsvoltage=rx[0]|rx[1]<<8;
	caps->inputcurrent=rx[0]|rx[1]<<8;
	caps->tarpower=rx[0]|rx[1]<<8;
}

void caspctrl()
{
	for(;;)
	{
		int16_t capsmes[4];
		if(chasinfo.cur.powerbuffer<50)
			capsmes[0]=chasinfo.cur.powerlimit;
		else
			capsmes[0]=chasinfo.cur.powerlimit*1.5f;
		CAN_send(0x210,hcan2,capsmes);
		osDelay(100);
	}
}
