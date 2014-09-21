/*  This file is part of the bailingwire firmware.
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

int device_count;
int *device_list;

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
	(*device_list[device_count]) = (*drivers[driver])();
	device_count++;
}

function remove_device( struct *device )
{
	// moves device-to-be-removed to the last position, realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
	
}

#endif // CORE_DEVICE_LIST_H
