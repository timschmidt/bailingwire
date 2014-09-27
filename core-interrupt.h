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
 
#ifndef CORE_INTERRUPT_H
#define CORE_INTERRUPT_H

/* Dynamically allocate:
 * interrupt for stepper driving - when a driver implementing the stepper interface is loaded, if available.
 *  - realloc memory space for function pointers to interrupt handlers
 * interrupt for pin change watching (solenoid, endstop, feedback encoder) - when a driver implementing the servo interface is loaded, if available.
 *  - read AVR datasheet for how to set up pin change events
 * software interrupt to be polled in the idle loop - always available and running.
 */

extern int regular_interrupt_count;
extern int *regular_interrupt_list;

function init_regular_interrupt_list()
{
    device_list = calloc( sizeof(int) );
    *device_list = &root_device;
}

/* realloc's *device_list to (devices * 1 byte), updating device_list,
 * and stores the new device's data in the last position.
 */
function add_device( int driver )
{
	int *temp_device_list;
	if ((temp_device_list = realloc(device_list, sizeof(int) * (device_count + 1))) == NULL)
	{
		error( 1 ); // Device list reallocation failed: out of memory
	}
	device_list = temp_device_list;
	device_list[device_count] = drivers[driver];
	device_count++;
}

/* Moves the last device into the position of the device being removed,
 * realloc's *device_list to be one device shorter.
 * Shrinking an allocation with realloc should always succeed.
 */
function remove_device( int device )
{
	int i;	
	for (i = 0; i < device_count; i++) // this will skip the root device, at device_list[0]
	{
		if (device_list[i] == device)
		{
			device_list[i] = device_list[device_count];
			break;
		}
	}
	realloc(device_list, sizeof(int) * (device_count - 1));
}

// describe timer interrupts or i/o interrupts in the same data structure
struct interrupt_handler
{
	// Public API
	
	int &interrupt_handler(int *timer_interrupt, float input);
	int low_threshold;
	int high_threshold;
	
	//Private API
	
}

// 8 / 16bit versions?
timed_interrupt()
{
	
}

input_interrupt()
{
	
}

init_timed_interrupt()
{
	// shift function pointer to timed_interrupt() into interrupt vector table for ISR1
}

init_input_interrupt()
{
	// shift function pointer to input_interrupt() into interrupt vector table for ISR1
}

#ifdef AVR328
	// 16bit counter 
	ISR(TIMER1_COMPA_vect)
	{
		(*interrupt_handler_1)();
	}
	
	// 8bit counter
	ISR(TIMER2_COMPA_vect)
	{
		(*interrupt_handler_2)();
	}
	
	// 8bit counter
	ISR(TIMER3_COMPA_vect)
	{
		(*interrupt_handler_3)();		
	}
#endif // AVR328
	
#ifdef AVR324

#endif // AVR324

#ifdef AVR2560

#endif //AVR2560

#ifdef PROPELLER
  // spin up a cog to handle each type of interrupt
#endif // PROPELLER




#endif // CORE_INTERRUPT_H
