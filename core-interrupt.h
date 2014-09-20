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
 
#ifndef CORE_INTERRUPT_H
#define CORE_INTERRUPT_H

// Dynamically allocate:
// interrupt for stepper driving - when a driver implementing the stepper interface is loaded, if available.
// interrupt for pin change watching (solenoid, endstop, feedback encoder) - when a driver implementing the servo interface is loaded, if available.
// software interrupt to be polled in the idle loop - always available and running.

ISR(TIMER1_COMPA_vect)
{
	
	
	
}

ISR(TIMER2_COMPA_vect)
{
	
	
	
}

ISR(TIMER3_COMPA_vect)
{
	
	
	
}

#endif // CORE_INTERRUPT_H
