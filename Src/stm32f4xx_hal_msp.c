/**
  ******************************************************************************
  * @file    stm32f4xx_hal_msp.c
  * @brief   HAL库底层MCU支持包（MSP）初始化
  *          每个外设的底层时钟、GPIO、DMA配置在这里
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
  * @brief  HAL库全局MSP初始化
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* TODO: 在这里配置系统级中断优先级分组 */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

/**
  * @brief  HAL库全局MSP反初始化
  */
void HAL_MspDeInit(void)
{
}

/* 外设MSP回调函数 ------------------------------------------------------------*/
/* TODO: 在这里为每个外设实现底层初始化回调，例如：

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (huart->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // PA9  TX
    GPIO_InitStruct.Pin       = GPIO_PIN_9;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA10 RX
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
  }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    __HAL_RCC_TIM2_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
}
*/
