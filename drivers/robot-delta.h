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
 
#ifndef COORDINATES_DELTA_H
#define COORDINATES_DELTA_H

// pre-calculated:
// input: function describing x over t, function describing y over t, function describing z over t
// output: function describing a over t, function describing b over t, function describing c over t

// instantaneous:
// input: x, y, z (cartesian coordinates)
// output: a, b, c (steps? how to manage servos?) - accelleration model

// Where's calibration go?  Per-coordinate system?
// Where's (plugable) probing?  main loop evaluator?

#endif // COORDINATES_DELTA_H
