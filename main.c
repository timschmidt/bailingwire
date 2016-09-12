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
 
// Accelleration in Marlin is accomplished by scaling the interrupt timer shared by all axes, uniformly scaling the pre-computed stepping ratios.  How to accomplish per-axis accelleration curves without incurring a per-tick re-evaluation of each axis's acceleration curve function?

// use promises to evaluate dynamic ladder-logic style constraints?  Better models?
// command / function list:
//  - call a per-coordinate system auto probing for axis _

// test memory consumption / efficiency / api
// c linked lists: https://gist.github.com/obedrios/2957439
// cpp linked lists: https://gist.github.com/obedrios/3008397
// c calloc / free: http://www.cplusplus.com/reference/cstdlib/calloc/ http://www.cplusplus.com/reference/cstdlib/free/
// cpp new / delete: http://www.cplusplus.com/reference/new/operator%20new/

#include <stdlib.h>
#include "devices.h"

void error( int error_number )
{
	// look up error text in core-constants, and output to serial, LCD
	// per-device error handling? - not initially
}

int setup(void) {
	unsigned char* buffer;
	buffer = (unsigned char*)calloc(4, 32); // buffer 4x 32byte commands
	unsigned char* current_command = buffer;
	
	init_device_list();
	
	uart_init();  // from driver-avrserial.h
	stdout = &uart_output;
    stdin  = &uart_input;
    unsigned char input;
    
    // todo: board initialization
}

int main(void) {
	while (nothing bad happens)
	{
	
	//iterate through an array of function pointers to services, which have been pushed onto the linked list by a serial command
	
		puts("Hello world!");
        input = getchar();
        printf("You wrote %c\n", input);
	}
}
