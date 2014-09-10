Serial Communications Protocol:
  Packet-based, binary, one device 'command' per packet.  Each packet is prefixed by a XX byte device ID, and each packet's payload is 0 to 32 bytes long.  All packets, reguardless of address prefix, are sent to the same serial connection from the HOST.  The DEVICE on the recieving side of that serial connection will route the packets apropriately.

  Packet / Command IDs for serial-retry - incremental, random, length, location?
  
  Checksums - see nRF datasheet
  
  

Structure:

Core
----
- Configured at compile time
- Microcontroller-specific
- Board-specific

Device / Class (better name?)
------
- Hardware-agnostic high-level device interfaces
- Accept real-world units (inches, litres, minutes), with automatic conversion to per-axis native units
- The interface a hardware-specific driver codes against

Driver
------
- consumes GPIO, serial, i2c, and other hardware-specific function pointers, and provides a function pointer compatible with a DEVICE's calling conventions
- drivers can depend on other drivers - for instance, gpio pin function pointers which point to a GPIO pin function implemented by an i2c GPIO expander IC's driver, which depend on a hardware-specific driver's i2c port function pointer are possible.
- configurable at run time

Feedback
--------
- comsumed by the servo/endstop style pin-change interrupt handler
- processes the interrupt, calling an axis-specific feedback function pointer, calling the configured feedback compatible function, who's duty it is to update the real-time model of the machine for the triggered axis.

Control
-------
- algorithms for determining when a machine should act based on sensor input
- regulate air/fluid flow, temperature, concentrations in fluids, light intensity, voltage, etc.

Coordinates
-----------
- provide function pointers with compatible interfaces to convert from cartesian coordinates (used in the core kinematic models) and per-axis native coordinates in real, automatically converted to per-axis native units

Service
-------
- runs in the idle loop

