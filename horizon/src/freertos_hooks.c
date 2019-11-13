/**
 * @file freertos_hooks.c
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief FreeRTOS required hooks
 * 
 */

#include "FreeRTOS.h"
#include "task.h"

/*============================================================================*/
void vApplicationTickHook( void )
{
}

/*============================================================================*/
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

/*============================================================================*/
void vApplicationMallocFailedHook( void ) 
{
}

/*============================================================================*/
void vApplicationIdleHook( void )
{
}

/*============================================================================*/