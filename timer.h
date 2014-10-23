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
 
#ifndef TIMER_H
#define TIMER_H

// - stepper driver interrupt - fires at machine resolution through time
// - servo / endstop interrupt - watches pins, and quickly evaluates when they're triggered
//  - is this an endstop?
//  - is this a servo?  (call feedback function), adjust speed


// convert these into a single invariant function w/ lookup table in progmem
void timer3_init(int pin) {
	pinMode(pin, OUTPUT);
    analogWrite(pin, 1);  // let Arduino setup do it's thing to the PWM pin

    TCCR3B = 0x00;  // stop Timer4 clock for register updates
    TCCR3A = 0x82; // Clear OC3A on match, fast PWM mode, lower WGM3x=14
    ICR3 = labs(F_CPU / LASER_PWM); // clock cycles per PWM pulse
    OCR3A = labs(F_CPU / LASER_PWM) - 1; // ICR3 - 1 force immediate compare on next tick
    TCCR3B = 0x18 | 0x01; // upper WGM4x = 14, clock sel = prescaler, start running

    noInterrupts();
    TCCR3B &= 0xf8; // stop timer, OC3A may be active now
    TCNT3 = labs(F_CPU / LASER_PWM); // force immediate compare on next tick
    ICR3 = labs(F_CPU / LASER_PWM); // set new PWM period
    TCCR3B |= 0x01; // start the timer with proper prescaler value
    interrupts();
}

void timer4_init(int pin) {
	pinMode(pin, OUTPUT);
    analogWrite(pin, 1);  // let Arduino setup do it's thing to the PWM pin

    TCCR4B = 0x00;  // stop Timer4 clock for register updates
    TCCR4A = 0x82; // Clear OC4A on match, fast PWM mode, lower WGM4x=14
    ICR4 = labs(F_CPU / LASER_PWM); // clock cycles per PWM pulse
    OCR4A = labs(F_CPU / LASER_PWM) - 1; // ICR4 - 1 force immediate compare on next tick
    TCCR4B = 0x18 | 0x01; // upper WGM4x = 14, clock sel = prescaler, start running

    noInterrupts();
    TCCR4B &= 0xf8; // stop timer, OC4A may be active now
    TCNT4 = labs(F_CPU / LASER_PWM); // force immediate compare on next tick
    ICR4 = labs(F_CPU / LASER_PWM); // set new PWM period
    TCCR4B |= 0x01; // start the timer with proper prescaler value
    interrupts();
}

void laser_init()
{
  // Initialize timers for laser intensity control
  #if LASER_CONTROL == 1
    if (LASER_FIRING_PIN == 2 || LASER_FIRING_PIN == 3 || LASER_FIRING_PIN == 5) timer3_init(LASER_FIRING_PIN);
    if (LASER_FIRING_PIN == 6 || LASER_FIRING_PIN == 7 || LASER_FIRING_PIN == 8) timer4_init(LASER_FIRING_PIN);
  #endif
  #if LASER_CONTROL == 2
    if (LASER_INTENSITY_PIN == 2 || LASER_INTENSITY_PIN == 3 || LASER_INTENSITY_PIN == 5) timer3_init(LASER_INTENSITY_PIN);
    if (LASER_INTENSITY_PIN == 6 || LASER_INTENSITY_PIN == 7 || LASER_INTENSITY_PIN == 8) timer4_init(LASER_INTENSITY_PIN);
  #endif
}

#endif // TIMER_H
