#include "main.h"

void device_init(void)
{
	while(!RC_READY)
	{
		RC_INIT();
		HAL_Delay(100);
	}
	while(!CAN1_ready||!CAN2_ready||!MPU_ready)
	{
		can_filter_init();
		HAL_Delay(100);
	}

		
}
