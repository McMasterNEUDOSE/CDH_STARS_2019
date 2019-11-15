/**
 * @file libsci.c
 * @author mostafa ayesh (ayeshm@mcmaster.ca)
 * @brief LibSCI provides functions for scientific data collection
 * 
 */
#include "libsci.h"

/**
 * @brief Initializes all sensors
 * 
 * @return int status
 */
int xInitLibSci(void)
{
    if (BSP_ACCELERO_Init() != ACCELERO_OK) return 1;
    if (BSP_HSENSOR_Init() != HSENSOR_OK) return 1;
    if (BSP_MAGNETO_Init() != MAGNETO_OK) return 1;
    if (BSP_PSENSOR_Init() != PSENSOR_OK) return 1;
    if (BSP_TSENSOR_Init() != TSENSOR_OK) return 1;
    return 0;
}

/**
 * @brief Gets Acceleration data from IMU
 * 
 * @param xyzAccel XYZ accelerations (m/s^2)
 */
void xGetAcceleration(float * xyzAccel)
{
    int16_t intAccel[3];
    BSP_ACCELERO_AccGetXYZ(intAccel);
    xyzAccel[0] = ((float) intAccel[0])/1000 * 9.81;
    xyzAccel[1] = ((float) intAccel[1])/1000 * 9.81;
    xyzAccel[2] = ((float) intAccel[2])/1000 * 9.81;
}

/**
 * @brief Gets humidity data
 * 
 * @return float humidity (percentage)
 */
float xGetHumidity(void)
{
    return BSP_HSENSOR_ReadHumidity();
}

/**
 * @brief Gets Magnetometer data
 * 
 * @param xyzMag XYZ Magnetic flux (mGauss)
 * 
 */
void xGetMagnetometer(float * xyzMag)
{
    int16_t intMag[3];
    BSP_MAGNETO_GetXYZ(intMag);
    xyzMag[0] = ((float) intMag[0]);
    xyzMag[1] = ((float) intMag[1]);
    xyzMag[2] = ((float) intMag[2]);
}

/**
 * @brief Gets pressure reading from barometer
 * 
 * @return float Pressure (hPA)
 */
float xGetPressure(void)
{
    return BSP_PSENSOR_ReadPressure();
}

/**
 * @brief Gets temperature reading
 * 
 * @return float temperature (Celsius)
 */
float xGetTemperature(void)
{
    return BSP_TSENSOR_ReadTemp();
}