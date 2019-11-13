#include "sci_board.h"

DFSDM_Channel_HandleTypeDef hdfsdm1_channel1;
I2C_HandleTypeDef hi2c2;
RTC_HandleTypeDef hrtc;
UART_HandleTypeDef huart1;

int prvConfigSystemClock(void);
int prvInitGPIO(void);
int prvInitRTC(void);
int prvInitUART(void);
int prvInitDFSDM(void);
int prvInitI2C(void);

/**
 * @brief Initialize SCI
 * 
 * @return int status
 */
int xSCIInit(void)
{
    if (HAL_Init() != HAL_OK)
        return 1;
    if (prvConfigSystemClock() != 0)
        return 1;
    if (prvInitGPIO() != 0)
        return 1;
    if (prvInitRTC() != 0)
        return 1;
    if (prvInitUART() != 0)
        return 1;
    if (prvInitDFSDM() != 0)
        return 1;
    if (prvInitI2C() != 0)
        return 1;
    return 0;
}

/**
 * @brief Configure system clock
 * 
 * @return int status
 */
int prvConfigSystemClock(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    /** Initializes the CPU, AHB and APB busses clocks 
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        return 1;
    }
    /** Initializes the CPU, AHB and APB busses clocks 
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        return 1;
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_USART1 | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_DFSDM1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
    PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK2;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        return 1;
    }
    /** Configure the main internal regulator output voltage 
  */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Initialize GPIO
 * 
 * @return int status
 */
int prvInitGPIO(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(VL53L0X_XSHUT_GPIO_Port, VL53L0X_XSHUT_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : LED2_Pin */
    GPIO_InitStruct.Pin = LED2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pin : HT221_DRDY_Pin */
    GPIO_InitStruct.Pin = HT221_DRDY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HT221_DRDY_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pin : VL53L0X_XSHUT_Pin */
    GPIO_InitStruct.Pin = VL53L0X_XSHUT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(VL53L0X_XSHUT_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pins : VL53L0X_GPIO1_EXTI7_Pin LIS3MDL_DRDY_Pin */
    GPIO_InitStruct.Pin = VL53L0X_GPIO1_EXTI7_Pin | LIS3MDL_DRDY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    return 0;
}

/**
 * @brief Initialize RTC
 * 
 * @return int status
 */
int prvInitRTC(void)
{
    /** Initialize RTC Only 
  */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Initialize UART
 * 
 * @return int status
 */
int prvInitUART(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = UART_BAUDRATE;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Initialize Digital Filter 
 *        for Sigma-Delta Modulators (Microphone)
 * 
 * @return int status
 */
int prvInitDFSDM(void)
{
    hdfsdm1_channel1.Instance = DFSDM1_Channel1;
    hdfsdm1_channel1.Init.OutputClock.Activation = ENABLE;
    hdfsdm1_channel1.Init.OutputClock.Selection = DFSDM_CHANNEL_OUTPUT_CLOCK_SYSTEM;
    hdfsdm1_channel1.Init.OutputClock.Divider = 2;
    hdfsdm1_channel1.Init.Input.Multiplexer = DFSDM_CHANNEL_EXTERNAL_INPUTS;
    hdfsdm1_channel1.Init.Input.DataPacking = DFSDM_CHANNEL_STANDARD_MODE;
    hdfsdm1_channel1.Init.Input.Pins = DFSDM_CHANNEL_FOLLOWING_CHANNEL_PINS;
    hdfsdm1_channel1.Init.SerialInterface.Type = DFSDM_CHANNEL_SPI_RISING;
    hdfsdm1_channel1.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
    hdfsdm1_channel1.Init.Awd.FilterOrder = DFSDM_CHANNEL_FASTSINC_ORDER;
    hdfsdm1_channel1.Init.Awd.Oversampling = 1;
    hdfsdm1_channel1.Init.Offset = 0;
    hdfsdm1_channel1.Init.RightBitShift = 0x00;
    if (HAL_DFSDM_ChannelInit(&hdfsdm1_channel1) != HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Initialize I2C
 * 
 * @return int status
 */
int prvInitI2C(void)
{
    hi2c2.Instance = I2C2;
    hi2c2.Init.Timing = 0x10909CEC;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c2) != HAL_OK)
    {
        return 1;
    }
    /** Configure Analogue filter 
  */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        return 1;
    }
    /** Configure Digital filter 
  */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Sends characters to UART
 * 
 * @param ch charcter to put into stdout
 * @return int character sent 
 */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}