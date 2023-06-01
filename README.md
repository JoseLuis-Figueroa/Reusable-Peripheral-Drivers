# Reusable-Drivers
This repository contains a personal project based on the _“Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers”_ book where the objective is to create reusable firmware development that can be used across multiple microcontroller platforms and software products.  This is achieved through embedded C (Bare-metal) code that works directly with the register map of the microcontroller (MCU), following industry-standard coding practices as MISRA-C. The project is focused on creating reusable drivers and HALs for MCU.

This repository currently contains the GPIO driver. Note that this repository is a work in progress, and additional peripherical drivers such as SPI, Timer, I2C, and more will be added in the future. Each driver will be well documented automatically using Doxygen and implemented in a development board. The project documentation can be found in [Reusable drivers.](https://joseluis-figueroa.github.io/Reusable-Drivers/)

The current tooling being used for this project includes:
* Development Board: _Nucleo-F401RE._
* IDE/Debugger: _Visual Studio Code (PlatformIO extension)._
* Compiler Toolchain: _GNU ARM Embedded Toolchain._

_Thank you for visiting my project repository, and I hope you find it useful!_

