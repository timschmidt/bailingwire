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

function set_pin(int *device_descriptor, int state){
	digitalWrite(*(device_descriptor + 1), state);
}

struct device_descriptor
{
	int &set_pin(int *device_descriptor, int state);
	int pin;
	int state;
}

function init_avr_gpio(int pin)
{
	int avr_gpio = calloc( sizeof(struct device_descriptor) );
	if (avr_gpio !=0)
	{
		*(avr_gpio + 1) = pin;
	}
	return avr_gpio;
}
#endif // DRIVER_AVR_GPIO_H
