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
* DIO test functions for MCU register verification
*****************************************************************************/
/* 
 * Test that initializing the DIO peripheral sets the correct bits in the 
 * MCU registers.
*/
void test_dio_init_registers(void)
{
    /* Verify MODER register for PA5 is set to output (01) */
    TEST_ASSERT_BITS(0b11 << (5*2), (DIO_OUTPUT<<(5*2)), GPIOA->MODER);

    /* Verify OTYPER register for PA5 is set to push-pull (0) */
    TEST_ASSERT_BITS(1 << 5, 1 << DIO_PUSH_PULL, GPIOA->OTYPER);

    /* Verify OSPEEDR register for PA5 is set to high speed (10) */
    TEST_ASSERT_BITS(0b11 << (5*2), (DIO_HIGH_SPEED<<(5*2)), GPIOA->OSPEEDR);

    /* Verify PUPDR register for PA5 is set to no resistor (00) */
    TEST_ASSERT_BITS(0b11 << (5 * 2), (DIO_NO_RESISTOR<<(5*2)), GPIOA->PUPDR);

    /* Verify AFRL register for PA5 is set to AF0 (0000) */
    TEST_ASSERT_BITS(0b1111 << (5 * 4), (DIO_AF0<<(5*4)), GPIOA->AFR[0]);
}

/*
 * Test input data register that the address results in the expected 
 * value.
*/
void test_dio_input_data_register(void)
{
    /* Set bit 13 high */
    uint32_t testValue = 0x00001000;    

    /* Read from GPIOA_IDR using DIO_pinRead */
    DioPinConfig_t pinConfig = {DIO_PC, DIO_PC13};
    DioPinState_t pinState = DIO_pinRead(&pinConfig);
    TEST_ASSERT_BITS(testValue, (pinState << 13), GPIOC->IDR);
}

/* Test output data register that the address results in the expected 
 * value.
*/
void test_dio_output_data_register(void)
{
    /* Set bit 5 high */
    uint32_t testValue = 0x00000020;    

    /* Write to GPIOA_ODR using DIO_pinWrite */
    DioPinConfig_t pinConfig = {DIO_PA, DIO_PA5};
    DIO_pinWrite(&pinConfig, DIO_HIGH);
    TEST_ASSERT_EQUAL(testValue, GPIOA->ODR);

    /* Set bit 5 low */
    testValue = 0x00000000;

    /* Write to GPIOA_ODR using DIO_pinWrite */
    DIO_pinWrite(&pinConfig, DIO_LOW);
    TEST_ASSERT_EQUAL(testValue, GPIOA->ODR);
}

/*****************************************************************************
* DIO test functions for functionality verification
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

    /* Run test to verify DIO initialization configures registers */
    RUN_TEST(test_dio_init_registers);

    /* Run test to verify DIO IDR read*/
    RUN_TEST(test_dio_input_data_register);

    /* Run test to verify DIO ODR write*/
    RUN_TEST(test_dio_output_data_register);

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