/*
 *  This file is part of the bailingwire firmware.
 *
 *  Bailingwire is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Bailingwire is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Bailingwire.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef CORE_DEVICE_LIST_H
#define CORE_DEVICE_LIST_H

int device_count;
int *device_list;

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
// 33: feedback - encoder wheel, quadrature, etc.

// Drivers:
// Array pointing to driver initializtion functions
void (*drivers[10]) = {
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
}

function init_device_list()
{
    device_list = calloc( 1 );
    // store the root device
}

function add_device( int driver )
{
	// realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
	int new_device_list = realloc(device_list, device_count + 1);
	if (new_device_list != 0) device_list = new_device_list;
	*(device_list + device_count) = (*drivers[driver])();
	device_count++;
}

function remove_device( struct *device )
{
	// moves device-to-be-removed to the last position, realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
	
}

#endif // CORE_DEVICE_LIST_H
