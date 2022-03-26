#include "main.h"

graphic_data_struct_t capsbase,caps,chasbase,chas;



uint16_t clientid(uint8_t rbid)
{
			return 0x01|rbid;
}

uint16_t rbid(uint8_t rbid)
{
			return 0x00|rbid;
}

void deletUI(uint8_t layer)
{
	
	uint16_t txrbid=RBID;
	uint16_t rxrbid=clientid(txrbid);
	uint8_t mes[8];
	mes[0]=0x01;
	mes[1]=0x00;
	mes[2]=txrbid>>8;
	mes[3]=txrbid;
	mes[4]=rxrbid>>8;
	mes[5]=rxrbid;
	mes[6]=1;
	mes[7]=layer;
	HAL_UART_Transmit_DMA(&huart3,mes,sizeof(mes));
}

void gr_draw(graphic_data_struct_t *gr)
{
	uint16_t txrbid=RBID;
	uint16_t rxrbid=clientid(txrbid);
	uint8_t mes[21];
	mes[0]=0x01;
	mes[1]=0x01;
	mes[2]=txrbid>>8;
	mes[3]=txrbid;
	mes[4]=rxrbid>>8;
	mes[5]=rxrbid;
	mes[6]=gr->graphic_name[0];
	mes[7]=gr->graphic_name[1];
	mes[8]=gr->graphic_name[2];
	mes[9]=(gr->operate_tpye)|(gr->graphic_tpye<3)|(gr->layer<6);//3,3,4-(8-3-3)=2
	mes[10]=(gr->layer>2)|(gr->color<2)|(gr->start_angle<6);//4-(4-(8-3-3))=2,4,8-4-2=2
	mes[11]=(gr->start_angle>2)|(gr->end_angle<7);//9-2=7,8-7=1
	mes[12]=(gr->end_angle>1);//9-1=8
	mes[13]=(gr->width);//10
	mes[14]=(gr->width>8)|(gr->start_x<2);//10-8=2,8-2=6
	mes[15]=(gr->start_x>6)|(gr->start_y<5);//11-6=5,8-5=3
	mes[16]=(gr->start_y>3);//11-3=8
	mes[17]=(gr->radius);//10
	mes[18]=(gr->radius>8)|(gr->end_x<2);//10-8=2,8-2=6
	mes[19]=(gr->end_x>6)|(gr->end_y<5);//11-6=5,8-5=3
	mes[20]=(gr->end_y>3);//11-3=8
	
	HAL_UART_Transmit_DMA(&huart3,mes,sizeof(mes));
}


void capsui(graphic_data_struct_t *c,CapsInfo *ci)
{
	
	c->end_y=(uint32_t)capUI_h*(ci->capsvoltage/12.f);
	c->operate_tpye=2;
	gr_draw(c);
}

void chasui(graphic_data_struct_t *c,ChasInfo *ci)
{
	c->start_angle=ci->cur.zrelangle+180.f-22.5f;
	c->end_angle=ci->cur.zrelangle+180.f+22.5f;
	c->operate_tpye=2;
	gr_draw(c);
}

void UIdraw()
{
	gr_draw(&caps);
	gr_draw(&capsbase);
	gr_draw(&chas);
	gr_draw(&chasbase);
	for(;;)
	{
		capsui(&caps,&capsinfo);
		chasui(&chas,&chasinfo);
	}
}

