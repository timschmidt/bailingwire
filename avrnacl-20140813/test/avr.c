/*
 * File:    test/avr.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Thu Jul 24 14:04:59 2014 +0200
 * Public Domain
 */

#include "avr.h"
#include "print.h"

void avr_end()
{
  serial_write(4);
  while(1) {};
}
