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
 
#ifndef DRIVER_ULN2003_STEPPER_H
#define DRIVER_ULN2003_STEPPER_H

struct device_descriptor
{
	// Public API
	int device_type = DEVICE_TYPE_STEPPER;
	int &step(int direction);
	
	// Private API
	int *gpio_1;
	int *gpio_2;
	int *gpio_3;
	int *gpio_4;
	int direction;
	int steps_per_revolution;
	long long position;
}

// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, and return a pointer to the memory address of the struct
function alloc_uln2003_stepper()
{
	return calloc( sizeof(struct device_descriptor) );
}

function init_uln2003_stepper()
{
	
}

function step(int direction)
{
	analogWrite(gpio, brightness);
}

#endif // DRIVER_ULN2003_STEPPER_H
