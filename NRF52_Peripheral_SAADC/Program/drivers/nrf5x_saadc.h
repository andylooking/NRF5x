/* #include "nrf5x_saadc.h" */

#ifndef __NRF5x_SAADC_H
#define __NRF5x_SAADC_H

#include "nrf5x_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define ADCx_CHANNEL  0 // AIN0
/*====================================================================================================*/
/*====================================================================================================*/
void    SAADC_Config( void );
int16_t SAADC_Read( uint8_t channel );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
