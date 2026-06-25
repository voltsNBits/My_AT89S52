# AT89S52 Driver Library

A collection of bare-metal peripheral drivers written for the AT89S52 (8051-compatible) microcontroller.

This library was developed as part of my embedded systems learning journey to gain hands-on experience with low-level embedded programming, register-level configuration, and modular driver development using C.

## Features

Currently implemented drivers:

- LCD Driver
  - Character LCD interfacing
  - Data and command handling

- UART Driver
  - Serial communication
  - Configurable baud rate support

- Timer Driver
  - Timer initialization and configuration

- Servo Driver
  - PWM generation using timers
  - Basic servo position control

- Watchdog Driver
  - Watchdog initialization
  - Refresh/reset functionality

## Project Structure

```text
AT89S52_Library/
├── LCD/
├── SERVO/
├── TIMER/
├── UART/
├── WATCHDOG/
└── device.h
```

## Hardware

- Microcontroller: AT89S52
- Architecture: 8051
- Programming Languages:
  - Embedded C
- Development Environment:
  - Keil µVision / Keil C51

## Learning Objectives

This project was created to:

- Understand 8051 architecture
- Practice register-level programming
- Develop reusable embedded drivers
- Learn peripheral interfacing
- Build a foundation for ARM Cortex-M and RTOS-based development


## License

This project is licensed under the MIT License.
