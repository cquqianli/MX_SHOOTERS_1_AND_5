#include "main.h"

void device_init(void)
{
	HAL_GPIO_WritePin(LED_B_GPIO_Port,LED_B_Pin,GPIO_PIN_SET); // 初始化的灯光提示
	while(!RC_READY)
	{
		RC_INIT();
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_SET); // 初始化的灯光提示
		HAL_Delay(1000);
	}
	HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_RESET);
	while(!CAN1_ready||!CAN2_ready||!MPU_ready)
	{
		can_filter_init();
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_B_GPIO_Port,LED_B_Pin,GPIO_PIN_RESET); // 初始化的灯光提示
}
