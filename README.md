# Reusable Drivers

**Introduction.**

This personal project was performed with the acquired knowledge based on the _“Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers”_ book where the objective is to create reusable firmware development that can be used across multiple microcontroller platforms and software products.  This is achieved through embedded C (Bare-metal) code that works directly with the microcontroller (MCU) register map, following industry-standard coding practices such as MISRA-C.

**Project Overview.**

The repository consists of creating reusable drivers, and HALs for MCU. The current tooling being used for this project includes:
* Development Board: _Nucleo-F401RE._
* IDE/Debugger: _Visual Studio Code (PlatformIO extension)._
* Compiler Toolchain: _GNU ARM Embedded Toolchain._

**General Propose Input/Output (GPIO).**

The main code consists of configuring the user button (PC13 pin) as an input. When pressed, the button turns on the embedded led (PA5) on the board and turns off the yellow led (PB0 pin) by writing directly to the ORD register. Conversely, when the button is released, the embedded led is turned off, and the yellow led is turned on. The red led (PA0 pin) is set to toggle, although this behavior may not be apparent as a delay is not currently implemented (it will be implemented later), but it can be seen in debug mode. Additionally, the value of PC13 is obtained by reading directly from the IDR register, and if the user button is pressed, a corresponding message is printed on the console. The main purpose of this code is to implement and test the GPIO driver. The doxygen documentation can be found in [Digital Input/Output Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/main/Documentation/Doxygen/DIO/output_files/html/index.html). The video shows the implementation in a development board. 

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/assets/113542682/7324bd6a-fac1-4b3b-a10d-abe7818b59bd" alt="DIO_Implementation">
</p>

**Serial Peripheral Interface (SPI).**

The code involves the configuration of a Serial Peripheral Interface. The GPIO driver is employed to set up the SPI1 pins as follows: PA5 for SCK, PA6 for MISO, PA7 for MOSI, and PA9 for SS. The SPI driver is used to configure the SPI1 as a master device. The setting includes a baud rate = 4KHz, full duplex communication, an 8 bits data frame format, and most significant bit transmission.
A KY-57 logic analyzer is connected to the master device for data reception and analysis. The main code continuously transmits data to the logic analyzer, with the current involving the transmission of 0x56. The doxygen documentation can be found in [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/main/Documentation/Doxygen/SPI/output_files/html/index.html). A video showcases the physical implementation of the SPI driver for a visual demonstration, while an accompanying image displays the data captured and analyzed on the logic analyzer. 

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/assets/113542682/f02b5172-8913-499b-b7c0-ef087a645344" alt="[SPI_Implementation">
</p>

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/assets/113542682/4b9f9b89-4a98-4f69-9e67-45bdb6536647" alt="[SPI Protocol" width="100%">
</p>

Note that this repository is a work in progress, and additional peripherical drivers such as SPI slave, Timer, I2C, and more will be added in the future. Each driver will be well documented automatically using Doxygen and implemented in a development board.

_Thank you for visiting my project repository, and I hope you find it useful!_
