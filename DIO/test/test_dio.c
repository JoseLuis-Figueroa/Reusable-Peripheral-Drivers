/**
 * @file test_dio.c
 * @author Jose Luis Figueroa
 * @brief The unit-testing implementation for the DIO driver on the host.
 * @version 1.2
 * @date 2025-nov-07
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
 */
#include "../include/dio.h"
#include "../src/dio.c"
#include <unity.h>

/*****************************************************************************
* Default setUp and tearDown functions
*****************************************************************************/
/*
 * setUp is executed before each test. Here we enable the clocks and 
 * initialize the peripheral under test.
*/
void setUp(void)
{
    /*Enable clock access to GPIOA*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* set the address of the configuration table for DIO*/
    const DioConfig_t DioTestConfig[] = 
    {
        {DIO_PA, DIO_PA5, DIO_OUTPUT, DIO_PUSH_PULL, DIO_HIGH_SPEED, 
        DIO_NO_RESISTOR, DIO_AF0},
    };

    /* set the size of the configuration table*/
    size_t TestSizeDio = sizeof(DioTestConfig)/sizeof(DioTestConfig[0]);

    /*Initialize the DIO pins according to the configuration table*/
    DIO_init(&DioTestConfig[0], TestSizeDio);
}

void tearDown(void)
{
    /*Nothing to do here*/
}

/*****************************************************************************
* DIO test functions
*****************************************************************************/
/*
 * Verify the LED pin macro matches the on-board built-in LED pin.
 * This ensures the project is configured for the expected board pin.
 */
void led_builtin_pin_number()
{
    TEST_ASSERT_EQUAL(0x05, DIO_PA5);
}

/*
 * Test that writing a HIGH/SET to the LED pin results in a HAL read of SET.
 */
void test_led_state_high()
{
    DioPinConfig_t ledPin = {DIO_PA, DIO_PA5};

    DIO_pinWrite(&ledPin, DIO_HIGH);
    TEST_ASSERT_EQUAL(DIO_HIGH, DIO_pinRead(&ledPin));
}

/*
 * Test that writing a LOW/RESET to the LED pin results in a HAL read of RESET.
*/
void test_led_state_low()
{
    DioPinConfig_t ledPin = {DIO_PA, DIO_PA5};

    DIO_pinWrite(&ledPin, DIO_LOW);
    TEST_ASSERT_EQUAL(DIO_LOW, DIO_pinRead(&ledPin));
}

/* 
 * Test that changing the state of the LED pin results in a HAL read of the 
 * toggled state.
*/
void test_led_state_toggle()
{
    DioPinConfig_t ledPin = {DIO_PA, DIO_PA5};

    DIO_pinToggle(&ledPin);
    TEST_ASSERT_EQUAL(DIO_HIGH, DIO_pinRead(&ledPin));

    DIO_pinToggle(&ledPin);
    TEST_ASSERT_EQUAL(DIO_LOW, DIO_pinRead(&ledPin));
}

/* 
 * Test that writing a value to a register address results in the expected 
 * value being read from that register.
*/
void test_register_write()
{
    uint32_t odrRegisterA = 0x40020014; /* GPIOA_ODR */
    uint32_t testValue = 0x00000020;    /* Set bit 5 high */

    /* Write to GPIOA_ODR */
    DIO_registerWrite(odrRegisterA, testValue); 
    TEST_ASSERT_EQUAL(testValue, GPIOA->ODR);
}

/* 
 * Test that reading a value from a register address results in the expected 
 * value.
*/
void test_register_read()
{
    uint32_t odrRegisterA = 0x40020014; /* GPIOA_ODR */
    uint32_t setValue = 0x00000020;    /* Set bit 5 high */

    /* Write to GPIOA_ODR directly */
    GPIOA->ODR = setValue;

    /* Read from GPIOA_ODR using DIO_registerRead */
    uint32_t readValue = DIO_registerRead(odrRegisterA);
    TEST_ASSERT_EQUAL(readValue, GPIOA->ODR);
}

/*****************************************************************************
* Main function to run the DIO tests
*****************************************************************************/
int main(void)
{
    HAL_Init();      // initialize the HAL library
    HAL_Delay(2000); // service delay

    /*Initialize the Unity Test Framework*/
    UNITY_BEGIN();

    /*Run the DIO test functions*/
    RUN_TEST(led_builtin_pin_number);
    
    /*Run test to verify LED pin can be set HIGH*/
    RUN_TEST(test_led_state_high);

    /*Run test to verify LED pin can be set LOW*/
    RUN_TEST(test_led_state_low);

    /*Run test to verify LED pin can be toggled*/
    RUN_TEST(test_led_state_toggle);

    /* Run test to verify register write and read*/
    RUN_TEST(test_register_write);

    /* Run test to verify register read*/
    RUN_TEST(test_register_read);

    /*Complete the Unity Test Framework*/
    UNITY_END();

    /* Typical embedded pattern: prevent exit by looping forever */
    while (1)
    {
        //asm("nop");
    }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}