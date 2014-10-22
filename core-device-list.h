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

#include <stdlib.h>

// Device types (function call interfaces)
// Move to core-constants
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

extern int device_count;
extern int *device_list;

function init_device_list()
{
    device_list = calloc( sizeof(int) );
    *device_list = &root_device;
}

/* realloc's *device_list to (devices * 1 byte), updating device_list,
 * and stores the new device's data in the last position.
 */
function add_device( int driver )
{
	int *temp_device_list;
	if ((temp_device_list = realloc(device_list, sizeof(int) * (device_count + 1))) == NULL)
	{
		error( 1 ); // Device list reallocation failed: out of memory
	}
	device_list = temp_device_list;
	device_list[device_count] = drivers[driver];
	device_count++;
}

/* Moves the last device into the position of the device being removed,
 * realloc's *device_list to be one device shorter.
 * Shrinking an allocation with realloc should always succeed.
 */
function remove_device( int device )
{
	int i;	
	for (i = 0; i < device_count; i++) // this will skip the root device, at device_list[0]
	{
		if (device_list[i] == device)
		{
			device_list[i] = device_list[device_count];
			break;
		}
	}
	free(device);
	realloc(device_list, sizeof(int) * (device_count - 1));
}

#endif // CORE_DEVICE_LIST_H
