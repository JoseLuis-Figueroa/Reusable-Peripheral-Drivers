/**
 * @file dio.c
 * @author Jose Luis Figueroa
 * @brief The implementation for the dio
 * @version 1.0
 * @date 2023-03-19
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. All rights reserved.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include "dio.h"        /*For this modules definitions*/
#include "stm32f4xx.h"  /*Microcontroller family header*/

/*****************************************************************************
* Module Preprocessor Constants
*****************************************************************************/

/*****************************************************************************
* Module Preprocessor Macros
*****************************************************************************/

/*****************************************************************************
* Module Typedefs
*****************************************************************************/

/*****************************************************************************
* Module Variable Definitions
*****************************************************************************/
/**
 * Defines a table of pointers to the peripheral input register on the 
 * microcontroller.
*/
static TYPE volatile * const DataIn[NUMBER_OF_PORTS] =  
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the peripheral data direction register on 
 * on the microcontroller.
 */
static TYPE volatile * const DataDirection[NUMBER_OF_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the peripheral latch register on the
 * microcontroller
 */
static TYPE volatile * const DataOut[NUMBER_OF_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the peripheral resistor enable register on 
 * the microcontroller.
 */
static TYPE volatile * const Resistor[NUMBER_OF_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/**
 * Defines a table of pointers to the port's function selected register on 
 * the microcontroller.
 */
static TYPE volatile * const Function[NUMBER_OF_PORTS] =
{
    (TYPE*)&REGISTER1, (TYPE*)&REGISTER2,
};

/*****************************************************************************
* Function Prototypes
*****************************************************************************/

/*****************************************************************************
* Function Definitions
*****************************************************************************/
/*****************************************************************************
 * Function: DIO_Init()
*//**
*\b Description:
 * This function is used to initialize the Dio based on the configuration  
 * table defined in dio_cfg module.
 * 
 * PRE-CONDITION: Configuration table needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: NUMBER_OF_CHANNELS_PER_PORT > 0 <br>
 * PRE-CONDITION: NUMBER_OF_PORTS > 0 <br>
 * PRE-CONDITION: The MCU clocks must be configured and enable.
 * 
 * POST-CONDITION: The DIO peripheral is set up with the configuration 
 * settings.
 * 
 * @param   Config is a pointer to the configuration table that contains the 
 *                 initialization for the peripheral.
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 *  const DioConfig_t * DioConfig = DIO_ConfigGet();
 *  DIO_Init(DioConfig);
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 * 
*****************************************************************************/
void DIO_Init(const DioConfig_t * Config)
{
    /*TODO: Define implementation*/
}

/*****************************************************************************
 * Function: DIO_ChannelRead()
*//**
 *\b Description:
 * This function is used to read the state of a dio channel (pin)
 * 
 * PRE-CONDITION: The channel is configured as INPUT <br>
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is within the maximum DioChannel_t 
 * definition.
 * 
 * POST-CONDITION: The channel state is returned.
 * 
 * @param   Channel is the DioChannel_t that represents a pin.
 * @return  The state of the channel as HIGH or LOW.
 * 
 * \b Example:
 * @code
 *  uint8_t pin = DIO_ReadChannel(PORT1_0);
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 * 
**********************************************************************/
DioPinState_t DIO_ChannelRead(DioChannel_t Channel)
{

}

/**********************************************************************
 * Function: DIO_ChannelWrite()
*//**
 *\b Description:
 * This function is used to write the state of a channel (pin) as either
 * logic high or low through the use of the DioChannel_t enum to select 
 * the channel and the DioPinState_t to define the desired state.
 * 
 * PRE-CONDITION: The channel is configured as OUTPUT <br>
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is within the maximum DioChannel_t 
 * definition.
 * 
 * POST-CONDITION: The channel state will be State.
 * 
 * @param   Channel is the pin to write using the DioChannel_t enum
 *          definition State is HIGH or LOW as defined in the 
 *          DioPinState_t enum
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 *  DIO_WriteChannel(PORT1_0, LOW);  //Set the PORT pin low
 *  DIO_WriteChannel(PORT1_0, HIGH); //Set the PORT pin high
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 * 
 **********************************************************************/
void DIO_ChannelWrite(DioChannel_t Channel, DioPinState_t State)
{

}

/**********************************************************************
 * Function: DIO_ChannelToggle()
*//**
 *\b Description:
 * This function is used to toggle the current state of a channel (pin).
 * 
 * PRE-CONDITION: The channel is configured as output <br>
 * PRE-CONDITION: The channel is configured as GPIO <br>
 * PRE-CONDITION: The channel is within the maximum DioChannel_t 
 * definition.
 *
 * POST-CONDITION:
 * 
 * @param   Channel is the pin from the DioChannel_t that is to be 
 *          modified.
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 *  DIO_ChannelToggle(PORTA_1);
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 * 
 * <br><b> - HISTORY OF CHANGES - </b>
 * 
 **********************************************************************/
void DIO_ChannelToggle(DioChannel_t Channel)
{

}

/**********************************************************************
 * Function: DIO_RegisterWrite()
*//**
 *\b Description:
 * This function is used to directly address and modify a Dio register.
 * The function should be used to access specialized functionality in 
 * the Dio peripheral that is not exposed by any other function of the
 * interface.
 * 
 * PRE-CONDITION: Address is within the boundaries of the Dio register
 * address space.
 * 
 * POST-CONDITION: The register located at address with be updated with
 * value.
 * 
 * @param   address is a register address within the Dio peripheral map.
 * @param   value is the value to set the Dio register. 
 * 
 * @return void
 * 
 * \b Example
 * @code
 *  DIO_RegisterWrite(0x1000, 0x15);
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 * 
**********************************************************************/ 
void DIO_RegisterWrite(uint32_t address, TYPE value)
{

}

/**********************************************************************
 * Function: DIO_RegisterRead()
*//**
 *\b Description:
 * This function is used  to directly address a Dio register. The 
 * function should be used to access specialized functionality in the Dio
 * peripheral that is not exposed by any other function of the interface
 * 
 * PRE-CONDITION: Address is within the boundaries of the Dio register 
 * address space.
 * 
 * POST-CONDITION: The value stored in the register is returned to the 
 * caller.
 * 
 * @param   address is the address of the Dio register to read.
 * 
 * @return  The current value of the Dio register.
 * 
 * \b Example:
 * @code
 *  DioValue = DIO_RegisterRead(0x1000);
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 *
 **********************************************************************/ 
TYPE DIO_RegisterRead(uint32_t address)
{

}

/**********************************************************************
 * Function: DIO_CallbackRegister()
*//**
 *\b Description:
 * This function is used to set the callback function of the dio driver.
 * By default, the callbacks are initialized to a NULL pointer. The 
 * driver may contain more than one possible callback, so the function
 * will take a parameter to configure the specified callback.
 * 
 * PRE-CONDITION: The DioCallback_t has been populated.
 * PRE-CONDITION: The callback function exists within memory.
 * 
 * POST-CONDITION: The specified callback function will be registered 
 * with the driver.
 * 
 * @param   function is the callback function that will be registered.
 * @param   callbackFunction is a function pointer to the desired 
 * function.
 * 
 * @return None
 * 
 * \b Example:
 * @code
 *  DioCallback_t Dio_Function = DIO_SAMPLE_COMPLETE;
 *  DIO_CallbackRegister(Dio_Function, Dio_SampleAverage);
 * @endcode
 * 
 * @see DIO_Init
 * @see DIO_ChannelRead
 * @see DIO_ChannelWrite
 * @see DIO_ChannelToggle
 * @see DIO_RegisterWrite
 * @see DIO_RegisterRead
 * @see DIO_CallbackRegister
 * 
 **********************************************************************/ 
void DIO_CallbackRegister(DioCallback_t Function, TYPE (*CallbackFunction)(type))
{
    
}