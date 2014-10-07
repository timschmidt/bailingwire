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
 * 
 *  Based on code from http://appelsiini.net/2011/simple-usart-with-avr-libc
 *  MIT License: http://www.opensource.org/licenses/mit-license.php
 *  Copyright 2011 Mika Tuupola
 *  Modified 2014 Timothy Schmidt
 * 
 * Todo:
 *  - verify buffer size (check avr-libc), reduce buffer size to 32ish bytes
 *  - modify to conform to bailingwire driver model
 *  - write comms helper functions - can they write to the command buffer
 *    (or just return to a helper function which does) more directly?
 */
 
#ifndef DRIVER_AVRSERIAL_H
#define DRIVER_AVRSERIAL_H

#include <stdio.h>
#include <avr/io.h>

// must be defined (along with F_CPU in core-boards.h) before including setbaud.h 
#define BAUD 115200

#include <util/setbaud.h>

// input: AVR serial port parameters
// output: function pointer(s) to serial interface

void uart_init(void)
{
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

  #if USE_2X
    UCSR0A |= _BV(U2X0);
  #else
    UCSR0A &= ~(_BV(U2X0));
  #endif

  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void uart_putchar(char c, FILE *stream)
{
  if (c == '\n')
  {
    uart_putchar('\r', stream);
  }
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
}

char uart_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
  return UDR0;
}

/* FDEV_SETUP_STREAM macro can be used to setup a buffer which is valid
 * for stdio operations. Initialized buffer will be of type FILE. You
 * can define separate buffers for input and output. Alternatively you
 * can define only one buffer which works for both input and output.
 * First and second parameters are names of the functions which will be
 * called when data is either read from or written to the buffer.
 */
//FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

FILE uart_io FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

#endif // DRIVER_AVRSERIAL_H
