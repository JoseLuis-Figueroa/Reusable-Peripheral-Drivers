/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief Implement the DIO module. Use debug mode to test the registerWrite 
 * and registerRead functions.
 * @version 1.0
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. All rights reserved.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "dio.h"


int main()
{
    /** Enable clock access to GPIOA and GPIOC*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /** Get the address of the configuration table*/
    const DioConfig_t * const DioConfig = DIO_configGet();
    /** Initialize the GPIO according to the configuration table*/
    DIO_init(DioConfig);
    
    while(1)
    {
        /** Review PC13 pin (User button). A pull-up resistor circuit is
         *  embedded on board, when it is pressed a ground signal is send.*/
        if (DIO_pinRead(DIO_PC, DIO_PC13) == false)
        {
            /**Turn on the PA5 (Embedded LED)*/
            DIO_pinWrite(DIO_PA, DIO_PA5, DIO_HIGH);
        }
        else
        {
            /**Turn off the PA5*/
            DIO_pinWrite(DIO_PA, DIO_PA5, DIO_LOW);
        }

        /**Toggle the PA0 pin*/
        DIO_pinToggle(DIO_PA, DIO_PA0);
        /*Add delay to be avoid to see the toggling pin*/
        DIO_pinToggle(DIO_PA, DIO_PA0);

        /** Write directly to the register (MODER)*/
        DIO_registerWrite(0x40020000, 0x30000000);

        /** Read directly the register (IDR) in order to read the button*/
        uint16_t readButton = DIO_registerRead(0x40020810);
    }

}