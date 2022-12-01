#include "main.h"
#include "devices/mpu.h"
#include "devices/rc.h"

int RC_READY=0;//外设就绪标志位
RC_DATA RC_Data;//需要的数据
RC_DATA RC_Last_Data;//需要的数据
KEY Key;
KEY Last_Key;
uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];//DMA接收数组

/*-------------------------------------
* 函数名：遥控器解码
* 描述  ：解码遥控器发来的数据
* 输入  ：DMA数据，解码后的结构体指针
* 输出  ：无
作者：抄的DJI的
日期：2021.7.7
-----------------------------------------*/ 
void RC_RX_Decoder(uint8_t *sbus_buf, RC_DATA *rc_data,KEY *key)
{
    if (sbus_buf == NULL || rc_data == NULL)
    {
        return;
    }
		RC_Last_Data=RC_Data;
		Last_Key=Key;
    rc_data->rc.ch[0] = (sbus_buf[0] | (sbus_buf[1] << 8)) & 0x07ff;        //!< Channel 0
    rc_data->rc.ch[1] = ((sbus_buf[1] >> 3) | (sbus_buf[2] << 5)) & 0x07ff; //!< Channel 1
    rc_data->rc.ch[2] = ((sbus_buf[2] >> 6) | (sbus_buf[3] << 2) |          //!< Channel 2
                         (sbus_buf[4] << 10)) &0x07ff;
    rc_data->rc.ch[3] = ((sbus_buf[4] >> 1) | (sbus_buf[5] << 7)) & 0x07ff; //!< Channel 3
    rc_data->rc.s[1] = ((sbus_buf[5] >> 4) & 0x0003);                  //!< Switch left
    rc_data->rc.s[0] = ((sbus_buf[5] >> 4) & 0x000C) >> 2;                       //!< Switch right
    rc_data->mouse.x = sbus_buf[6] | (sbus_buf[7] << 8);                    //!< Mouse X axis
    rc_data->mouse.y = sbus_buf[8] | (sbus_buf[9] << 8);                    //!< Mouse Y axis
    rc_data->mouse.z = sbus_buf[10] | (sbus_buf[11] << 8);                  //!< Mouse Z axis
    rc_data->mouse.press_l = sbus_buf[12];                                  //!< Mouse Left Is Press ?
    rc_data->mouse.press_r = sbus_buf[13];                                  //!< Mouse Right Is Press ?
    rc_data->key.v = sbus_buf[14] | (sbus_buf[15] << 8);                    //!< KeyBoard value
    rc_data->rc.ch[4] = sbus_buf[16] | (sbus_buf[17] << 8);                 //NULL

    rc_data->rc.ch[0] -= RC_CH_VALUE_OFFSET;
    rc_data->rc.ch[1] -= RC_CH_VALUE_OFFSET;
    rc_data->rc.ch[2] -= RC_CH_VALUE_OFFSET;
    rc_data->rc.ch[3] -= RC_CH_VALUE_OFFSET;
    rc_data->rc.ch[4] -= RC_CH_VALUE_OFFSET;		
		
//		rc_data->rc.ch[0]=(rc_data->rc.ch[0]-RC_CH_VALUE_OFFSET)/660*180;
//		if(rc_data->rc.ch[1]>0)
//			rc_data->rc.ch[1]=(rc_data->rc.ch[1]-RC_CH_VALUE_OFFSET)/660*pit.parameter.angle_limit[1];
//		else if(rc_data->rc.ch[1]<=0)
//			rc_data->rc.ch[1]=(rc_data->rc.ch[1]-RC_CH_VALUE_OFFSET)/660*pit.parameter.angle_limit[0];
//		
//		for(int i=2;i<5;i++)
//		{
//			rc_data->rc.ch[i]=(rc_data->rc.ch[i]-RC_CH_VALUE_OFFSET)/660*maxmotorspeed;
//		}	
		
		
		key->key_w     =  rc_data->key.v & 0x0001;
		key->key_s     = (rc_data->key.v & 0x0002)>>1;
		key->key_a     = (rc_data->key.v & 0x0004)>>2;
		key->key_d     = (rc_data->key.v & 0x0008)>>3;
		key->key_shift = (rc_data->key.v & 0x0010)>>4;
		key->key_ctrl  = (rc_data->key.v & 0x0020)>>5;
		key->key_q     = (rc_data->key.v & 0x0040)>>6;
		key->key_e     = (rc_data->key.v & 0x0080)>>7;
    key->key_r     = (rc_data->key.v & 0x0100)>>8;
    key->key_f     = (rc_data->key.v & 0x0200)>>9;
    key->key_g     = (rc_data->key.v & 0x0400)>>10;
    key->key_z     = (rc_data->key.v & 0x0800)>>11;
    key->key_x     = (rc_data->key.v & 0x1000)>>12;
    key->key_c     = (rc_data->key.v & 0x2000)>>13;
    key->key_v     = (rc_data->key.v & 0x4000)>>14;
    key->key_b     = (rc_data->key.v & 0x8000)>>15;
		
		RC_READY=1;
}

/*-------------------------------------
* 函数名：遥控器初始化
* 描述  ：初始化遥控器
* 输入  ：串口，串口dma，缓冲0，缓冲1，数据长度
* 输出  ：无
作者：LPGUAIA魔改的DJI的
日期：2021.7.7
-----------------------------------------*/ 
void RC_INIT(void)
{
	DMA_RX_INIT(&huart3,&hdma_usart3_rx,sbus_rx_buf[0],sbus_rx_buf[1],SBUS_RX_BUF_NUM);
}
/*-------------------------------------
* 函数名：放在it.c文件里的串口一的中断里的handler
* 描述  ：中断串口一接收处理
* 输入  ：无
* 输出  ：无
作者：LPGUAIA魔改的DJI的
日期：2021.7.7
-----------------------------------------*/ 
void USART3_inIRQHandler(void)
{
		if(huart3.Instance->SR & UART_FLAG_RXNE)
    {
      __HAL_UART_CLEAR_IDLEFLAG(&huart3);
    }
		else if(huart3.Instance->SR & UART_FLAG_IDLE) 
    {
      static uint16_t this_time_rx_len = 0;
			__HAL_UART_CLEAR_PEFLAG(&huart3);
		  this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;
			hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;
			if((hdma_usart3_rx.Instance->CR&DMA_SxCR_CT)==RESET)
			{
				hdma_usart3_rx.Instance->CR|=DMA_SxCR_CT;
				__HAL_DMA_ENABLE(&hdma_usart3_rx);
				if(this_time_rx_len == RC_FRAME_LENGTH)
        {
					RC_RX_Decoder(sbus_rx_buf[0], &RC_Data,&Key);
        }
			}
			else
			{
				DMA1_Stream1->CR &= ~(DMA_SxCR_CT);
				__HAL_DMA_ENABLE(&hdma_usart3_rx);
				if(this_time_rx_len == RC_FRAME_LENGTH)
				{
					RC_RX_Decoder(sbus_rx_buf[1], &RC_Data,&Key);
        }
			}
		}
		
}


