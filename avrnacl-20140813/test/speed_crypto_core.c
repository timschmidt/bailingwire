/*
 * File:    test/speed_crypto_core.c
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

#undef crypto_core
#undef crypto_core_OUTPUTBYTES
#undef crypto_core_INPUTBYTES
#undef crypto_core_KEYBYTES
#undef crypto_core_CONSTBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_core             XCONCAT(crypto_core_,PRIMITIVE)
#define crypto_core_OUTPUTBYTES XCONCAT3(crypto_core_,PRIMITIVE,_OUTPUTBYTES)
#define crypto_core_INPUTBYTES  XCONCAT3(crypto_core_,PRIMITIVE,_INPUTBYTES)
#define crypto_core_KEYBYTES    XCONCAT3(crypto_core_,PRIMITIVE,_KEYBYTES)
#define crypto_core_CONSTBYTES  XCONCAT3(crypto_core_,PRIMITIVE,_CONSTBYTES)

static unsigned char *h;
static unsigned char *n;
static unsigned char *k;
static unsigned char *c;

#define hlen crypto_core_OUTPUTBYTES
#define nlen crypto_core_INPUTBYTES
#define klen crypto_core_KEYBYTES
#define clen crypto_core_CONSTBYTES

int main(void)
{
  unsigned int i;
  unsigned long long t[NRUNS];

  h = calloc(hlen,1);
  if(!h) fail("allocation of h failed");
  n = calloc(nlen,1);
  if(!n) fail("allocation of n failed");
  k = calloc(klen,1);
  if(!k) fail("allocation of k failed");
  c = calloc(clen,1);
  if(!c) fail("allocation of c failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_core(h,n,k,c);
  }
  print_speed(XSTR(crypto_core),-1,t,NRUNS);

  free(h);
  free(n);
  free(k);
  free(c);

  avr_end();
  return 0;
}
