/**
 * @file libsci.h
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief LibSCI header
 * 
 */
/* Includes --------------------------------------------------------------------*/
#include "sci_board.h"
#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_tsensor.h"


/* Exported handles -----------------------------------------------------------*/

int xInitLibSci(void);
void xGetAcceleration(float * xyzAccel);
float xGetHumidity(void);
void xGetMagnetometer(float * xyzMag);
float xGetPressure(void);
float xGetTemperature(void);