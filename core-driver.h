#ifndef CORE_DEVICES_H
#define CORE_DEVICES_H

#include <avr/pgmspace.h>

// define public methods, for these objects:
// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, function pointers to the public methods for that device as implemented by it's driver, and return a pointer to the memory address of the struct

// PROGMEM array pointing to driver initializtion functions
array prog_char[32] PROGMEM = [
	&init_accelerometer			// 1: accelerometer 
	&init_barometer				// 2: barometer
	&init_battery				// 3: battery - check status, time left
	&init_colorsensor			// 4: color sensor - get color
	&init_conductivitysensor	// 5: conductivity sensor - get conductivity
	&init_currentsensor			// 6: current sensor - get current
	&init_distancesensor		// 7: distance sensor - get distance
	&init_extruder				// 8: extruder - extrude X mm? ml?
	&init_fan					// 9: fan - set fan speed (percent)
	&init_flowsensor			// 10: flow sensor - get flow (volume / time)
	&init_gpio					// 11: gpio - 
	&init_heater				// 12: heater - 
	&init_humidity				// 13: humidity - 
	&init_laser					// 14: laser - 
	&init_lcd					// 15: lcd - 
	&init_led					// 16: led - set light intensity
	&init_lightsensor			// 17: light sensor - 
	&init_motor					// 18: motor - move (direction, distance, time)
	&init_phsensor				// 19: ph sensor - 
	&init_pump					// 20: pump - 
	&init_relay					// 21: relay - 
	&init_rtc					// 22: rtc - 
	&init_sd					// 23: sd - 
	&init_servo					// 24: servo - 
	&init_soilmoisture			// 25: soil moisture - 
	&init_solenoid				// 26: solenoid - 
	&init_stepper				// 27: stepper - 
	&init_swtich				// 28: switch - 
	&init_tempsensor			// 29: temp sensor - 
	&init_valve					// 30: valve - 
	&init_voltagesensor			// 31: voltage sensor - 
	&init_windsensor			// 32: wind sensor - 
];

function initialize_driver( int driver )
{
	
};

#endif // CORE_DEVICES_H
