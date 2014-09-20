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
 
#ifndef DRIVER_AVR_GPIO_H
#define DRIVER_AVR_GPIO_H

struct device_descriptor
{
	// Public API
	int device_type = DEVICE_TYPE_GPIO;
	int &set_pin_state(int *device_descriptor, int state);
	int pin;
	int state;
	
	//Private API
	
}

function alloc_avr_gpio()
{
	return calloc( sizeof(struct device_descriptor) );
}

function init_avr_gpio(int *device_descriptor, int pin, int state)
{
	*(device_descriptor + 2) = pin;
	*(device_descriptor + 1)(*device_descriptor, state);
}

function set_pin_state(int *device_descriptor, int state)
{
	digitalWrite(*(device_descriptor + 3), state);
}

#endif // DRIVER_AVR_GPIO_H
