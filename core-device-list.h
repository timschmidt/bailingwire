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

#include <avr/pgmspace.h>

// Device types (function call interfaces)
#define DEVICE_TYPE_ACCELLEROMETER		1
#define DEVICE_TYPE_BAROMETER 			2
#define DEVICE_TYPE_BATTERY				3 // check status, time left
#define DEVICE_TYPE_COLOR_SENSOR		4 // get color
#define DEVICE_TYPE_CONDUCTIVITY_SENSOR	5 // get conductivity
#define DEVICE_TYPE_CURRENT_SENSOR		6 // get current
#define DEVICE_TYPE_DISTANCE_SENSOR		7 // get distance
#define DEVICE_TYPE_EXTRUDER			8 // extrude X mm? ml?
#define DEVICE_TYPE_FAN					9 // set fan speed (percent)
#define DEVICE_TYPE_FLOW_SENSOR			10 // get flow (volume / time)
#define DEVICE_TYPE_GPIO				11
#define DEVICE_TYPE_HEATER				12
#define DEVICE_TYPE_HUMIDITY			13
#define DEVICE_TYPE_LASER				14
#define DEVICE_TYPE_LCD					15
#define DEVICE_TYPE_LED					16 // set light intensity
#define DEVICE_TYPE_LIGHT_SENSOR		17
#define DEVICE_TYPE_MOTOR				18 // move (direction, distance, time)
#define DEVICE_TYPE_PH_SENSOR			19
#define DEVICE_TYPE_PUMP				20
#define DEVICE_TYPE_RELAY				21
#define DEVICE_TYPE_RTC					22
#define DEVICE_TYPE_SD					23
#define DEVICE_TYPE_SERVO				24
#define DEVICE_TYPE_SOIL_MOISTURE		25
#define DEVICE_TYPE_SOLENOID			26
#define DEVICE_TYPE_STEPPER				27
#define DEVICE_TYPE_SWITCH				28
#define DEVICE_TYPE_TEMP_SENSOR			29
#define DEVICE_TYPE_VALVE				30
#define DEVICE_TYPE_VOLTAGE_SENSOR		31
#define DEVICE_TYPE_WIND_SENSOR			32
#define DEVICE_TYPE_FEEDBACK			33 // 33: feedback - encoder wheel, quadrature, etc.

/*
 * Loading a Driver:
 * - find the function pointer to the driver's initialization function in the *drivers array
 * - run it.  it will return a pointer to the memory address of the data structure describing the instance of that driver which you have just created.
 * - the first 8 bits of data at the driver's memory address describe the type of interface that driver provides (motor, gpio, fan, etc)
 * - 
 * 
 */
 
int device_count;
int *device_list;

// Drivers:
// Array pointing to driver initializtion functions
void (*drivers[10]) = {
	&alloc_avr_gpio,
	&alloc_8574_i2c_gpio,
	&alloc_attiny,
	&alloc_avreeprom,
	&alloc_avrserial,
	&alloc_axis,
	&alloc_ftdi,
	&alloc_nrf24l01,
	&alloc_qtouch,
	&alloc_uln2003
}

prog_char driver_0[] PROGMEM = "AVR GPIO";
prog_char driver_1[] PROGMEM = "8574 I2C GPIO Expander";
prog_char driver_2[] PROGMEM = "ATTiny Serial";
prog_char driver_3[] PROGMEM = "AVR EEPROM";
prog_char driver_4[] PROGMEM = "AVR Serial";
prog_char driver_5[] PROGMEM = "Axis virtual driver";
prog_char driver_6[] PROGMEM = "FTDI Serial";
prog_char driver_7[] PROGMEM = "NRF24L01+ Networking";
prog_char driver_8[] PROGMEM = "QTouch";
prog_char driver_9[] PROGMEM = "ULN2003 Stepper Motor";

// Then set up a table to refer to our strings.
PROGMEM const char *driver_descriptions[] =
{   
	driver_0,
	driver_1,
	driver_2,
	driver_3,
	driver_4,
	driver_5,
	driver_6,
	driver_7,
	driver_8,
	driver_9
};



char buffer[30]; // make sure this is large enough for the largest string it must hold
strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Copy string from program memory into buffer - casts and dereferencing are necessary



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
