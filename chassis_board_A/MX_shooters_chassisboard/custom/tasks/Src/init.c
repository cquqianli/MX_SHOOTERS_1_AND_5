#include "main.h"

void device_init(void)
{
//	while(!RC_READY)
//	{
//		RC_INIT();
//	}
	while(!CAN1_ready||!CAN2_ready||!GIMB_READY)
	{
		can_filter_init();
	}

}
