/**
 * @file sci_main.h
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief SCI main header
 * 
 */

#ifndef __SCI_MAIN_H__
#define __SCI_MAIN_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------*/
#include "sci_board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "libsci/libsci.h"
#include "csp/csp.h"
#include "csp/can_horizon.h"
#include "csp_table.h"
#include <stdio.h>

#define CSP_ADDRESS SCI_ADDRESS

#ifdef __cplusplus
 }
#endif

#endif /* __SCI_MAIN_H__ */