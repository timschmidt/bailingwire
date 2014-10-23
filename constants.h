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
 
#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

// #ifdefs / functions for storing and retrieving constants (at compile time) in program space, EEPROM, or SRAM

#include <avr/pgmspace.h>

/*prog_char      - a signed char (1 byte) -127 to 128
 *prog_uchar     - an unsigned char (1 byte) 0 to 255
 *prog_int16_t   - a signed int (2 bytes) -32,767 to 32,768
 *prog_uint16_t  - an unsigned int (2 bytes) 0 to 65,535
 *prog_int32_t   - a signed long (4 bytes) -2,147,483,648 to * 2,147,483,647.
 *prog_uint32_t  - an unsigned long (4 bytes) 0 to 4,294,967,295
 */

array prog_char[3] PROGMEM = ["a", "b", "c"];

// Error messages go here:
prog_char error_message_device_memory[] PROGMEM = "Device list reallocation failed: out of memory";

const char *error_messages[] =
{
   error_message_device_memory
};

/* Multpliers for unit conversion - we use multiplication for speed.
 * These should always be stored in SRAM for the same reason.
 * float * float = 2 cycles
 * float / float = 5,000 cycles
 */
extern float unit_conversions[5] = [
	1,			// millimeter
	1 / 10,		// centimeter
	1 / 1000,	// meter
	1 / 25.4,	// inch
	1 / 304.8	// foot
]
  
#endif // CORE_CONSTANTS_H
