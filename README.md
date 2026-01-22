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
5. [Unit Testing](#unit-testing)
6. [Release Process](#release-process)  
   1. [Versioning](#versioning)  
   2. [Payload](#payload)  
7. [How to Get Help](#how-to-get-help)  
8. [Contributing](#contributing)  
9. [Further Reading](#further-reading)  
10. [License](#license)  
11. [Authors](#authors)  
12. [Acknowledgments](#acknowledgments)  

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

Current Version: `v1.2`  
Tested on: `Nucleo-F401RE`  
- ✅ SPI Master.  
- ✅ SPI Master-Slave.  
- ✅ GPIO Button/LED Control.  
- ✅  Unit Testing (DIO).

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

- **Build using the PlatformIO Toolbar (GUI):** If you're using VS Code with the PlatformIO extension, simply click the "_Build_" button in the PlatformIO toolbar. This will compile your project using the selected environment in your `platformio.ini`.

- **Build using the PlatformIO CLI:** From the project's root directory, run the following command to build all environments defined in `platformio.ini`:

```
pio run
```

- **Build specific environments in CLI:** run the following command to build a specific environment:

```
pio run -e nucleo_f401re
```

### Running Tests

You can test on actual hardware by uploading the code using the **PlatformIO extension in Visual Studio Code** or the **PlatformIO CLI**:

- **Run and debug using the PlatformIO Toolbar (GUI):** If you're using VS Code with the PlatformIO extension, simply click the "_Run and Debug_" button in the PlatformIO toolbar. This will run and debug your project using the selected environment in your `platformio.ini`.

- **Build using the PlatformIO CLI:** From the project's root directory, run the following command to upload all environments defined in `platformio.ini`:

```
pio run --target upload
```

#### Other Tests

- Manual debugging via SWD.  
- Logic analyzer (KY-57) signal validation for SPI.  
- Static analysis (planned).

### Installation

No separate installation needed firmware is flashed directly to the microcontroller using the ST-Link interface.

**[Back to top](#table-of-contents)**

---

## Usage


### General-Purpose Input/Output (DIO)

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

<p align="center">Image 1. DIO Hardware Test.</p>

Please refer to the Doxygen documentation available in the [Digital I/O Doxygen Documentation](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Drivers/main/Documentation/Doxygen/DIO/output_files/html/index.html) for further code information.

### External Interrupt with Callback Functions (DIO_EXTI)

The DIO_EXTI module extends the General-Purpose Input/Output (GPIO) driver by implementing **external interrupts** with **callback functions**. This allows the microcontroller to respond immediately to external events without polling, enabling efficient event-driven programming. When an interrupt occurs, a pre-registered callback function is invoked automatically by the interrupt handler. This application code implements the following routine:
 
When PC13 (User Button) is Pressed:
- EXTI Line 13 detects a falling edge.
- `EXTI15_10_IRQHandler()` is invoked.
- `toggle_led1()` callback is executed.
- **PA5 LED toggles** (on ↔ off).

When PC0 (External Button) is Pressed:
- EXTI Line 0 detects a falling edge.
- `EXTI0_IRQHandler()` is invoked.
- `toggle_led2()` callback is executed.
- **PA0 LED toggles** (on ↔ off).

Simultaneous Button Presses:
If both buttons are pressed simultaneously:
- **EXTI0 (PC0) executes first** due to lower IRQ priority number.
- **EXTI15_10 (PC13) executes after** EXTI0 completes.
- Both LEDs will toggle in sequence.

The benefits of this implementation can seen as follows:

<div align="center">
<table>
  <tr>
    <th>Feature</th>
    <th>Benefit</th>
  </tr>
  <tr>
    <td>Callback Functions</td>
    <td>ecoupled event handling; easy to modify response behavior.</td>
  </tr>
  <tr>
    <td>Hardware Interrupts</td>
    <td>No polling overhead; immediate response to events.</td>
  </tr>
  <tr>
    <td>Flexible Triggers</td>
    <td>Rising/falling edge detection for different button types.</td>
  </tr>
  <tr>
    <td>Multiple EXTI Lines</td>
    <td>Handle multiple simultaneous interrupt sources.</td>
  </tr>
  <tr>
    <td>Priority Support</td>
    <td>Control interrupt execution order via NVIC.</td>
  </tr>
  <tr>
    <td>Modular Configuration</td>
    <td>All settings defined in configuration table.</td>
  </tr>
</table>
</div>

<p align="center">Table 1. EXTI Benefit.</p>

This implementation serves as a **test and validation of the external interrupt**. A video demonstration provides a visual representation of the physical implementation.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Peripheral-Drivers/blob/main/Documentation/Doxygen/DIO/images/EXTI_Implementation.gif" alt="EXTI_Implementation" width="20%">
</p>

<p align="center">Image 2. External Interrupt Hardware Test.</p>

### Serial Peripheral Interface (SPI)

The SPI codes configure **SPI1 as a master device** with the following settings:
- **Baud rate:** 4 kHz
- **Communication mode:** Full duplex
- **Data frame format:** 8-bit
- **Bit transmission order:** Most Significant Bit (MSB) first  

A **KY-57 logic analyzer** is connected to the master device for data reception and analysis. The GPIO driver configures the SPI1 pins for proper operation.

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

<p align="center">Table 2. SPI Pin Connections.</p>

The master continuously transmits data to the logic analyzer, currently sending **0x56**. Below is a screenshot of the captured data:

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/blob/main/Documentation/Doxygen/SPI/imagens/SPI%20Master%20Screen.png" alt="[SPI Protocol" width="100%">
</p>

<p align="center">Image 3. SPI Protocol.</p>

Please refer to the Doxygen documentation available in the [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Peripheral-Drivers/main/Documentation/Doxygen/SPI/output_files/html/index.html) for further code information.


### Serial Peripheral Interface Master-Slave (SPI_Master && SPI slave)

This implementation configures two **Nucleo-F401RE boards** for SPI communication:
- One board acts as the **master**, and the other as the **slave**.
- Both use **SPI1** for communication.
- The configuration includes:
    - **Baud rate:** 4 kHz.
    - **Comunication mode:** Full-duplex communication.
    - **Data frame format:** 8-bit.
    - **Bit transmission order:** Most significant bit (MSB) first.

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

<p align="center">Table 3. Master-Slave Pin Connections.</p>

The **slave device continuously transmits** a **0x66 value**, which the master receives and echoes back to the slave. A KY-57 logic analyzer is used to monitor the data exchange.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Drivers/blob/main/Documentation/Doxygen/SPI_Master_Slave/imagens/SPI_Master_Slave_v2.png" alt="[SPI Protocol" width="100%">
</p>

<p align="center">Image 4. Master-Slave SPI Protocol.</p>

Please refer to the Doxygen documentation available in the [Serial Peripheral Interface Reusable Driver](https://raw.githack.com/JoseLuis-Figueroa/Reusable-Peripheral-Drivers/main/Documentation/Doxygen/SPI_Master_Slave/output_files/html/index.html) for further code information.


**[Back to top](#table-of-contents)**

### Universal Synchronous/Asynchronous Receiver Transmitter (USART)

The USART driver is configured to establish **serial communication** between the **Nucleo-F401RE** board and a **personal computer** via the ST-Link debugger interface. The implementation demonstrates a complete two-way communication system with the following characteristics:
- **Port:** USART2
- **Baud rate:** 9600 bps
- **Data frame format:** 8-bit
- **Stop bits:** 1
- **Parity:** Disabled
- **Communication mode:** Full-duplex (simultaneous transmit and receive)

The following diagram shows how the system connected.

```
Nucleo-F401RE          ST-Link Debugger          PC Terminal Emulator
┌─────────────┐        ┌──────────────┐          ┌──────────────────┐
│   PA2 (TX)  ├───────→│    TX        │─────────→│  RX (Input)      │
│             │        │              │          │                  │
│   PA3 (RX)  │←───────│    RX        │←─────────│  TX (Output)     │
└─────────────┘        └──────────────┘          └──────────────────┘
```
<p align="center">Image 5. USART Connection.</p>

The application code perform a data Reception and LED Control.
   - The application enters an infinite loop, continuously receiving data from the PC.
   - When character `'1'` is received: PA5 embedded LED turns **ON**.
   - When any other character is received: PA5 embedded LED turns **OFF**
   - This demonstrates real-time control of hardware via serial communication

The serial connection operates at **9600 baud** and can be accessed using any terminal emulator (e.g., PuTTY, Tera Term, minicom, or VS Code Serial Monitor) with the following settings:
- Port: Virtual COM Port (from ST-Link)
- Baud Rate: 9600
- Data Bits: 8
- Stop Bits: 1
- Parity: None
- Flow Control: None

This implementation serves as a **test and validation of the USART driver** and provides a foundation for more complex communication applications such as:
- Remote device monitoring.
- Firmware updates over serial.
- Data logging to PC.
- Interactive embedded system configuration.

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Peripheral-Drivers/blob/main/Documentation/Doxygen/USART/images/USART.gif" alt="USART_Implementation" width="20%">
</p>

<p align="center">Image 6. USART Hardware Test.</p>

**[Back to top](#table-of-contents)**

---

## Unit Testing

This project includes target-based unit testing for the DIO driver using the **PlatformIO Unit Testing** Framework and **Unity**. 
Unit testing is executed on the  **Nucleo-F401RE boards** using a custom `unity_config.h` (as documented in PlatformIO’s advanced unit-testing guide).

### Test Framework

- **Framework:** PlatformIO Unity Test Runner.
- **Custom Unity Configuration:** Implemented to redirect Unity output through the platformio.ini environment.
- **Test File:**
   - `test_dio.c` (located in `test/` directory).
- **Framework used in project:** `stm32cube` (instead of CMSIS).

### Running Unit Tests.

You can run unit testing on actual hardware (MCU) by using the **PlatformIO extension in Visual Studio Code** or the **PlatformIO CLI**:

- **Test using the PlatformIO Toolbar (GUI):** If you're using VS Code with the PlatformIO extension, go to the advanced folder and simply click the "_Test_" option in the PlatformIO toolbar. This will build and upload the tests on the host machine using the selected environment in your `platformio.ini`. 

- **Build using the PlatformIO CLI:** From the project's root directory, run the following command to build and upload all tests using the selected environments defined in `platformio.ini`:

```
platformio test
```

### Tests

The following aspects of the DIO driver are verified:
- Correct **initialization** of STM32 GPIO registers.
- **Input data** register behavior.
- **Output data** register behavior.
- **Pin** mapping and functional behavior (write, read, toggle).
- **Register-level** read/write abstractions.

The test results of the `test_dio.c` code can be seen as follow:

<p align="center">
    <img src="https://github.com/JoseLuis-Figueroa/Reusable-Peripheral-Drivers/blob/main/Documentation/Doxygen/DIO/images/DIO-Tests.png" alt="[DIO Unit Testing" width="100%">
</p>

<p align="center">Image 5. Unit Testing Results.</p>


**[Back to top](#table-of-contents)**

---

## Release Process

New features and updates are pushed under versioned tags.

### Versioning

We use [Semantic Versioning](http://semver.org/).  
Latest release: **v1.2**

### Payload

- `v1.0`: Initial release. GPIO and SPI drivers.  
- `v1.1`: Updated documentation, structural improvements, and design by contract enhancements.
- `V1.2`: Implement unit testing on the target.

**[Back to top](#table-of-contents)**

---

## How to Get Help

Create an [issue on GitHub](https://github.com/JoseLuis-Figueroa/Reusable-Drivers/issues) or contact the author through the GitHub profile.

---

## Contributing

Pull requests are welcome!

Please read [CONTRIBUTING.md](/Documentation/CONTRIBUTING.md) for details on the development process, coding standards, and submission guidelines.

**[Back to top](#table-of-contents)**

---

## Further Reading

- [Reusable Firmware Development](https://www.beningo.com/store/developing-reusable-firmware-a-practical-approach-to-apis-hals-and-drivers/) by Jacob Beningo  
- [STM32Cube HAL Drivers](https://www.st.com/en/embedded-software/stm32cubef4.html)  
- [MISRA-C Guidelines](https://www.misra.org.uk/)
- [Unit Testing with PlatformIO](https://docs.platformio.org/en/latest/advanced/unit-testing/index.html)

---

## License

This project is licensed under the MIT License – see the [LICENSE.md](LICENSE) file for details.

---

## Authors

**[JoseLuis-Figueroa](https://github.com/JoseLuis-Figueroa)** – Developer and maintainer

---

## Acknowledgments

- [Beningo Embedded Group](https://www.beningo.com/)  
- [Embedded Artistry](https://github.com/embeddedartistry)  
- STM32 community and PlatformIO

**[Back to top](#table-of-contents)**


