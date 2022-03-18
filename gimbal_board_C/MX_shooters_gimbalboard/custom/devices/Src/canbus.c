#include "main.h"

static CAN_TxHeaderTypeDef  CAN_tx;
static uint8_t              CAN_tx_message[8];

uint8_t CAN1_ready=0;
uint8_t CAN2_ready=0;

/*-------------------------------------
* 函数名：CAN初始化
* 描述  ：初始化CAN1/2
* 输入  ：无
* 输出  ：无
作者：LPGUAIA
日期：2021.9.20
-----------------------------------------*/ 
void can_filter_init(void)
{
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);


    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

/*-------------------------------------
* 函数名：CAN发送
* 描述  ：发送协议信息
* 输入  ：地址，hcan1/2，传输内容的结构体
* 输出  ：无
作者：LPGUAIA
日期：2021.9.20
-----------------------------------------*/ 
void CAN_send(uint32_t address,\
							CAN_HandleTypeDef hcanx,\
							int16_t message[4]
							)
{
    uint32_t send_mail_box;
    CAN_tx.StdId = address;
    CAN_tx.IDE = CAN_ID_STD;
    CAN_tx.RTR = CAN_RTR_DATA;
    CAN_tx.DLC = 0x08;
    CAN_tx_message[0] = message[0] >> 8;
    CAN_tx_message[1] = message[0] ;
    CAN_tx_message[2] = message[1] >> 8;
    CAN_tx_message[3] = message[1];
    CAN_tx_message[4] = message[2] >> 8;
    CAN_tx_message[5] = message[2];
    CAN_tx_message[6] = message[3] >> 8;
    CAN_tx_message[7] = message[3];
		HAL_CAN_AddTxMessage(&hcanx, &CAN_tx, CAN_tx_message, &send_mail_box);

}



