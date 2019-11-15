/**
 * @file obc_board.h
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief OBC board specific definitions
 * 
 */

#ifndef __OBC_BOARD_H__
#define __OBC_BOARD_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Exported functions prototypes ---------------------*/
int xOBCInit(void);

/* Target definitions ---------------------*/
#define TARGET_BOARD "OBC"

/* Pin definitions -----------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define UART_BAUDRATE 115200

#ifdef __cplusplus
 }
#endif

#endif /* __OBC_BOARD_H__ */
