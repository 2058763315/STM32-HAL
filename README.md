# STM32F407ZGT6 HAL库示例工程

基于 STM32Cube HAL 库的 Keil MDK 标准模板工程，目标芯片为 **STM32F407ZGT6**（Cortex-M4F，1MB Flash，192KB RAM）。工程已补全所有底层驱动与启动文件，用户代码预留 TODO 注释位置，开箱即用。

---

## 硬件平台

| 项目      | 参数                               |
| --------- | ---------------------------------- |
| 芯片      | STM32F407ZGT6                      |
| 内核      | ARM Cortex-M4F（带浮点单元）       |
| Flash     | 1 MB（0x08000000 ~ 0x080FFFFF）    |
| SRAM      | 192 KB（128KB 主SRAM + 64KB CCM）  |
| 系统时钟  | HSE 8 MHz → PLL → SYSCLK 168 MHz   |
| 开发环境  | Keil MDK 5.x（ARMCC/ARMCLANG）     |
| HAL库版本 | STM32F4xx HAL Driver（DFP 2.16.0） |

---

## 目录结构

```
STM32-HAL/
├── example.uvprojx              # Keil MDK 工程文件
├── example.uvoptx               # Keil 工程选项（调试器/下载配置）
│
├── Inc/                          # 用户头文件
│   ├── main.h                    # 主程序头文件（引脚宏定义、Error_Handler声明）
│   ├── stm32f4xx_hal_conf.h       # HAL库配置（模块使能、HSE值等）
│   └── stm32f4xx_it.h            # 中断服务函数声明
│
├── Src/                          # 用户源文件
│   ├── main.c                    # 主函数（时钟配置+外设初始化+主循环，TODO注释占位）
│   ├── stm32f4xx_it.c            # 中断服务函数（内核异常+外设中断模板）
│   └── stm32f4xx_hal_msp.c       # HAL底层MSP回调（时钟/GPIO/DMA配置）
│
├── Drivers/                      # 官方驱动库
│   ├── STM32F4xx_HAL_Driver/     # STM32F4xx HAL驱动
│   │   ├── Inc/                  #   HAL头文件（99个，含Legacy）
│   │   └── Src/                  #   HAL源文件（94个）
│   └── CMSIS/                    # ARM CMSIS支持
│       ├── Core/Include/         #   Cortex-M4核心头文件（core_cm4.h等）
│       └── Device/ST/STM32F4xx/  # STM32F4xx设备级文件
│           ├── Include/          #   设备寄存器定义（stm32f4xx.h, stm32f407xx.h）
│           └── Source/Templates/ # 系统初始化与启动文件
│               ├── system_stm32f4xx.c
│               └── arm/startup_stm32f407xx.s
│
├── Listings/                     # 编译输出（列表文件）
├── Objects/                      # 编译输出（.o/.axf/.hex等）
└── DebugConfig/                  # 调试器配置
```

---

## 工程配置

### 全局宏定义

```
USE_HAL_DRIVER
STM32F407xx
```

### 头文件搜索路径

```
.\Inc
.\Drivers\STM32F4xx_HAL_Driver\Inc
.\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy
.\Drivers\CMSIS\Device\ST\STM32F4xx\Include
.\Drivers\CMSIS\Core\Include
```

### 内存布局

| 区域            | 起始地址   | 大小   |
| --------------- | ---------- | ------ |
| Flash (IROM)    | 0x08000000 | 1 MB   |
| 主SRAM (IRAM)   | 0x20000000 | 128 KB |
| CCM RAM (IRAM2) | 0x10000000 | 64 KB  |

### 文件组划分

| 组名                 | 文件数 | 说明                            |
| -------------------- | ------ | ------------------------------- |
| USER                 | 3      | 用户应用代码（main / it / msp） |
| CMSIS                | 2      | 系统初始化 + 启动文件           |
| STM32F4xx_HAL_Driver | 94     | 全部HAL外设驱动源文件           |

---

## 快速开始

1. 用 Keil MDK 打开 `example.uvprojx`
2. 选择调试器（ST-Link / J-Link / DAP）：菜单 **Project → Options for Target → Debug**
3. 点击 **Build (F7)** 编译工程
4. 连接开发板，点击 **Download (F8)** 下载程序

---

## 用户代码开发指南

### 添加外设初始化

在 `Src/main.c` 中：

```c
// 1. 在文件顶部声明句柄
UART_HandleTypeDef huart1;

// 2. 添加初始化函数声明
static void MX_USART1_UART_Init(void);

// 3. 在 main() 中调用
MX_USART1_UART_Init();

// 4. 实现初始化函数
static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  HAL_UART_Init(&huart1);
}
```

### 配置外设底层（MSP）

在 `Src/stm32f4xx_hal_msp.c` 中实现对应的 `HAL_xxx_MspInit()` 回调：

```c
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // GPIO复用配置、中断优先级等
  }
}
```

### 添加中断处理

在 `Src/stm32f4xx_it.c` 中添加对应的中断服务函数：

```c
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}
```

---

## 时钟树说明

`SystemClock_Config()` 已配置好标准168MHz时钟：

```
HSE 8 MHz
  │
  ├── PLL_M = 8   →  1 MHz (PLL输入)
  ├── PLL_N = 336 → 336 MHz (VCO输出)
  ├── PLL_P = 2   → 168 MHz (SYSCLK)
  └── PLL_Q = 7   →  48 MHz (USB OTG FS / SDIO / RNG)

AHB  = 168 MHz (HCLK)
APB1 =  42 MHz (PCLK1, 定时器84MHz)
APB2 =  84 MHz (PCLK2, 定时器168MHz)
```

> 如果你的外部晶振不是 8 MHz，需要修改 `stm32f4xx_hal_conf.h` 中的 `HSE_VALUE` 和 PLL 参数。

---

## 注意事项

- 本工程**未启用RTX/FreeRTOS**，为裸机模板；如需RTOS，需自行移植
- 所有HAL外设源文件均已加入编译，如不需要某个模块可在 `stm32f4xx_hal_conf.h` 中注释掉对应的 `HAL_xxx_MODULE_ENABLED` 宏以减小固件体积
- `main.c` 中的业务逻辑全部用 `/* TODO: ... */` 注释标注位置，直接在对应位置填充代码即可
- 调试时建议开启 **Use MicroLIB**（Project → Options → Target → Code Generation）以减小固件体积
