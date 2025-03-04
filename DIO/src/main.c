/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief Implement the DIO driver. 
 * @version 1.1
 * @date 2025-03-04
 * @note 
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. MIT License.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "dio.h"

int main()
{
    bool buttonFlag = false;

    /* Enable clock access to GPIOA, GPIOB and GPIOC*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;   
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    /* Get the address of the configuration table*/
    const DioConfig_t * const DioConfig = DIO_configGet();

    /* Initialize the GPIO according to the configuration table*/
    DIO_init(DioConfig);

    /*Define the pin configuration for PC13 (User button)*/
    const DioPinConfig_t UserButton1= {DIO_PC, DIO_PC13};
    /*Define the pin configuration for PA5 (Embedded LED)*/
    const DioPinConfig_t UserLED1= {DIO_PA, DIO_PA5}; 
    /*Define the pin configuration for PA0*/
    const DioPinConfig_t UserLED2= {DIO_PA, DIO_PA0};
    
    while(1)
    {
        /* 
         * Review PC13 pin (User button). A pull-up resistor circuit is
         * embedded on board, when it is pressed a ground signal is send and
         * embedded led of the board turns on.
        */
        if (DIO_pinRead(&UserButton1) == false)
        {
            /* Turn on the PA5 (Embedded LED)*/
            DIO_pinWrite(&UserLED1, DIO_HIGH);

            /* Write directly to the register GPIOB_ODR (clear PB0)*/
            DIO_registerWrite(0x40020414, 0x00000000);

            buttonFlag = true;
        }
        else
        {
            /* Turn off the PA5*/
            DIO_pinWrite(&UserLED1, DIO_LOW);

            /* Write directly to the register GPIOB_ODR (set PB0)*/
            DIO_registerWrite(0x40020414, 0x00000001);
        }
        
        /* Toggle the PA0 pin. Add delay to be able to see the toggling pin*/
        DIO_pinToggle(&UserLED2);

        /* 
         * Read directly the register GPIOC_IDR (read PC13) in order to read 
         * the button
        */
        uint16_t readButton = DIO_registerRead(0x40020810);
        /* Make a mask to get IDR13 bit (PC13 pin)*/
        uint16_t readButtonMask = readButton & 0x2000;
        if (readButtonMask == 0x0000 && buttonFlag == true)
        {
            buttonFlag = false;
        }
    }
}