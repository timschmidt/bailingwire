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
 
#ifndef DRIVER_FEEDBACK_QUADRATURE_H
#define DRIVER_FEEDBACK_QUADRATURE_H

/* Quadrature feedback contains enough information to determine speed and direction
 */

struct device_descriptor
{
	// Public API
	int device_type = DEVICE_TYPE_FEEDBACK;
	int &update(int *device_desriptor, int state);
	int pin;
	int state;
	
	// Private API
	float speed;
	float direction;
}

function alloc_feedback_quadrature()
{
	return calloc( sizeof(struct device_descriptor) );
}

function init_feedback_quadrature(int *device_descriptor, int pin, int state)
{
	
}

function update(int *device_descriptor, int state)
{
	
}

#endif // DRIVER_FEEDBACK_QUADRATURE_H
