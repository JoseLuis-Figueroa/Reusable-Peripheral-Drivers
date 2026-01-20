/**
 * @file main.c
 * @author Jose Luis Figueroa
 * @brief Implement the external interrupt of the DIO driver. 
 * @version 1.0
 * @date 2026-jun-14
 * @note 
 * 
 * @copyright Copyright (c) 2026 Jose Luis Figueroa. MIT License.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "dio.h"

/******************************************************************************
* Variables
******************************************************************************/
/*Define the pin configuration for PC13 (User button)*/
const DioPinConfig_t UserButton1= {DIO_PC, DIO_PC13};
/*Define the pin configuration for PA5 (Embedded LED)*/
const DioPinConfig_t UserLED1= {DIO_PA, DIO_PA5}; 

/*Define the pin configuration for PC0 (external button)*/
const DioPinConfig_t UserButton2= {DIO_PC, DIO_PC0};
/*Define the pin configuration for PA0 (external LED)*/
const DioPinConfig_t UserLED2= {DIO_PA, DIO_PA0}; 

/******************************************************************************
* function prototypes
******************************************************************************/
void toggle_led1(void);
void toggle_led2(void);

/******************************************************************************
* Main
******************************************************************************/
int main()
{
    /* Enable clock access to GPIOA, GPIOB and GPIOC*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    /*Enable clock access to SYSCFG*/
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* Get the address of the configuration table*/
    const DioConfig_t * const DioConfig = DIO_configGet();
    /* Get the size of the configuration table*/
    size_t configSizeDio = DIO_configSizeGet();
    /* Initialize the GPIO according to the configuration table*/
    DIO_init(DioConfig, configSizeDio);

    /*Register the callback function for EXTI line 13 (PC13)*/
    DIO_callbackDispatcher(DIO_EXTI13, toggle_led1);
    /*Register the callback function for EXTI line 0 (PC0)*/
    DIO_callbackDispatcher(DIO_EXTI0, toggle_led2);

    while(1)
    {
        /* Wait for interrupt*/
        asm("nop");    
    }

    return 0;
}


/*****************************************************************************
* Function Definitions
*****************************************************************************/
void toggle_led1(void)
{
    /*Toggle the specified LED pin*/
    DIO_pinToggle(&UserLED1);
}

void toggle_led2(void)
{
    /*Toggle the specified LED pin*/
    DIO_pinToggle(&UserLED2);
}