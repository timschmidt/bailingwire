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

#include <avr/interrupt.h>

/* describe regular interrupts or pin interrupts in the same data structure?
 */
struct interrupt_handler
{
	// Public API
	void *handler;
	int interrupt_type;
	int identifier;
	
	//Private API
	
}
/***********************************************************************
 * The recurring interrupt handler makes use of a timer and comparator
 * (on AVR / ARM, or a cog on Propeller) to execute a list of functions
 * at regular intervals.  The recurring interrupt handler provides the
 * heartbeat of the firmware.
 * 
 * It's enabled dynamically, when devices which require regular
 * servicing are loaded.
 * 
 * The recurring interrupt handler is responsible for stepper motors,
 * temperature sensors, luminance sensors, etc.
 **********************************************************************/
extern int recurring_interrupt_count;
extern int *recurring_interrupt_list;

void init_recurring_interrupt_list(int interrupt_handler)
{
    recurring_interrupt_list = calloc( sizeof(int) );
    *recurring_interrupt_list = &interrupt_handler;
}

/* realloc's *recurring_interrupt_list to (recurring_interrupt_count * 1 byte),
 * updating recurring_interrupt_list, and stores the new interrupt
 * handler's pointer in the last position.
 */
void add_recurring_interrupt( int interrupt_handler )
{
	int *temp_list;
	if ((temp_list = realloc(recurring_interrupt_list, sizeof(int) * (recurring_interrupt_count + 1))) == NULL)
	{
		error( 1 ); // Device list reallocation failed: out of memory
	}
	recurring_interrupt_list = temp_list;
	recurring_interrupt_list[recuring_interrupt_count] = interrupt_handler;
	recurring_interrupt_count++;
}

/* Moves the last interrupt handler into the position of the 
 * interrupt handler being removed, realloc's *recurring_interrupt_list
 * to be one interrupt handler shorter.  Shrinking an allocation with
 * realloc should always succeed.
 */
void remove_recurring_interrupt( int interrupt_handler )
{
	int i;	
	for (i = 0; i < recuring_interrupt_count; i++) // this will skip the root device, at device_list[0]
	{
		if (recurring_interrupt_list[i] == interrupt_handler)
		{
			recuring_interrupt_list[i] = recurring_interrupt_list[recurring_interrupt_count];
			break;
		}
	}
	realloc(recurring_interrupt_list, sizeof(int) * (recurring_interrupt_count - 1));
}

void recurring_interrupts()
{
	int i;
		
	for (i = -1; i < recurring_interrupt_count; i++)
	{
		(*recurring_interrupt_list[i])();
	}
}
/***********************************************************************
 * The external interrupt handler configures the interrupt hardware to
 * monitor the state of a pin, or group of pins, and runs only when the
 * state of those pins changes in a pre-defined way.  When it's run, the
 * external interrupt handler attempts to determine which pin caused the
 * interrupt, and then runs only the interrupt handling function
 * associated with that pin.
 * 
 * The external interrupt handler is responsible for endstops, feedback
 * hardware like quadrature encoders and flow sensors, buttons, etc.
 **********************************************************************/
extern int external_interrupt_count;
extern int *external_interrupt_list;

void init_external_interrupt_list(int interrupt_handler)
{
    external_interrupt_list = calloc( sizeof(int) );
    *external_interrupt_list = &interrupt_handler;
}

/* realloc's *external_interrupt_list to (external_interrupt_count * 1 byte),
 * updating external_interrupt_list, and stores the new interrupt
 * handler's pointer in the last position.
 */
void add_external_interrupt( int interrupt_handler )
{
	int *temp_list;
	if ((temp_list = realloc(external_interrupt_list, sizeof(int) * (external_interrupt_count + 1))) == NULL)
	{
		error( 1 ); // Device list reallocation failed: out of memory
	}
	external_interrupt_list = temp_list;
	external_interrupt_list[external_interrupt_count] = interrupt_handler;
	external_interrupt_count++;
}

/* Moves the last interrupt handler into the position of the 
 * interrupt handler being removed, realloc's *external_interrupt_list
 * to be one interrupt handler shorter.  Shrinking an allocation with
 * realloc should always succeed.
 */
void remove_external_interrupt( int interrupt_handler )
{
	int i;	
	for (i = 0; i < external_interrupt_count; i++) // this will skip the root device, at device_list[0]
	{
		if (external_interrupt_list[i] == interrupt_handler)
		{
			external_interrupt_list[i] = external_interrupt_list[external_interrupt_count];
			break;
		}
	}
	realloc(external_interrupt_list, sizeof(int) * (external_interrupt_count - 1));
}

void external_interrupts()
{
	/* reference datasheet for pin interrupt registers / ISR names
	 * populate all associated IVT entries with this function pointer
	 * for now, can implement seperate IVT entries as an optimization
	 * later.
	 */
	
}


/* This is where we populate the Interrupt Vector Table with function
 * pointers to interrupt service routines.
 */
#ifdef AVR328
	// 16bit counter
	ISR(TIMER1_COMPA_vect)
	{
		recurring_interrupts();
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
