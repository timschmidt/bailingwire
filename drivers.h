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
 
#ifndef DRIVERS_H
#define DRIVERS_H

#include <avr/pgmspace.h>

/*
 * Loading a Driver:
 * - find the function pointer to the driver's initialization function in the *drivers array
 * - run it.  it will return a pointer to the memory address of the data structure describing the instance of that driver which you have just created.
 * - the first 8 bits of data at the driver's memory address describe the type of interface that driver provides (motor, gpio, fan, etc)
 * - 
 * 
 */

// Drivers:
// Array pointing to driver initializtion functions
// Move to core-constants
void (*drivers[10]) = {
	&alloc_avr_gpio,
	&alloc_8574_i2c_gpio,
	&alloc_attiny,
	&alloc_avreeprom,
	&alloc_avrserial,
	&alloc_axis,
	&alloc_ftdi,
	&alloc_nrf24l01,
	&alloc_qtouch,
	&alloc_uln2003
}

prog_char driver_0[] PROGMEM = "AVR GPIO";
prog_char driver_1[] PROGMEM = "8574 I2C GPIO Expander";
prog_char driver_2[] PROGMEM = "ATTiny Serial";
prog_char driver_3[] PROGMEM = "AVR EEPROM";
prog_char driver_4[] PROGMEM = "AVR Serial";
prog_char driver_5[] PROGMEM = "Axis virtual driver";
prog_char driver_6[] PROGMEM = "FTDI Serial";
prog_char driver_7[] PROGMEM = "NRF24L01+ Networking";
prog_char driver_8[] PROGMEM = "QTouch";
prog_char driver_9[] PROGMEM = "ULN2003 Stepper Motor";

// Then set up a table to refer to our strings.
PROGMEM const char *driver_descriptions[] =
{   
	driver_0,
	driver_1,
	driver_2,
	driver_3,
	driver_4,
	driver_5,
	driver_6,
	driver_7,
	driver_8,
	driver_9
};



char buffer[30]; // make sure this is large enough for the largest string it must hold
strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Copy string from program memory into buffer - casts and dereferencing are necessary

#endif // CORE_DRIVER_LIST_H
