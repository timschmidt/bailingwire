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

#ifndef CONTROL_BANGBANG_H
#define CONTROL_BANGBANG_H

struct control_descriptor
{
	// Public API
	int &control_bangbang(int *control_descriptor, int input);
	int low_threshold;
	int high_threshold;
	
	//Private API
	
}

function alloc_control_bangbang()
{
	return calloc( sizeof(struct control_descriptor) );
}

function init_control_bangbang(int *control_descriptor, float low_threshold, float high_threshold)
{
	*(control_descriptor + 1) = low_threshold;
	*(control_descriptor + 2) = high_threshold;
}

function control_bangbang(int *control_descriptor, int input)
{
	if (input < *(control_descriptor + 1))
	{
		return 1;
	}
	
	if (input > *(control_descriptor + 2))
	{
		return 0;
	}
}

#endif // CONTROL_BANGBANG_H