/*-------------------------------------
* 函数名：CAN接收
* 描述  ：接收中断，先判断是can1/2的数据，根据地址接收，然后解算成代码内使用的单位
* 输入  ：无
* 输出  ：无
作者：LPGUAIA
日期：2021.9.20
-----------------------------------------*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

	if(hcan->Instance==CAN1)
	{
//		switch(rx_header.StdId)
//		{
//			case 0x201:
//			{
//					wheel[0].tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					wheel[0].tempdata.temp_angle[1] =wheel[0].tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&wheel[0]);
//					wheel[0].tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					wheel[0].tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
//					wheel[0].curmotorctrlinfo.speed = wheel[0].tempdata.speed;
//					wheel[0].curmotorctrlinfo.speed = wheel[0].curmotorctrlinfo.speed/wheel[0].parameter.reductiongearratio;
////					wheel[0].curmotorctrlinfo.current = wheel[0].tempdata.current;
////					wheel[0].curmotorctrlinfo.current =wheel[0].curmotorctrlinfo.current/10000*wheel[0].parameter.current_limit[1];
//				
//			}break;
//			case 0x202:
//			{
//					wheel[1].tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					wheel[1].tempdata.temp_angle[1] =wheel[1].tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&wheel[1]);
//					wheel[1].tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					wheel[1].tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
//					wheel[1].curmotorctrlinfo.speed = wheel[1].tempdata.speed;
//					wheel[1].curmotorctrlinfo.speed = wheel[1].curmotorctrlinfo.speed/wheel[1].parameter.reductiongearratio;
////					wheel[1].curmotorctrlinfo.current = wheel[1].tempdata.current;
////					wheel[1].curmotorctrlinfo.current =wheel[1].curmotorctrlinfo.current/10000*wheel[1].parameter.current_limit[1];
//			}break;
//			case 0x203:
//			{
//					wheel[2].tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					wheel[2].tempdata.temp_angle[1] =wheel[2].tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&wheel[2]);
//					wheel[2].tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					wheel[2].tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					wheel[2].curmotorctrlinfo.speed = wheel[2].tempdata.speed;
//					wheel[2].curmotorctrlinfo.speed = wheel[2].curmotorctrlinfo.speed/wheel[2].parameter.reductiongearratio;
////					wheel[2].curmotorctrlinfo.current = wheel[2].tempdata.current;
////					wheel[2].curmotorctrlinfo.current =wheel[2].curmotorctrlinfo.current/10000*wheel[2].parameter.current_limit[1];
//			}break;
//			case 0x204:
//			{
//					wheel[3].tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					wheel[3].tempdata.temp_angle[1] =wheel[3].tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&wheel[3]);
//					wheel[3].tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					wheel[3].tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
//					wheel[3].curmotorctrlinfo.speed = wheel[3].tempdata.speed;
//					wheel[3].curmotorctrlinfo.speed = wheel[3].curmotorctrlinfo.speed/wheel[3].parameter.reductiongearratio;
////					wheel[3].curmotorctrlinfo.current = wheel[3].tempdata.current;
////					wheel[3].curmotorctrlinfo.current =wheel[3].curmotorctrlinfo.current/10000*wheel[3].parameter.current_limit[1];
//			}break;

//			case 0x205:
//			{
//					yaw.tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					yaw.curmotorctrlinfo.angle =yaw.tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					yaw.curmotorctrlinfo.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					yaw.tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
////					yaw.curmotorctrlinfo.current = yaw.tempdata.current;
////					yaw.curmotorctrlinfo.current =yaw.curmotorctrlinfo.current/10000*yaw.parameter.current_limit[1];
//			}break;
//			
//		}
		//HAL_IWDG_Refresh(&hiwdg);
		CAN1_ready=1;
	}
	else if (hcan->Instance==CAN2)
	{
		switch(rx_header.StdId)
		{
//			case 0x201:
//			{
//					fric[0].tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					fric[0].tempdata.temp_angle[1] =fric[0].tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&fric[0]);
//					fric[0].tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					fric[0].tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
//					fric[0].curmotorctrlinfo.speed = fric[0].tempdata.speed;
//					fric[0].curmotorctrlinfo.speed = fric[0].curmotorctrlinfo.speed/fric[0].parameter.reductiongearratio;
//					fric[0].curmotorctrlinfo.current = fric[0].tempdata.current;
//					fric[0].curmotorctrlinfo.current =fric[0].curmotorctrlinfo.current/10000*fric[0].parameter.current_limit[1];
//			}break;
//			
//			case 0x202:
//			{
//					fric[1].tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					fric[1].tempdata.temp_angle[1] =fric[1].tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&fric[1]);
//					fric[1].tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					fric[1].tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
//					fric[1].curmotorctrlinfo.speed = fric[1].tempdata.speed;
//					fric[1].curmotorctrlinfo.speed = fric[1].curmotorctrlinfo.speed/fric[1].parameter.reductiongearratio;
////					fric[1].curmotorctrlinfo.current = fric[1].tempdata.current;
////					fric[1].curmotorctrlinfo.current =fric[1].curmotorctrlinfo.current/10000*fric[1].parameter.current_limit[1];
//			}break;
//			
//			
//			case 0x203:
//			{
//					trig.tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					trig.tempdata.temp_angle[1] =trig.tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					gearmotor_angledecoder(&trig);
//					trig.tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					trig.tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//					
//					trig.curmotorctrlinfo.speed = trig.tempdata.speed;
//					trig.curmotorctrlinfo.speed = trig.curmotorctrlinfo.speed/trig.parameter.reductiongearratio;
////					trig.curmotorctrlinfo.current = trig.tempdata.current;
////					trig.curmotorctrlinfo.current =trig.curmotorctrlinfo.current/10000*trig.parameter.current_limit[1];
//			}break;
//			
//			case 0x205:
//			{
////					pit.tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
////					pit.tempdata.temp_angle[1] =pit.tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
////					gearmotor_angledecoder(&pit);
////					pit.tempdata.speed = ((rx_data[2]<<8)|(rx_data[3]));
////					pit.tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
////					
////					pit.curmotorctrlinfo.speed = pit.tempdata.speed;
////					pit.curmotorctrlinfo.speed = pit.curmotorctrlinfo.speed/pit.parameter.reductiongearratio;
//////					pit.curmotorctrlinfo.current = pit.tempdata.current;
//////					pit.curmotorctrlinfo.current =pit.curmotorctrlinfo.current/10000*pit.parameter.current_limit[1];
//				
//					pit.tempdata.temp_angle[1] = (rx_data[0]<<8)|(rx_data[1]);
//					pit.curmotorctrlinfo.angle =pit.tempdata.temp_angle[1]*360.0f/0x1fff-180.f;
//					pit.curmotorctrlinfo.speed = ((rx_data[2]<<8)|(rx_data[3]));
//					pit.tempdata.current = (rx_data[4]<<8)|(rx_data[5]);
//			}break;
		}
//		CAN2_ready=1;
	}
}
