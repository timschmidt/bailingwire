#ifndef CORE_BOARDS_H
#define CORE_BOARDS_H

// bitmask describing the capabilities of a single pin
// data structure holding all those bitmasks for each board
// everything that provides GPIO provides a list of these bitmasks for each of it's pins.

/**
 * Atmega 328p
 * 
 * 32kb flash
 * 1kb EEPROM
 * 2kb SRAM
 * 2x 8 bit timer / counters - prescaler, compare
 * 1x 16bit timer / counter - prescaler, compare, capture
 * 1x real time counter
 * 6x PWM channels
 * 8-channel 10-bit ADC
 * programmable uart
 * master / slave SPI interface
 * i2c interface
 * watchdog
 * analog comparator
 * interrupt and wake-up on pin change
 * programmable brown-out protection
 * Six Sleep Modes: Idle, ADC Noise Reduction, Power-save, Power-down, Standby, and Extended Standby
 * 23 Programmable I/O Lines
 * 
 */
 
/**
 * Atmega 324p
 * 
 * 32kb flash
 * 1kb EEPROM
 * 2kb SRAM
 * 2x 8 bit timer / counters - prescaler, compare
 * 1x 16bit timer / counter - prescaler, compare, capture
 * 1x real time counter
 * 6x PWM channels
 * 8-channel 10-bit ADC
 * programmable uart
 * master / slave SPI interface
 * i2c interface
 * watchdog
 * analog comparator
 * interrupt and wake-up on pin change
 * programmable brown-out protection
 * Six Sleep Modes: Idle, ADC Noise Reduction, Power-save, Power-down, Standby, and Extended Standby
 * 32 Programmable I/O Lines
 * 
 */
 
/**
 * 
 * Atmega 2560
 * 
 * 256kb flash
 * 4kb EEPROM
 * 8kb SRAM
 * Atmel Qtouch capatitive touch support - 64 channels
 * JTAG interface
 * 2x 8 bit timer / counters - prescaler, compare
 * 4x 16bit timer / counter - prescaler, compare, capture
 * real time counter
 * 4x 8bit PWM channels
 * 12x 2 - 16bit PWM channels
 * output compare modulator
 * 16 channel 10-bit ADC
 * 4x uarts
 * master / slave SPI interface
 * i2c interface
 * watchdog
 * analog comparator
 * interrupt and wake-up on pin change
 * programmable brown-out protection
 * Six Sleep Modes: Idle, ADC Noise Reduction, Power-save, Power-down, Standby, and Extended Standby
 * 86 programmable i/o lines
 */
  
/**
 * 
 * Parallax Propeller
 * 
 * 8 cores
 * 2 timers per core
 * 2 video registers per core
 * 2Kb SRAM per core
 * 32Kb RAM, 32Kb ROM accessible to all cores, round-robin
 * ROM contains bitmap font, base 2 2048 entry log table, base 2 2048 entry antilog table, sine table (16-bit, 2049 entries representing first quadrant, angles from 0 to π/2; other three quadrants are created from the same table).
 * From Wikipedia: "The math extensions are intended to help compensate for the lack of a floating-point unit as well as more primitive missing operations, such as multiplication and division (this is masked in Spin but is a limitation for assembly language routines). The Propeller is a 32-bit processor, however, and these tables may not have sufficient accuracy for higher-precision applications."
 * no interrupts - spin up a core, and ask it to poll a pin state
 * no ADC, I2C, Serial, SPI, etc. - spin up a core and bit-bang the protocol.  Mmmmm.  Hardwareish.
 * 32 programmable i/o lines accessible to all cores
 */
  
#endif // CORE_BOARDS_H
