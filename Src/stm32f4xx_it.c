/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   中断服务函数
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"

/* Cortex-M4 内核异常处理 ----------------------------------------------------*/
/**
  * @brief  不可屏蔽中断
  */
void NMI_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  硬件错误
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  内存管理错误
  */
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  总线错误
  */
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  用法错误
  */
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  SVC调用
  */
void SVC_Handler(void)
{
}

/**
  * @brief  调试监控
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief   PendSV（FreeRTOS任务切换会重定义这里）
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  SysTick中断（HAL时基）
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/* 外设中断服务函数 ----------------------------------------------------------*/
/* TODO: 在这里添加你的外设中断处理函数，例如：
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}
*/
