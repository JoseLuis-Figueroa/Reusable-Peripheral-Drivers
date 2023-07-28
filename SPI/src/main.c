/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief Implement the SPI driver. 
 * @version 1.0
 * @date 2023-07-24
 * @note 
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. MIT License.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include "spi.h"
#include "dio.h"

int main(void)
{
    /* Enable clock access to GPIOA*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* Get the address of the Configuration table for DIO*/
    const DioConfig_t * const DioConfig = DIO_configGet();
    /* Initialize the DIO pins according to the configuration table*/
    DIO_Init(DioConfig);
    
    /* Get the address of the configuration table for SPI*/
    const SpiConfig_t * const SpiConfig = SPI_ConfigGet();
    /* Initialize the SPI channel according to the configuration table*/
    SPI_Init(SpiConfig);

    /* Data to be sent*/
    uint16_t data = 0x9090;

    while(1)
    {
        /* Pull cs line low to enable slave*/
        DIO_pinWrite(DIO_PA, DIO_PA9, DIO_LOW);
        /* Transmit data*/
        SPI_Transfer(SPI1, data, 1);
        /* Pull cs line high to disable slave*/
        DIO_pinWrite(DIO_PA, DIO_PA9, DIO_HIGH);
    }
}