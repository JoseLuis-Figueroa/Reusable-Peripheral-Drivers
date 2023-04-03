/**
 * @file dio_cfg.h
 * @author Jose Luis Figueroa (you@domain.com)
 * @brief This module contains interface definitions for the Dio 
 * configuration. This is the header file for the definition of the
 * interface for retrieving the digital input/output configuration table.
 * @version 1.0
 * @date 2023-03-16
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. All rights reserved.
 * 
 */
#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/*****************************************************************************
* Includes
*****************************************************************************/

/*****************************************************************************
* Preprocessor Constants
*****************************************************************************/
/**
 * Defines the number of pins on each processor port.
 */
#define NUMBER_OF_CHANNELS_PER_PORT 8U
/**
 * Defines the number of ports on the processor.
 */
#define NUMBER_OF_PORTS 8U

/*****************************************************************************
* Typedefs
*****************************************************************************/
/**
 * Defines the possible states for a digital output pin
*/
typedef enum
{
    DIO_LOW,            /**Defines digital state ground*/
    DIO_HIGH,           /**Defines digital state power*/
    DIO_PIN_STATE_MAX   /**Defines the Maximum digital state*/
}DioPinState_t;

/**
 * Defines a enumerated list of all the channels (pins) on the MCU device.
 * The last element is used to specify the maximum number of enumerated 
 * labels.
 */
typedef enum
{
    /*TODO: Populate this list based on available MCU pins*/
    PA0,        /**< PA0 */
    PA1,        /**< PA1 */
    PA2,        /**< PA2 */
    PA3,        /**< PA3 */
    PA4,        /**< PA4 */
    PA5,        /**< PA5 */
    PA6,        /**< PA6 */
    PA7,        /**< PA7 */
    PA8,        /**< PA8 */
    PA9,        /**< PA9 */
    PA10,       /**< PA10 */
    PA11,       /**< PA11 */
    PA12,       /**< PA12 */
    PA13,       /**< PA13 */
    PA14,       /**< PA14 */
    PA15,       /**< PA15 */
    PB0 = 0,    /**< PB0 */
    PB1,        /**< PB1 */
    PB2,        /**< PB2 */
    PB3,        /**< PB3 */
    PB4,        /**< PB4 */
    PB5,        /**< PB5 */
    PB6,        /**< PB6 */
    PB7,        /**< PB7 */
    PB8,        /**< PB8 */
    PB9,        /**< PB9 */
    P10,        /**< PB10 */
    P11,        /**< P11 */
    P12,        /**< P12 */
    P13,        /**< P13 */
    P14,        /**< P14 */
    P15,        /**< P15 */
}DioChannel_t;

/**
 * Defines the direction of the Dio pin as an input or output  
 */
typedef enum
{
    /*TODO: Populate with possible direction options*/
    DIO_INPUT,
    DIO_OUTPUT
}DioDirection_t;


/**
 * Defines the possible DIO pin multiplexing values. The data sheet should 
 * be reviewed for proper multiplexing options.
 */
typedef enum
{
    /*TODO: Populate with possible mode options*/
    DIO_MAX_MODE
}DioMode_t;

/**
 * Defines the possible states of the channel pull-ups
 */
typedef enum
{
    DIO_PULLUP_DISABLED,    /*< Used to disable the internal pull-ups*/
    DIO_PULLUP_ENABLED,     /*< Used to enable the internal pull-ups*/
    DIO_MAX_RESISTOR        /*< Resistor states should be bellow this value*/
}DioResistor_t;

/**
 * Defines the digital input/output configuration table's elements that are 
 * used by Dio_Init to configure the Dio peripheral.
 */
typedef struct 
{
    /* TODO: Add additional members for the MCU peripheral */
    DioChannel_t Channel;       /**< The I/O pin */
    DioResistor_t Resistor;     /**< ENABLED OR DISABLED */
    DioDirection_t Direction;   /**< Output or Input */
    DioPinState_t Data;         /**< High or Low */
    DioMode_t Function;         /**< Mux Function - Dio_Peri_Select*/
}DioConfig_t;

/**
 * Defines the slew rate settings available
 */
typedef enum
{
    Fast,   /**< Fast slew rate is configured on the corresponding pin, */
    Slow,   /**< Slow slew rate is configured on the corresponding pin, */
}DioSlew_t;

/*****************************************************************************
* Function Prototypes
*****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

const DioConfig_t * const DIO_ConfigGet(void);

#ifdef __cplusplus
} //extern "C"
#endif

#endif /*DIO_H_*/