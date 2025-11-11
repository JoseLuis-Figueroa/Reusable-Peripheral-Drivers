#include "unity_config.h"
#include "stm32f4xx_hal.h"

// USART configuration defines
// Select USART2 peripheral for test output
#define USARTx USART2
// Clock enable/disable macros for USART2 and its GPIO pins
#define USARTx_CLK_ENABLE()             __HAL_RCC_USART2_CLK_ENABLE()
#define USARTx_CLK_DISABLE()            __HAL_RCC_USART2_CLK_DISABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define USARTx_TX_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()

// Reset control macros for USART2
#define USARTx_FORCE_RESET()    __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()  __HAL_RCC_USART2_RELEASE_RESET()

// Pin definitions for USART2 TX and RX
#define USARTx_TX_PIN GPIO_PIN_2
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_TX_AF GPIO_AF7_USART2
#define USARTx_RX_PIN GPIO_PIN_3
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_RX_AF GPIO_AF7_USART2

// UART handle structure for managing the UART peripheral
static UART_HandleTypeDef UartHandle;

// Initialize UART for test output
void unityOutputStart()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Enable clocks for UART GPIO pins
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();

    // Enable UART peripheral clock
    USARTx_CLK_ENABLE();

    // Configure TX pin
    GPIO_InitStruct.Pin = USARTx_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;     // Alternate function push-pull
    GPIO_InitStruct.Pull = GPIO_PULLUP;         // Enable pullup
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;    // Fast GPIO speed
    GPIO_InitStruct.Alternate = USARTx_TX_AF;   // Set alternate function for UART

    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

    // Configure RX pin with same settings as TX
    GPIO_InitStruct.Pin = USARTx_RX_PIN;
    GPIO_InitStruct.Alternate = USARTx_RX_AF;

    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

    // Configure UART peripheral
    UartHandle.Instance = USARTx;
    UartHandle.Init.BaudRate = 115200;          // Set baud rate to 115200
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    // Initialize UART with above settings
    if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        // Error handling - infinite loop if initialization fails
        while (1)
        {
        }
    }
}

// Transmit a single character through UART
void unityOutputChar(char c)
{
    HAL_UART_Transmit(&UartHandle, (uint8_t *)(&c), 1, 1000);  // 1000ms timeout
}

// Flush output - not implemented for this UART configuration
void unityOutputFlush() {}

// Cleanup - disable all clocks used by UART
void unityOutputComplete()
{
    USARTx_CLK_DISABLE();
    USARTx_RX_GPIO_CLK_DISABLE();
    USARTx_TX_GPIO_CLK_DISABLE();
}