/**
 * @file sci_board.h
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief SCI board specific definitions
 * 
 */

#ifndef __SCI_BOARD_H__
#define __SCI_BOARD_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Exported functions prototypes ---------------------*/
int xSCIInit(void);

/* Exported handles -----------------------------------------------------------*/
extern DFSDM_Channel_HandleTypeDef hdfsdm1_channel1;
extern I2C_HandleTypeDef hi2c2;
extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart1;

/* Target definitions ---------------------*/
#define TARGET_BOARD "SCI"

/* Pin definitions -----------------------------------*/
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOB
#define HT221_DRDY_Pin GPIO_PIN_15
#define HT221_DRDY_GPIO_Port GPIOD
#define VL53L0X_XSHUT_Pin GPIO_PIN_6
#define VL53L0X_XSHUT_GPIO_Port GPIOC
#define VL53L0X_GPIO1_EXTI7_Pin GPIO_PIN_7
#define VL53L0X_GPIO1_EXTI7_GPIO_Port GPIOC
#define LIS3MDL_DRDY_Pin GPIO_PIN_8
#define LIS3MDL_DRDY_GPIO_Port GPIOC
#define UART_BAUDRATE 115200

#ifdef __cplusplus
 }
#endif

#endif /* __SCI_BOARD_H__ */