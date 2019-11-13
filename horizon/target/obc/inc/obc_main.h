/**
 * @file obc_main.h
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief OBC main header
 * 
 */

#ifndef __OBC_MAIN_H__
#define __OBC_MAIN_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------*/
#include "obc_board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "csp/csp.h"
#include "csp_table.h"
#include "csp/can_horizon.h"
#include <stdio.h>

#define CSP_ADDRESS OBC_ADDRESS

#ifdef __cplusplus
 }
#endif

#endif /* __OBC_MAIN_H__ */
