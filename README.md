# Reusable Embedded Drivers

This repository showcases reusable peripheral driver development and low-level hardware interaction for STM32 microcontrollers, demonstrating the type of **firmware solutions** I can deliver as a **freelancer/firmware engineer**. These reusable drivers are designed with modularity, scalability, and reusability in mind, allowing them to be updated to **support different microcontroller families and vendors**. The drivers are built in **Embedded C** following best practices in firmware development and industry standards such as **MISRA-C**.

---

## Table of Contents

1. [About the Project](#about-the-project)  
2. [Project Status](#project-status)  
3. [Getting Started](#getting-started)  
   1. [Dependencies](#dependencies)  
   2. [Getting the Source](#getting-the-source)  
   3. [Building](#building)  
   4. [Running Tests](#running-tests)  
      1. [Other Tests](#other-tests)  
   5. [Installation](#installation)  
4. [Usage](#usage)  
5. [Release Process](#release-process)  
   1. [Versioning](#versioning)  
   2. [Payload](#payload)  
6. [How to Get Help](#how-to-get-help)  
7. [Contributing](#contributing)  
8. [Further Reading](#further-reading)  
9. [License](#license)  
10. [Authors](#authors)  
11. [Acknowledgments](#acknowledgments)  

---

## About the Project

This project was inspired by **_"Reusable Firmware Development: A Practical Approach to APIs, HALs, and Drivers"_**.  
It aims to abstract hardware-dependent functionality while keeping the codebase minimal and efficient.

### Key Features

- Modular and layered architecture (Drivers, HAL, Application).
- Reusable DIO (GPIO) and SPI drivers for STM32 platforms.
- MISRA-C compliance and bare-metal implementation.
- Doxygen-powered documentation for all modules.
- Demonstrated using Nucleo-F401RE board and KY-57 logic analyzer.

### Technical Details

- **Microcontroller Platform:** STM32F401RE (ARM Cortex-M4).
- **Languages:** Embedded C (Bare-metal).
- **Coding Standards:** MISRA-C.
- **Architecture:** Layered (Driver ↔ Application).
- **Tools:**
  - IDE/Debugger: VS Code + PlatformIO.
  - Compiler: GNU ARM Embedded Toolchain.
  - Logic Analyzer: KY-57.
  - Documentation: Doxygen.

**[Back to top](#table-of-contents)**

---

## Project Status

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

Current Version: `v1.1`  
Tested on: `Nucleo-F401RE`  
- ✅ SPI Master.  
- ✅ SPI Master-Slave.  
- ✅ GPIO Button/LED Control.  
- ⏳ Timer driver (Planned).

**[Back to top](#table-of-contents)**

---

## Getting Started

This guide helps you build and test the firmware on supported microcontrollers.

### Dependencies

Install the following tools:
- [Visual Studio Code](https://code.visualstudio.com/) with [PlatformIO extension](https://platformio.org/install)
- [GNU ARM Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm)
- [STM32Cube Drivers](https://www.st.com/en/ecosystems/stm32cube.html) (via PlatformIO)
- [Doxygen](https://doxygen.nl/manual/install.html) (for documentation)


### Getting the Source

Clone the GitHub repository:

```
git clone https://github.com/JoseLuis-Figueroa/Reusable-Peripheral-Drivers
cd Reusable-Drivers
```

### Building

You can build the project using either the **PlatformIO extension in Visual Studio Code** or the **PlatformIO CLI**.

**Build using the PlatformIO Toolbar (GUI).**

If you're using **VS Code with the PlatformIO extension**, simply click the **"Build" button** in the PlatformIO toolbar. This will compile your project using the selected environment in your `platformio.ini`.

**Build using the PlatformIO CLI.**

From the project's root directory, run the following command to build all environments defined in `platformio.ini`:

```
pio run
```

Build specific environments:

```
pio run -e nucleo_f401re
```

### Running Tests

You can test on actual hardware by uploading the code:

```
pio run --target upload
```

To monitor output:

```
pio device monitor
```

#### Other Tests

- Manual debugging via SWD  
- Logic analyzer (KY-57) signal validation for SPI  
- Static analysis (planned)

### Installation

No separate installation needed—firmware is flashed directly to the microcontroller using the ST-Link interface.

---

## Usage

### General-Purpose Input/Output (GPIO)

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

Please refer to the Doxygen documentation available in the [Digital I/O Doxygen Documentation](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/main/Documentation/Doxygen/DIO/output_files/html/index.html) for detailed documentation.



### Serial Peripheral Interface (SPI)

The SPI codes configure **SPI1 as a master device** with the following settings:
- **Baud rate:** 4 kHz
- **Communication mode:** Full duplex
- **Data frame format:** 8-bit
- **Bit transmission order:** Most Significant Bit (MSB) first  

A **KY-57 logic analyzer** is connected to the master device for data reception and analysis. The GPIO driver configures the SPI1 pins for proper operation.

**Pin Connections**

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



### Serial Peripheral Interface (Master-Slave)

This implementation configures two **Nucleo-F401RE boards** for SPI communication:
- One board acts as the **master**, and the other as the **slave**.
- Both use **SPI1** for communication.
- The configuration includes:
    - **Baud rate:** 4 kHz.
    - **Comunication mode:** Full-duplex communication.
    - **Data frame format:** 8-bit.
    - **Bit transmission order:** Most significant bit (MSB) first.

**Pin Connections**
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


**[Back to top](#table-of-contents)**

---

## Release Process

New features and updates are pushed under versioned tags.

### Versioning

We use [Semantic Versioning](http://semver.org/).  
Latest release: **v1.1**

### Payload

- `v1.0`: GPIO driver for user button and LED  
- `v1.1`: SPI Master and Master-Slave communication

**[Back to top](#table-of-contents)**

---

## How to Get Help

Create an [issue on GitHub](https://github.com/JoseLuis-Figueroa/Reusable-Drivers/issues)  
or contact the author through the GitHub profile.

---

## Contributing

Pull requests are welcome!

Please read [CONTRIBUTING.md](docs/CONTRIBUTING.md) for details on the development process, coding standards, and submission guidelines.

**[Back to top](#table-of-contents)**

---

## Further Reading

- [Reusable Firmware Development](https://www.amazon.com/dp/1732708609) by Jacob Beningo  
- [STM32Cube HAL Drivers](https://www.st.com/en/embedded-software/stm32cubef4.html)  
- [MISRA-C Guidelines](https://www.misra.org.uk/)

---

## License

This project is licensed under the MIT License – see the [LICENSE.md](LICENSE.md) file for details.

---

## Authors

**[JoseLuis-Figueroa](https://github.com/JoseLuis-Figueroa)** – Developer and maintainer

---

## Acknowledgments

- [Beningo Embedded Group](https://www.beningo.com/)  
- [Embedded Artistry](https://github.com/embeddedartistry)  
- STM32 community and PlatformIO

**[Back to top](#table-of-contents)**
