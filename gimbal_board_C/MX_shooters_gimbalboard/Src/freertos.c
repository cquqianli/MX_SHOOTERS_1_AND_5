/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for infotask */
osThreadId_t infotaskHandle;
const osThreadAttr_t infotask_attributes = {
  .name = "infotask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for gimbaltask */
osThreadId_t gimbaltaskHandle;
const osThreadAttr_t gimbaltask_attributes = {
  .name = "gimbaltask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for weapontask */
osThreadId_t weapontaskHandle;
const osThreadAttr_t weapontask_attributes = {
  .name = "weapontask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void infoproc(void *argument);
void gimbctrl(void *argument);
void weapctrl(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of infotask */
  infotaskHandle = osThreadNew(infoproc, NULL, &infotask_attributes);

  /* creation of gimbaltask */
  gimbaltaskHandle = osThreadNew(gimbctrl, NULL, &gimbaltask_attributes);

  /* creation of weapontask */
  weapontaskHandle = osThreadNew(weapctrl, NULL, &weapontask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_infoproc */
/**
  * @brief  Function implementing the infotask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_infoproc */
__weak void infoproc(void *argument)
{
  /* USER CODE BEGIN infoproc */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END infoproc */
}

/* USER CODE BEGIN Header_gimbctrl */
/**
* @brief Function implementing the gimbaltask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_gimbctrl */
__weak void gimbctrl(void *argument)
{
  /* USER CODE BEGIN gimbctrl */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END gimbctrl */
}

/* USER CODE BEGIN Header_weapctrl */
/**
* @brief Function implementing the weapontask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_weapctrl */
__weak void weapctrl(void *argument)
{
  /* USER CODE BEGIN weapctrl */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END weapctrl */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
