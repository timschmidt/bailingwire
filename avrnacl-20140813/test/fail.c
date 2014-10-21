/*
 * File:    test/fail.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Thu Jul 24 14:04:59 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "fail.h"
#include "print.h"
#include "avr.h"

void fail(const char *error)
{
  print("ERROR: ");
  print(error);
  print("\n");
  avr_end();
  exit(-1);
}
