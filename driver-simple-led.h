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

function set_led(int gpio, float brightness){
	analogWrite(gpio, brightness);
}

struct device_descriptor
{
	int &set_led(int gpio, int brightness);
	int *gpio;
	float brightness;
}

// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, and return a pointer to the memory address of the struct
function init_simple_led(int gpio)
{
	int simple_led = calloc( sizeof(struct device_descriptor) );
	if (simple_led !=0)
	{
		*(simple_led + 1) = gpio;
	}
	return simple_led;
}
#endif // DRIVER_SIMPLE_LED_H
