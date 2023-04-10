/**
 * @file dio.h
 * @author Jose Luis Figueroa
 * @brief The interface definition for the dio. This is the header file for 
 * the definition of the interface for a digital input/output peripheral on 
 * a standard microcontroller.
 * @version 1.0
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023 Jose Luis Figueroa. All rights reserved.
 * 
 */
#ifndef DIO_H_
#define DIO_H_

/*****************************************************************************
* Includes
*****************************************************************************/
#include <stdint.h>
#include "dio_cfg.h"    /*For dio configuration*/

/*****************************************************************************
* Preprocessor Constants
*****************************************************************************/

/*****************************************************************************
* Configuration Constants
*****************************************************************************/

/*****************************************************************************
* Macros
*****************************************************************************/

/*****************************************************************************
* Typedefs
*****************************************************************************/

/*****************************************************************************
* Variables
*****************************************************************************/

/*****************************************************************************
* Function Prototypes
*****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void DIO_Init(const DioConfig_t * const Config);
DioPinState_t DIO_ChannelRead(DioChannel_t Channel);
void DIO_ChannelWrite(DioChannel_t Channel, DioPinState_t State);
void DIO_ChannelToggle(DioChannel_t Channel);
void DIO_RegisterWrite(uint32_t address, TYPE value);
TYPE DIO_RegisterRead(uint32_t address);
void DIO_CallbackRegister(DioCallback_t Funtion, TYPE(*CallbackFunction)(type));

#ifdef __cplusplus
} // extern C
#endif

#endif /*DIO_H_*/