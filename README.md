# Door Opener — STM32F446RE

Building an automatic door opener using the STM32F446RE microcontroller and the STM32 HAL library.

## Goal

Control a door mechanism (motor/servo) using button input or sensors, with the STM32 handling all the GPIO, timers, and peripheral logic via HAL.

## Hardware

- STM32F446RE (Nucleo board)
- Push button (PC13 — onboard)
- LED (PA5 — onboard, for testing)
- Motor/servo driver (to be added)

## Build

Uses CMake with the GNU ARM toolchain. Open in STM32CubeIDE or build via:

```bash
cmake --preset Debug
cmake --build build/Debug
```
