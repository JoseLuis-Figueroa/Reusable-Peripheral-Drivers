/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief Implement a slave SPI driver using Nucleo-F401RE. Send a value to 
 * the master continuously.
 * @version 1.0
 * @date 2023-08-30
 * @note Take into account the following considerations:
 * + The microcontroller internal system clock is 16MHz. The baud rate is 
 *   divided by 4, then, baud rate = 4MHz.
 * + It is necessary to connect the Logic Analyzer to the SPI1 pins to debug
 *   or test the SPI communication.
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
    /* Enable clock access to GPIOA and SPI1*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /* Get the address of the Configuration table for DIO*/
    const DioConfig_t * const DioConfig = DIO_configGet();
    /* Get the size of the configuration table*/
    size_t configSizeDio = DIO_configSizeGet();
    /* Initialize the DIO pins according to the configuration table*/
    DIO_init(DioConfig, configSizeDio);
    
    /* Get the address of the configuration table for SPI*/
    const SpiConfig_t * const SpiConfig = SPI_ConfigGet();
    /* Get the size of the configuration table*/
    size_t configSizeSpi = SPI_configSizeGet();
    /* Initialize the SPI channel according to the configuration table*/
    SPI_init(SpiConfig, configSizeSpi);

    /* Data to be sent*/
    uint16_t data[1]={0x66};

    /* SPI transfer configuration*/
    SpiTransferConfig_t TransferConfig =
    {
        .Channel = SPI_CHANNEL1,
        .size = sizeof(data)/sizeof(data[0]),
        .data = data
    };


    while(1)
    {
        /* Transmit data*/
        SPI_transfer(&TransferConfig);

    }
}