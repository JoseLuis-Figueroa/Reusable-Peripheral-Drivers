# Reusable Drivers

**Introduction.**

This personal project was performed with the acquired knowledge based on the _“Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers”_ book where the objective is to create reusable firmware development that can be used across multiple microcontroller platforms and software products.  This is achieved through embedded C (Bare-metal) code that works directly with the microcontroller (MCU) register map, following industry-standard coding practices such as MISRA-C.

**Project Overview.**

The repository consists of creating reusable drivers, and HALs for MCU. The current tooling being used for this project includes:
* Development Board: _Nucleo-F401RE._
* IDE/Debugger: _Visual Studio Code (PlatformIO extension)._
* Compiler Toolchain: _GNU ARM Embedded Toolchain._

**General Propose Input/Output (GPIO).**

The main code consists of configuring the user button (PC13 pin) as an input. When pressed, the button turns on the embedded LED (PA5) on the board and turns off the yellow LED (PB0 pin) by writing directly to the ORD register. Conversely, when the button is released, the embedded LED is turned off, and the yellow LED is turned on. The red LED (PA0 pin) is set to toggle, although this behavior may not be apparent as a delay is not currently implemented (it will be implemented later), but it can be seen in debug mode. Additionally, the value of PC13 is obtained by reading directly from the IDR register, and if the user button is pressed, a corresponding message is printed on the console.

The main purpose of this code is to implement and test the GPIO driver. A video demonstration provides a visual representation of the DIO driver's physical implementation.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/assets/113542682/7324bd6a-fac1-4b3b-a10d-abe7818b59bd" alt="DIO_Implementation">
</p>

Please refer to the Doxygen documentation available in [Digital Input/Output Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/main/Documentation/Doxygen/DIO/output_files/html/index.html) for detailed documentation.

**Serial Peripheral Interface (SPI).**

The code involves the configuration of a Serial Peripheral Interface. The SPI driver is used to configure the SPI1 as a master device. The setting includes a baud rate = 4KHz, full duplex communication, an 8-bit data frame format, and most significant bit transmission.
A KY-57 logic analyzer is connected to the master device for data reception and analysis. To establish the physical connections, the GPIO driver configures the SPI1 pins. The following table illustrates the pin connections among the Nucleo board, and KY-57 logic analyzer:

<div align="center">
<table>
  <tr>
    <th>SPI Connection</th>
    <th>Master</th>
    <th>Logic Analyzer</th>
  </tr>
  <tr>
    <td>NSS</td>
    <td>PA9</td>
    <td>CH4</td>
  </tr>
  <tr>
    <td>SCK</td>
    <td>PA5</td>
    <td>CH1</td>
  </tr>
  <tr>
    <td>MISO</td>
    <td>PA6</td>
    <td>CH2</td>
  </tr>
  <tr>
    <td>MOSI</td>
    <td>PA7</td>
    <td>CH3</td>
  </tr>
</table>
</div>

The main code continuously transmits data to the logic analyzer, with the current involving the transmission of 0x56. An image displays the data captured and analyzed on the logic analyzer. 

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/blob/main/Documentation/Doxygen/SPI/imagens/SPI%20Master%20Screen.png" alt="[SPI Protocol" width="100%">
</p>

Please refer to the Doxygen documentation available in [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/readme/Documentation/Doxygen/SPI/output_files/html/index.html) for detailed documentation.

**Serial Peripheral Interface (Master-Slave)**

In this setup, the Serial Peripheral Interface (SPI) driver is configuring two Nucleo-F401RE boards, designating one as the master and the other as the slave, employing the SPI1 channel on both boards. The SPI configuration includes a baud rate = 4kHz, enabling full duplex communication, employing an 8-bit data frame format, and prioritizing the most significant bit transmission. To establish the physical connections, the GPIO driver configures the SPI1 pins. The following table illustrates the pin connections among the master board, slave board, and the KY-57 logic analyzer:

<div align="center">
<table>
  <tr>
    <th>SPI connection</th>
    <th>Master</th>
    <th>Slave</th>
    <th>Logic analyzer</th>
  </tr>
  <tr>
    <td>NSS</td>
    <td>PA4</td>
    <td>PA4</td>
    <td>CH4</td>
  </tr>
  <tr>
    <td>SCK</td>
    <td>PA5</td>
    <td>PA5</td>
    <td>CH1</td>
  </tr>
  <tr>
    <td>MISO</td>
    <td>PA6</td>
    <td>PA6</td>
    <td>CH2</td>
  </tr>
  <tr>
    <td>MOSI</td>
    <td>PA7</td>
    <td>PA7</td>
    <td>CH3</td>
  </tr>
</table>
</div>

In operation, the slave continually transmits a 0x66 value to the master device, which receives it and sends it back to the slave. The KY-57 logic analyzer is connected to capture and analyze the data exchanged between the two of them.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/blob/main/Documentation/Doxygen/SPI_Master_Slave/imagens/SPI_Master_Slave_v2.png" alt="[SPI Protocol" width="100%">
</p>

Please refer to the Doxygen documentation available in the [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/readme/Documentation/Doxygen/SPI_Master_Slave/output_files/html/index.html) for detailed documentation. Additionally, an accompanying image showcases the data captured and analyzed on the logic analyzer.

**Note.**

This repository is a work in progress, and additional peripherical drivers such as Timer, I2C, and more will be added in the future. Each driver will be well documented automatically using Doxygen and implemented in a development board.

_Thank you for visiting my project repository, and I hope you find it useful!_
