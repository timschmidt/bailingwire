/*
 * File:    test/speed_crypto_verify.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 5 09:35:45 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "cpucycles.h"
#include "fail.h"
#include "avr.h"

#undef crypto_verify
#undef crypto_verify_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_verify       XCONCAT(crypto_verify_,PRIMITIVE)
#define crypto_verify_BYTES XCONCAT3(crypto_verify_,PRIMITIVE,_BYTES)

static unsigned char *x;
static unsigned char *y;

int main(void)
{
  unsigned int i;
  unsigned long long t[NRUNS];

  x = calloc(crypto_verify_BYTES,1);
  if(!x) fail("allocation of x failed");
  y = calloc(crypto_verify_BYTES,1);
  if(!y) fail("allocation of y failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_verify(x,y);
  }
  print_speed(XSTR(crypto_verify),-1,t,NRUNS);

  free(x);
  free(y);

  avr_end();
  return 0;
}
