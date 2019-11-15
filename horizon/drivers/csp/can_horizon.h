/**
 * @file can_horizon.h
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief CSP CAN driver for both OBC and SCI nodes
 * 
 */
#ifndef __CAN_HORIZON_H__
#define __CAN_HORIZON_H__

/* Include HAL */
#include "stm32l4xx_hal.h"

/* CSP Includes */
#include "csp/csp.h"
#include "csp/arch/csp_thread.h"
#include "csp/interfaces/csp_if_can.h"

#ifdef __cplusplus
 extern "C" {
#endif

#include <csp/csp_types.h>

// #define CAN_LOOPBACK 

#ifdef CAN_LOOPBACK
    #define CAN_MODE CAN_MODE_LOOPBACK
#else
    #define CAN_MODE CAN_MODE_NORMAL
#endif

csp_iface_t * csp_can_init(const char * ifc, int bitrate);


#ifdef __cplusplus
 }
#endif

#endif /* __CAN_SCI_H__ */
