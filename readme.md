# Bailingwire Device Control Firmware

## Structure:
### Core
- Configured at compile time
- Microcontroller-specific
- Board-specific
- Hardware-agnostic high-level device interfaces
- transparent unit conversion
- The interface a hardware-specific driver codes against

### Driver
- referenced by pointer to a struct which provides a standard device interface in the form of a DEVICE_TYPE identifier, a function pointer to an initialization function, standard device class data and function pointers, and device-specific data and function pointers.
- provides one, and consumes one or more standard device interfaces
- device function cascades from the most abstract device interfaces to the most hardware-specific.
- standard interfaces defined for GPIO, serial, PWM, ADC, I2C, 1Wire, EEPROM, various I/O expansion ICs, networking ICs, motor control ICs, motors, pumps, solenoids, lights, heaters, fans, servos, sensors (flow, conductivity, ph, light, humidity, temperature, accellerometers, etc.)
- configurable at run time

### Feedback
- comsumed by the i/o interrupt handler
- processes the interrupt, calling an axis-specific feedback function pointer, calling the configured feedback compatible function, who's duty it is to update the real-time model of the machine for the triggered axis.

### Control
- algorithms for determining when a machine should act based on sensor input
- regulate air/fluid flow, temperature, concentrations in fluids, light intensity, voltage, etc.
- configurable per-axis, at runtime

### Coordinates
- provide function pointers with compatible interfaces to convert from cartesian coordinates (used in the core kinematic models) and per-axis native coordinates in real, automatically converted to per-axis native units

### Service
- runs in the idle loop


Todo:
 - improve code readability by defining macros, or similar for standard function call interfaces functions, core functions.
 - build 8 / 32bit compatibility layer for Propeller
 - build propeller cog -> interrupt handler interface in core-interrupt.h


Serial Communications Protocol Notes:
  Packet-based, binary, one device 'command' per packet.  Each packet is prefixed by a XX byte device ID, and each packet's payload is 0 to 32 bytes long.  All packets, reguardless of address prefix, are sent to the same serial connection from the HOST.  The DEVICE on the recieving side of that serial connection will route the packets apropriately.

  Packet / Command IDs for serial-retry - incremental, random, length, location?
  
  Checksums - see nRF datasheet

