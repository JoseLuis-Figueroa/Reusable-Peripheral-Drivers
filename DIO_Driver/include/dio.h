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
#include <stdio.h>
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

void DIO_init(const DioConfig_t * const Config);
DioPinState_t DIO_pinRead(DioPort_t Port, DioPin_t Pin);
void DIO_pinWrite(DioPort_t Port, DioPin_t Pin, DioPinState_t State);
void DIO_pinToggle(DioPort_t Port, DioPin_t Pin);
void DIO_registerWrite(uint32_t address, uint32_t value);
uint32_t DIO_registerRead(uint32_t address);
/*void DIO_CallbackRegister(DioCallback_t Function, TYPE(*CallbackFunction)(type));*/

#ifdef __cplusplus
} // extern C
#endif

#endif /*DIO_H_*/