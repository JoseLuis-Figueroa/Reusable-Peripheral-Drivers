/**
 * @file spi.c
 * @author Jose Luis Figueroa 
 * @brief The implementation for the SPI.
 * @version 1.0
 * @date 2023-07-14
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. MIT License.
 * 
 */
/*****************************************************************************
* Includes
*****************************************************************************/
#include "spi.h"

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
/** TODO: Populate all the peripheral register with the proper instances*/
/**
 * Defines a table of pointers to the peripheral input register on the 
 * microcontroller.
*/


/*****************************************************************************
* Function Prototypes
*****************************************************************************/

/*****************************************************************************
* Function Definitions
*****************************************************************************/
/*****************************************************************************
 * Function: SPI_init()
*//**
*\b Description:
 * This function is used to initialize the spi based on the configuration  
 * table defined in spi_cfg module.
 * 
 * PRE-CONDITION: Configuration table needs to be populated (sizeof > 0) <br>
 * PRE-CONDITION: SPI pins should be configured using GPIO driver.
 * PRE-CONDITION: The MCU clocks must be configured and enabled.
 * 
 * POST-CONDITION: The peripheral is set up with the configuration settings.
 * 
 * @param[in]   Config is a pointer to the configuration table that contains 
 *               the initialization for the peripheral.
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 *  const SpiConfig_t * const SpiConfig = SPI_configGet();
 *  SPI_Init(DioConfig);
 * @endcode
 * 
 * @see SPI_ConfigGet
 * @see SPI_Init
 * @see SPI_Transfer
 * @see SPI_RegisterWrite
 * @see SPI_RegisterRead
 * @see SPI_CallbackRegister
 * 
*****************************************************************************/
void SPI_Init(SpiConfig_t const * const Config)
{
    /** TODO: Define implementation*/
}

/**********************************************************************
 * Function: SPI_Transfer()
*//**
 *\b Description:
 * This function is used to initialize a data transfer on the SPI bus. 
 * 
 * PRE-CONDITION: SPI_Init must be called with valid configuration data.
 * PRE-CONDITION: SpiTransfer_t must be configured for the device.
 * PRE-CONDITION: The MCU clocks must be configured and enabled.
 * 
 * POST-CONDITION: Data transferred based on configuration.
 * 
 * @param[in]   Config is a configured structure describing the data  
 * transfer that occurs.
 *
 * 
 * @return  void
 * 
 * \b Example:
 * @code
 *  const SpiConfig_t * const SpiConfig = SPI_ConfigGet();
 * @endcode
 * 
 * @see SPI_ConfigGet
 * @see SPI_Init
 * @see SPI_Transfer
 * @see SPI_RegisterWrite
 * @see SPI_RegisterRead
 * @see SPI_CallbackRegister
 * 
 **********************************************************************/
void SPI_Transfer(uint16_t *data, uint16_t size)
{
    /** TODO: define implementation*/
}

/**********************************************************************
 * Function: SPI_registerWrite()
*//**
 *\b Description:
 * This function is used to directly address and modify a SPI register.
 * The function should be used to access specialized functionality in 
 * the SPI peripheral that is not exposed by any other function of the
 * interface.
 * 
 * PRE-CONDITION: Address is within the boundaries of the SPI register
 * address space.
 * 
 * POST-CONDITION: The register located at address with be updated with
 * value.
 * 
 * @param[in]   address is a register address within the SPI peripheral
 *              map.
 * @param[in]   value is the value to set the SPI register. 
 * 
 * @return void
 * 
 * \b Example
 * @code
 *  SPI_registerWrite(0x1000, 0x15);
 * @endcode
 * 
 * @see SPI_ConfigGet
 * @see SPI_Init
 * @see SPI_Transfer
 * @see SPI_RegisterWrite
 * @see SPI_RegisterRead
 * @see SPI_CallbackRegister
 * 
**********************************************************************/  
void SPI_RegisterWrite(uint32_t address, TYPE value)
{
    /** TODO: define implementation*/
}

/**********************************************************************
 * Function: SPI_registerRead()
*//**
 *\b Description:
 * This function is used to directly address a SPI register. The 
 * function should be used to access specialized functionality in the 
 * SPI peripheral that is not exposed by any other function of the 
 * interface.
 * 
 * PRE-CONDITION: Address is within the boundaries of the SPI register 
 * address space.
 * 
 * POST-CONDITION: The value stored in the register is returned to the 
 * caller.
 * 
 * @param[in]   address is the address of the SPI register to read.
 * 
 * @return  The current value of the SPI register.
 * 
 * \b Example:
 * @code
 * type spiValue = SPI_registerRead(0x1000);
 * @endcode
 * 
 * @see SPI_ConfigGet
 * @see SPI_Init
 * @see SPI_Transfer
 * @see SPI_RegisterWrite
 * @see SPI_RegisterRead
 * @see SPI_CallbackRegister
 *
 **********************************************************************/
TYPE SPI_RegisterRead(uint32_t address)
{
    /** TODO: Define implementation*/
}