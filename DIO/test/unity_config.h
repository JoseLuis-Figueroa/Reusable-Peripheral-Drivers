/**
 * @file unity_config.h
 * @author Jose Luis Figueroa
 * @brief This header contains the function prototype and macros for 
 * the Unity test framework configuration for UART output on the 
 * Nucleo-F401RE board.
 * @version 1.2
 * @date 2025-nov-03
 * 
 * @copyright Copyright (c) 2025 Jose Luis Figueroa. MIT License.
 * 
*/
#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

/*****************************************************************************
* Preprocessor Macros
*****************************************************************************/
// Define NULL if not already defined
#ifndef NULL
#ifndef __cplusplus
// In C, NULL is defined as a void pointer
#define NULL ((void*)0)
#else
// In C++, NULL is defined as integer 0
#define NULL 0
#endif
#endif

// Support for C++ compilation
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* Function Prototypes for Unity test output handling
*****************************************************************************/
// Called at the start of test execution
void unityOutputStart();
// Called to output a single character during test execution
void unityOutputChar(char);
// Called to flush output buffer
void unityOutputFlush();
// Called when test execution is complete
void unityOutputComplete();

// Unity configuration macros that map to our custom output functions
#define UNITY_OUTPUT_START()    unityOutputStart()
#define UNITY_OUTPUT_CHAR(c)    unityOutputChar(c)
#define UNITY_OUTPUT_FLUSH()    unityOutputFlush()
#define UNITY_OUTPUT_COMPLETE() unityOutputComplete()

// End C++ extern "C" block
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* UNITY_CONFIG_H */