/*
 * File:    test/speed_crypto_scalarmult.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 5 05:39:21 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "cpucycles.h"
#include "fail.h"
#include "avr.h"

#undef crypto_scalarmult
#undef crypto_scalarmult_base
#undef crypto_scalarmult_BYTES
#undef crypto_scalarmult_SCALARBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_scalarmult             XCONCAT(crypto_scalarmult_,PRIMITIVE)
#define crypto_scalarmult_base        XCONCAT3(crypto_scalarmult_,PRIMITIVE,_base)
#define crypto_scalarmult_BYTES       XCONCAT3(crypto_scalarmult_,PRIMITIVE,_BYTES)
#define crypto_scalarmult_SCALARBYTES XCONCAT3(crypto_scalarmult_,PRIMITIVE,_SCALARBYTES)

#define nlen crypto_scalarmult_SCALARBYTES
#define plen crypto_scalarmult_BYTES

static unsigned char *n;
static unsigned char *p;

int main(void)
{
  unsigned int i;
  unsigned long long t[NRUNS];

  n = calloc(nlen,1);
  if(!n) fail("allocation of n failed");
  p = calloc(plen,1);
  if(!p) fail("allocation of p failed");

  for (i = 0;i < nlen;++i) n[i] = i + 1;
  for (i = 0;i < plen;++i) p[i] = i + 2;


  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_scalarmult_base(p,n);
  }
  print_speed(XSTR(crypto_scalarmult_base),-1,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_scalarmult(p,n,p);
  }
  print_speed(XSTR(crypto_scalarmult),-1,t,NRUNS);


  free(n);
  free(p);

  avr_end();
  return 0;
}
