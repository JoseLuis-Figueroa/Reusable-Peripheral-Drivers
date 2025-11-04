/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief UART Communication.
 * Design and implement a program for a Nucleo-F401RE board to demonstrate 
 * data transfer between UART peripheral and the PC.
 * The USART driver is configured to:
 *     o Transmit a predefined data buffered in RAM via UART to the PC.
 *     o Receive data from the PC and analyze it to turn on/off an LED.
 *     o Write all configurations (UART, clock, GPIO) directly using 
 *       hardware registers. 
 * 
 * @version 1.1
 * @date 2025-03-25
 * @note 
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
*/
/*****************************************************************************
* Includes
*****************************************************************************/
#include<stdio.h>
#include<stdint.h>
#include "usart.h"
#include "dio.h"

/*****************************************************************************
 * Preprocessor Constants
******************************************************************************/
#define SYSTEM_CLOCK    16000000
#define APB1_CLOCK      SYSTEM_CLOCK
#define LED_PIN         (1U<<5)

/*****************************************************************************
 * Preprocessor variables
******************************************************************************/
char txBuffer = 'y';
char rxBuffer = 0;

int main(void)
{
    /* Enable clock access to GPIOA, and USART2 */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /*Get the address of the configuration table for DIO*/
    const DioConfig_t * const DioConfig = DIO_configGet();
    /*Get the size of the configuration table*/
    size_t configSizeDio = DIO_configSizeGet();
    /*Initialize the DIO pins according to the configuration table*/
    DIO_init(DioConfig, configSizeDio);

    /*Get the address of the configuration table for USART*/
    const UsartConfig_t * const UsartConfig = USART_configGet();
    /*Get the size of the configuration table*/
    size_t configSizeUsart = USART_configSizeGet();
    /*Initialize the USART peripheral according to the configuration table*/
    USART_init(UsartConfig, configSizeUsart, APB1_CLOCK);

    /* Transmit data */
    UsartTransferConfig_t TxTransferConfig =
    {
       .Port = USART_PORT_2,
       .data = (uint8_t*)&txBuffer
    };
    
    /* Transmit the data */
    USART_transmit(&TxTransferConfig);

    /* Receive data */
    UsartTransferConfig_t RxTransferConfig =
    {
       .Port = USART_PORT_2,
       .data = (uint8_t*)&rxBuffer
    };

    /*Define the pin configuration for PA5 (Embedded LED)*/
    const DioPinConfig_t UserLED1= {DIO_PA, DIO_PA5}; 

    while(1)
    {
        /* Receive the data */
        USART_receive(&RxTransferConfig);
        if(rxBuffer == '1')
        {
            /* Turn on the PA5 (Embedded LED)*/
            DIO_pinWrite(&UserLED1, DIO_HIGH);
        }
        else
        {
            /* Turn off the PA5 (Embedded LED)*/
            DIO_pinWrite(&UserLED1, DIO_LOW);
        }
        
    }
}