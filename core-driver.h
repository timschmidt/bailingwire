#ifndef CORE_DEVICES_H
#define CORE_DEVICES_H

#include <avr/pgmspace.h>

// define public methods, for these objects:
// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, function pointers to the public methods for that device as implemented by it's driver, and return a pointer to the memory address of the struct

// Device types (function call interfaces)
// 1: accelerometer 
// 2: barometer
// 3: battery - check status, time left
// 4: color sensor - get color
// 5: conductivity sensor - get conductivity
// 6: current sensor - get current
// 7: distance sensor - get distance
// 8: extruder - extrude X mm? ml?
// 9: fan - set fan speed (percent)
// 10: flow sensor - get flow (volume / time)
// 11: gpio - 
// 12: heater - 
// 13: humidity - 
// 14: laser - 
// 15: lcd - 
// 16: led - set light intensity
// 17: light sensor - 
// 18: motor - move (direction, distance, time)
// 19: ph sensor - 
// 20: pump - 
// 21: relay - 
// 22: rtc - 
// 23: sd - 
// 24: servo - 
// 25: soil moisture - 
// 26: solenoid - 
// 27: stepper - 
// 28: switch - 
// 29: temp sensor - 
// 30: valve - 
// 31: voltage sensor - 
// 32: wind sensor - 

// Drivers:
// PROGMEM array pointing to driver initializtion functions
array prog_char[32] PROGMEM = [
	&init_8574_i2c_gpio,
	&init_attiny,
	&init_avreeprom,
	&init_avrgpio,
	&init_avrserial,
	&init_axis,
	&init_ftdi,
	&init_nrf24l01,
	&init_qtouch,
	&init_uln2003
];

function initialize_driver( int driver )
{
	
};

#endif // CORE_DEVICES_H
