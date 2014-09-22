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

#endif // PROPELLER




#endif // CORE_INTERRUPT_H
