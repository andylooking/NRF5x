/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_saadc.h"
#include "modules\module_serial.h"

#include "nrf5xdk_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  Clock_Config();
  GPIO_Config();
  SAADC_Config();
  Serial_Config();

  printf("\fHello World!!\r\n");
}

int main( void )
{
  System_Init();

  while(1) {
    LED1_Toggle();
    delay_ms(100);

    printf("ADC = %d\r\n", SAADC_Read(ADCx_CHANNEL));
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
