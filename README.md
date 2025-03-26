# Reusable Drivers

## Introduction

This project is a personal initiative inspired by the book _"Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers."_ The goal is to develop reusable firmware that can be applied across multiple microcontroller platforms and software products.

The firmware is implemented in **embedded C (Bare-metal)**, directly interfacing with the microcontroller (MCU) register map. It follows **industry-standard coding practices**, including **MISRA-C**, to ensure reliability and maintainability.

## Project Overview

This repository focuses on developing **reusable drivers** and **Hardware Abstraction Layers (HALs)** for MCUs. The tools used in this project include:

### **Development Environment**
- **Development Board:** _Nucleo-F401RE._
- **Logic Analyzer:** _KY-57_.
- **IDE & Debugger:** _Visual Studio Code (PlatformIO extension)._
- **Compiler Toolchain:** _GNU ARM Embedded Toolchain._

---

## General-Purpose Input/Output (GPIO)

1. The DIO codes configure the **user button (PC13)** as an input. 

    When pressed:
    - The **embedded LED (PA5)** turns **on**.
    - The **yellow LED (PB0)** turns **off**, and its state is read **directly from the ODR register**.

    When released:
    - the LEDs **revert to their original states**. 

2. The **red LED (PA0)** toggles (without a delay, it can be observed in debugging mode). 

3. Additionally, the PC13 is also read **directly from the IDR register.**

This implementation serves as a **test and validation of the GPIO driver**. A video demonstration provides a visual representation of the physical implementation of the DIO driver.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/assets/113542682/7324bd6a-fac1-4b3b-a10d-abe7818b59bd" alt="DIO_Implementation">
</p>

Please refer to the Doxygen documentation available in the [Digital Input/Output Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/main/Documentation/Doxygen/DIO/output_files/html/index.html) for detailed documentation.

---

## Serial Peripheral Interface (SPI)

The SPI codes configure **SPI1 as a master device** with the following settings:
- **Baud rate:** 4 kHz
- **Communication mode:** Full duplex
- **Data frame format:** 8-bit
- **Bit transmission order:** Most Significant Bit (MSB) first  

A **KY-57 logic analyzer** is connected to the master device for data reception and analysis. The GPIO driver configures the SPI1 pins for proper operation.

### **Pin Connections**

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

The master continuously transmits data to the logic analyzer, currently sending **0x56**. Below is a screenshot of the captured data:

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/blob/main/Documentation/Doxygen/SPI/imagens/SPI%20Master%20Screen.png" alt="[SPI Protocol" width="100%">
</p>

Please refer to the Doxygen documentation available in the [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/readme/Documentation/Doxygen/SPI/output_files/html/index.html) for detailed documentation.

---

## Serial Peripheral Interface (Master-Slave)

This implementation configures two **Nucleo-F401RE boards** for SPI communication:
- One board acts as the **master**, and the other as the **slave**.
- Both use **SPI1** for communication.
- The configuration includes:
    - **Baud rate:** 4 kHz.
    - **Comunication mode:** Full-duplex communication.
    - **Data frame format:** 8-bit.
    - **Bit transmission order:** Most significant bit (MSB) first.

### **Pin Connections**
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

The **slave device continuously transmits** a **0x66 value**, which the master receives and echoes back to the slave. A KY-57 logic analyzer is used to monitor the data exchange.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/blob/main/Documentation/Doxygen/SPI_Master_Slave/imagens/SPI_Master_Slave_v2.png" alt="[SPI Protocol" width="100%">
</p>

Please refer to the Doxygen documentation available in the [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/readme/Documentation/Doxygen/SPI_Master_Slave/output_files/html/index.html) for detailed documentation.

---

## Conclusion

Reusable firmware development is a powerful approach for building embedded systems as it enhances scalability, maintainability, and efficiency. By designing firmware that can be reused across different microcontrollers and projects, developers can reduce development time, minimize errors, and improve code consistency.

Additionally, adhering to industry standards like MISRA-C and leveraging Hardware Abstraction Layers (HALs) ensures portability and flexibility, allowing the same firmware to be adapted to different hardware platforms with minimal modifications. This approach ultimately leads to cost-effective, reliable, and high-quality embedded solutions, making it an essential practice in modern firmware development.
