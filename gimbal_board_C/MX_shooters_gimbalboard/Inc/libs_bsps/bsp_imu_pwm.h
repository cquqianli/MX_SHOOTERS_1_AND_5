#ifndef BSP_IMU_PWM_H
#define BSP_IMU_PWM_H
#include "struct_typedef.h"
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_tim.h>

extern void imu_pwm_set(uint16_t pwm);

#endif
