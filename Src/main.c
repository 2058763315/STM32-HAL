/**
  ******************************************************************************
  * @file    main.c
  * @brief   主函数（用户实现留空，用注释标注待办位置）
  * @note    目标芯片: STM32F407ZGT6 (Cortex-M4F, 1MB Flash, 192KB RAM)
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* 私有变量 ------------------------------------------------------------------*/
/* TODO: 在这里定义你的句柄和全局变量，例如：
UART_HandleTypeDef huart1;
TIM_HandleTypeDef  htim2;
ADC_HandleTypeDef  hadc1;
*/

/* 函数声明 ------------------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* TODO: 在这里添加你的外设初始化函数声明，例如：
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
*/

/**
  * @brief  应用程序入口
  */
int main(void)
{
  /* HAL库初始化（必须最先调用） */
  HAL_Init();

  /* 系统时钟配置：HSE=8MHz → PLL → SYSCLK=168MHz */
  SystemClock_Config();

  /* 外设初始化 */
  MX_GPIO_Init();
  /* TODO: 在这里调用你的外设初始化函数，例如：
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  */

  /* 主循环 */
  while (1)
  {
    /* TODO: 在这里编写你的主循环业务逻辑，例如：
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_Delay(500);
    */
  }
}

/**
  * @brief  系统时钟配置
  *         HSE = 8MHz, PLL_M=8, PLL_N=336, PLL_P=2, PLL_Q=7
  *         SYSCLK = 168MHz, HCLK = 168MHz, PCLK1 = 42MHz, PCLK2 = 84MHz
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState    = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM        = 8;
  RCC_OscInitStruct.PLL.PLLN        = 336;
  RCC_OscInitStruct.PLL.PLLP        = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ        = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                   | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  GPIO初始化（示例：PC13板载LED）
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* TODO: 在这里添加你的GPIO初始化代码
  GPIO_InitStruct.Pin   = LED_Pin;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
  */
}

/**
  * @brief  错误处理（死循环）
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
    /* TODO: 在这里添加错误指示，例如点亮错误LED */
  }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  断言失败回调
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* TODO: 在这里处理断言失败，例如打印文件名和行号 */
  (void)file;
  (void)line;
}
#endif
