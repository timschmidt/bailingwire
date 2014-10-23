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
 
#ifndef UNITS_H
#define UNITS_H

/* Use multiplication to convert units for speed
 * float * float = 2 cycles
 * float / float = 5,000 cycles
 */
void convert_time(float time, int units)
{
	return unit_conversions[units] * time;
}

void convert_distance(float distance, int units)
{
	return unit_conversions[units] * distance;
}

void convert_volume(float volume, int units)
{
	return unit_conversions[units] * volume;
}

void convert_speed(float speed, int units)
{
	return unit_conversions[units] * speed;
}

void convert_angle(float angle, int units)
{
	return unit_conversions[units] * angle;
}

#endif // UNITS_H
