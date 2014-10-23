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
 
#ifndef COORDINATES_POLAR_H
#define COORDINATES_POLAR_H

// input: function describing x over t, function describing y over t, function describing z over t?
// output: function describing a over t, function describing r over t?

// Three, or two coordinates?  In what polar configuration?  Polar/linear Linear/Polar?

void cartesian_to_delta()
{
	radius = sqrt(x^2 + y^2);
	angle = arctan(y / x);
}

void delta_to_cartesian()
{
	
}

#endif // COORDINATES_POLAR_H
