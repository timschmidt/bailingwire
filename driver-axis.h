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
 
#ifndef DRIVER_AXIS_H
#define DRIVER_AXIS_H

// consumes: pointer to: one actuator, one sensor, one feedback device, and one control loop
// returns: pointer to: one axis

function home(){
	
}

struct device_descriptor
{
	int &home();
	int *actuator;
	int *feedback;
	int *control_loop;
	int *endstop;
	int *native_units;
	double length;
	
}

function init_axis()
{
	int axis = calloc( sizeof(struct device_descriptor) );
	if (axis !=0)
	{
		// populate struct
	}
	return axis;
}

#endif // DRIVER_AXIS_H
