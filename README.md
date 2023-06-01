# Reusable-Drivers
This repository contains a personal project based on the _“Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers”_ book where the objective is to create reusable firmware development that can be used across multiple microcontroller platforms and software products.  This is achieved through embedded C (Bare-metal) code that works directly with the register map of the microcontroller (MCU), following industry-standard coding practices as MISRA-C. The project is focused on creating reusable drivers and HALs for MCU.

This repository currently contains the GPIO driver. The main code consists on configuring the user button (PC13 pin) as an input. When the button is pressed, it turns on the embedded led (PA5) on the board and turns off the yellow led (PB0 pin) by writting derectly to the ORD register. Conversely, when the button is released, the emdedded led is turned off, and the yellow led is turned on. The red led (PA0 pin) is set to toggle, although this behavior may not be apparent as a delay is not currently implemented (it will be implemented later), but it can be seen in debug mode. Additionally, the value of PC13 is obtained by reading directly from the IDR register, and if the user button is pressed, a corresponding message is printed on the console. The main purpose of this code is to implement and test the GPIO driver. The video shows the implementation in a development board. 

![DIO_Implementation](https://github.com/JoseLuis-Figueroa/Reusable-Drivers/assets/113542682/7324bd6a-fac1-4b3b-a10d-abe7818b59bd)

The current tooling being used for this project includes:
* Development Board: _Nucleo-F401RE._
* IDE/Debugger: _Visual Studio Code (PlatformIO extension)._
* Compiler Toolchain: _GNU ARM Embedded Toolchain._

Note that this repository is a work in progress, and additional peripherical drivers such as SPI, Timer, I2C, and more will be added in the future. Each driver will be well documented automatically using Doxygen and implemented in a development board. The project documentation can be found in [Reusable drivers.](https://joseluis-figueroa.github.io/Reusable-Drivers/)

_Thank you for visiting my project repository, and I hope you find it useful!_

