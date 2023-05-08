# Reusable-Drivers
This repository contains a personal project based on the _“Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers”_ book where the objective is to create reusable firmware development that can be used across multiple microcontroller platforms and software products.  This is achieved through embedded C (bare-metal) code that works directly with the register map of the MCU, following industry-standard coding practices as MISRA-C. The project is focused on creating reusable drivers and HALs for MCU.

This repository currently contains the GPIO driver. The current tooling being used for this project includes:
* Development Board: _Nucleo-F401RE._
* IDE/Debugger: _Visual Studio Code (PlatformIO extension)._
* Compiler Toolchain: _GNU ARM Embedded Toolchain._

Please note that this repository is a work in progress, and additional peripherical drivers such as Timer, SPI, I2C, and more will be added in the future. Each driver will be well documented automatically using Doxygen and implemented in a development board. 

_Thank you for visiting my project repository, and I hope you find it useful!_

