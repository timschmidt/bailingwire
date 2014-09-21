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
 
#ifndef DRIVER_SIMPLE_LED_H
#define DRIVER_SIMPLE_LED_H

struct device_descriptor
{
	int DEVICE_TYPE_LIGHT;
	int &set_brightness(int *device_descriptor, float brightness);
	int *gpio;
	float brightness;
}

// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, and return a pointer to the memory address of the struct
function alloc_simple_led()
{
	return calloc( sizeof(struct device_descriptor) );
}

function init_simple_led(int *device_descriptor, int gpio, float brightness)
{
	*(device_descriptor[2]) = gpio;
	*(device_descriptor[3]) = brightness;
	analogWrite(gpio, brightness);
	
}
#endif // DRIVER_SIMPLE_LED_H
