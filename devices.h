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
 
#ifndef DEVICES_H
#define DEVICES_H

#include <stdlib.h>
#include "boards.h"

// Device types (function call interfaces)
// Move to core-constants
#define DEVICE_TYPE_ROOT				1
#define DEVICE_TYPE_ACCELLEROMETER		2
#define DEVICE_TYPE_BAROMETER 			3
#define DEVICE_TYPE_BATTERY				4 // check status, time left
#define DEVICE_TYPE_COLOR_SENSOR		5 // get color
#define DEVICE_TYPE_CONDUCTIVITY_SENSOR	6 // get conductivity
#define DEVICE_TYPE_CURRENT_SENSOR		7 // get current
#define DEVICE_TYPE_DISTANCE_SENSOR		8 // get distance
#define DEVICE_TYPE_EXTRUDER			9 // extrude X mm? ml?
#define DEVICE_TYPE_FAN					10 // set fan speed (percent)
#define DEVICE_TYPE_FLOW_SENSOR			11 // get flow (volume / time)
#define DEVICE_TYPE_GPIO				12
#define DEVICE_TYPE_HEATER				13
#define DEVICE_TYPE_HUMIDITY			14
#define DEVICE_TYPE_LASER				15
#define DEVICE_TYPE_LCD					16
#define DEVICE_TYPE_LED					17 // set light intensity
#define DEVICE_TYPE_LIGHT_SENSOR		18
#define DEVICE_TYPE_MOTOR				19 // move (direction, distance, time)
#define DEVICE_TYPE_PH_SENSOR			20
#define DEVICE_TYPE_PUMP				21
#define DEVICE_TYPE_RELAY				22
#define DEVICE_TYPE_RTC					23
#define DEVICE_TYPE_SD					24
#define DEVICE_TYPE_SERVO				25
#define DEVICE_TYPE_SOIL_MOISTURE		26
#define DEVICE_TYPE_SOLENOID			27
#define DEVICE_TYPE_STEPPER				28
#define DEVICE_TYPE_SWITCH				29
#define DEVICE_TYPE_TEMP_SENSOR			30
#define DEVICE_TYPE_VALVE				31
#define DEVICE_TYPE_VOLTAGE_SENSOR		32
#define DEVICE_TYPE_WIND_SENSOR			33
#define DEVICE_TYPE_FEEDBACK			34 // 33: feedback - encoder wheel, quadrature, etc.

extern int device_count;
extern int *device_list;

struct
{
	// Public API
	int device_type = DEVICE_TYPE_ROOT;
	  
	// Private API
} root_device;

void init_device_list()
{
    device_list = calloc( 1, sizeof(int) );
    *device_list = &root_device;
}

/* realloc's *device_list to (devices * 1 byte), updating device_list,
 * and stores the new device's data in the last position.
 */
void add_device( int driver )
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
void remove_device( int device )
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

#endif // DEVICES_H
