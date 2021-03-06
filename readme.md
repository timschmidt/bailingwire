# Bailingwire Device Control Firmware

Bailingwire uses a powerful hardware abstraction model to provide per-axis runtime reconfigurable geometry, feedback, and control algorithms for a wide variety of actuators, sensors, and other hardware.

## Goals
 - near 100% runtime reconfigurability
 - support hot pluggable hardware
 - per-axis configurable geometry (cartesian, delta, polar, etc.)
 - support for boards with standardized connectors like GROVE
 - first-class support for closed-loop servo and/or stepper control
 - no hard-coded policy (movement rules, overheat protection, etc.), but support for dynamically constructing it
 - fits in 2kb ram
 - fits in 32kb flash

## Plan
 - fix remaining compilation errors
 - establish working serial communication
 - using the dynamic hardware driver model, control an LED's illumination via serial commands
 - establish working i2c <-> 8754 <-> uln2003 <-> stepper I/O cascade
 - modify existing GROVE drivers to work within the dynamic driver model

## Sponsors
 - device model: mUVe3D ( https://www.muve3d.net )
 - parallax propeller support: ?

## Structure
### Core
 - Configured at compile time
 - Microcontroller-specific
 - Board-specific
 - Hardware-agnostic high-level device interfaces
 - transparent unit conversion

### Driver
 - a struct containing data and pointers to one or more functions.
 - when the struct is allocated in memory, initialized, and a pointer to it is added to the driver list, it's loaded.
 - first byte is a DEVICE_TYPE identifier
 - second byte is a function pointer to an initialization function
 - followed by device class specific interface function pointers and data at defined offsets
 - followed by driver specific data and function pointers at undefined offsets
 - each driver provides one, and consumes one or more of these pre-defined function pointer interfaces
 - device function cascades from the most abstract device interfaces to the most hardware-specific.
 - standard interfaces defined for GPIO, serial, PWM, ADC, I2C, 1Wire, EEPROM, various I/O expansion ICs, networking ICs, motor control ICs, motors, pumps, solenoids, lights, heaters, fans, servos, sensors (flow, conductivity, ph, light, humidity, temperature, accellerometers, etc.)
 - configurable at run time

### Feedback
 - comsumed by the i/o interrupt handler
 - i/o interrupt handler runs when a hardware interrupt happens (a pin changes state, or serial packet is recieved, etc.)
 - the i/o interrupt handler passes calls the 'state-change' function pointed to by the feedback struct
 - the state-change function performs a driver-specific calculation and updates/returns? the associated axis' position

### Control
 - algorithms for determining when a machine should act based on sensor input
 - regulate air/fluid flow, temperature, concentrations in fluids, light intensity, voltage, etc.
 - configurable per-axis, at runtime

### Coordinates
 - provide function pointers with compatible interfaces to convert from cartesian coordinates (used in the core kinematic models) and per-axis native coordinates in real, automatically converted to per-axis native units

### Service
 - runs in the idle loop

## Files
boards.h - contains a list of supported microcontrollers and microcontroller boards.  loads hardware drivers for the board chosen in config.h
config.h - contains all compile-time configuration settings
constants.h - functions for storing constants in EEPROM, flash, and SRAM, depending on the speed and frequency of access required.
control-bangbang.h - bangbang control algorithm
control-pid.h - PID control algorithm
devices.h - list of supported device types and functions for loading / unloading device drivers
drivers.h - functions for loading drivers - combind with devices.h
interrupts.h - interrupt handling functions
main.c
Makefile-AVR - build for AVR
Makefile-common
Makefile-example
Makefile-SIM - build simulator
model-ideal.h - machine state goal
model-past.h - machine state reality
readme.md - this file
timer.h - hardware timer / comparater functions
units.h - functions for fast binary unit conversion
watchdog.h - functions for using the watchdog safety hardware
services/gcode.h - interruptable functions for parsing + interpreting gcode protocol
services/opensbp.h - interruptable functions for parsing + interpreting opensbp protocol
services/repetier.h - interruptable functions for parsing + interpreting repetier binary protocol
services/ladderlogic.h - 
services/log.h
services/network.h

##Todo:
 - improve code readability by defining macros, or similar for standard function call interfaces functions, core functions.
 - build 8 / 32bit compatibility layer for Propeller
 - build propeller cog -> interrupt handler interface in core-interrupt.h
 - write constant storage / retrieval functions
 - pull in code for all GROVE hardware - audit licenses
 - implement fast sqrt approximation from teacup firmware
 - connect setup() to board initialization function, do serial port setup at board initialization
 - poll serial port for commands to buffer from recurring interrupt
 - check for full buffer, call protocol handler from main() idle loop
 

Serial Communications Protocol Notes:
 
Packet-based, binary, one device 'command' per packet.  Each packet is prefixed by a XX byte device ID, and each packet's payload is 0 to 32 bytes long.  All packets, reguardless of address prefix, are sent to the same serial connection from the HOST.  The DEVICE on the recieving side of that serial connection will route the packets apropriately.

Need packet / line numbers for re-send requests
  
Checksums - see nRF datasheet


## License
Bailingwire is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Bailingwire is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Bailingwire.  If not, see <http://www.gnu.org/licenses/>.
