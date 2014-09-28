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

/* The regular interrupt handler makes use of a timer and comparator to execute
 * a list of functions at regular intervals.  The regular interrupt handler provides
 * the heartbeat of the firmware.  It's enabled dynamically, when devices which
 * require regular servicing are loaded.
 * 
 * The regular interrupt handler is responsible for stepper motors, temperature
 * sensors, luminance sensors, etc.
 */
extern int regular_interrupt_count;
extern int *regular_interrupt_list;

/* The pin change interrupt handler configures the interrupt hardware to monitor
 * the state of a pin, or group of pins, and runs only when the state of those pins
 * changes in a pre-defined way.  When it's run, the pin change interrupt handler
 * attempts to determine which pin caused the interrupt, and then runs only the
 * interrupt handling function associated with that pin.
 * 
 * The pin change interrupt handler is responsible for endstops, feedback
 * hardware like quadrature encoders and flow sensors, buttons, etc.
 */
extern int pin_interrupt_count;
extern int *pin_interrupt_list;

function init_regular_interrupt_list(int interrupt_handler)
{
    regular_interrupt_list = calloc( sizeof(int) );
    *regular_interrupt_list = &interrupt_handler;
}

function init_pin_interrupt_list(int interrupt_handler)
{
    pin_interrupt_list = calloc( sizeof(int) );
    *pin_interrupt_list = &interrupt_handler;
}

/* realloc's *regular_interrupt_list to (regular_interrupt_count * 1 byte), updating regular_interrupt_list,
 * and stores the new interrupt handler's pointer in the last position.
 */
function add_regular_interrupt( int interrupt_handler )
{
	int *temp_list;
	if ((temp_list = realloc(regular_interrupt_list, sizeof(int) * (regular_interrupt_count + 1))) == NULL)
	{
		error( 1 ); // Device list reallocation failed: out of memory
	}
	regular_interrupt_list = temp_list;
	regular_interrupt_list[regular_interrupt_count] = interrupt_handler;
	regular_interrupt_count++;
}

/* Moves the last interrupt handler into the position of the 
 * interrupt handler being removed, realloc's *regular_interrupt_list
 * to be one interrupt handler shorter.  Shrinking an allocation with
 * realloc should always succeed.
 */
function remove_regular_interrupt( int interrupt_handler )
{
	int i;	
	for (i = 0; i < regular_interrupt_count; i++) // this will skip the root device, at device_list[0]
	{
		if (regular_interrupt_list[i] == interrupt_handler)
		{
			regular_interrupt_list[i] = regular_interrupt_list[regular_interrupt_count];
			break;
		}
	}
	realloc(regular_interrupt_list, sizeof(int) * (regular_interrupt_count - 1));
}

/* realloc's *pin_interrupt_list to (pin_interrupt_count * 1 byte), updating pin_interrupt_list,
 * and stores the new interrupt handler's pointer in the last position.
 */
function add_pin_interrupt( int interrupt_handler )
{
	int *temp_list;
	if ((temp_list = realloc(pin_interrupt_list, sizeof(int) * (pin_interrupt_count + 1))) == NULL)
	{
		error( 1 ); // Device list reallocation failed: out of memory
	}
	pin_interrupt_list = temp_list;
	pin_interrupt_list[pin_interrupt_count] = interrupt_handler;
	pin_interrupt_count++;
}

/* Moves the last interrupt handler into the position of the 
 * interrupt handler being removed, realloc's *pin_interrupt_list
 * to be one interrupt handler shorter.  Shrinking an allocation with
 * realloc should always succeed.
 */
function remove_pin_interrupt( int interrupt_handler )
{
	int i;	
	for (i = 0; i < pin_interrupt_count; i++) // this will skip the root device, at device_list[0]
	{
		if (pin_interrupt_list[i] == interrupt_handler)
		{
			pin_interrupt_list[i] = pin_interrupt_list[pin_interrupt_count];
			break;
		}
	}
	realloc(pin_interrupt_list, sizeof(int) * (pin_interrupt_count - 1));
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

#ifdef AVR328
	// 16bit counter
	ISR(TIMER1_COMPA_vect)
	{
		int i;
		
		for (i = -1; i < regular_interrupt_count; i++)
		{
			(*regular_interrupt_list[i])();
		}
	}
	
	// 8bit counter
	ISR(TIMER2_COMPA_vect)
	{

	}
	
	// 8bit counter
	ISR(TIMER3_COMPA_vect)
	{

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
