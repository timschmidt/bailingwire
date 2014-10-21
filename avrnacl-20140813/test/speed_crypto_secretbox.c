/*
 * File:    test/speed_crypto_secretbox.c
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

#undef crypto_secretbox
#undef crypto_secretbox_open
#undef crypto_secretbox_KEYBYTES
#undef crypto_secretbox_NONCEBYTES
#undef crypto_secretbox_ZEROBYTES
#undef crypto_secretbox_BOXZEROBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_secretbox              XCONCAT(crypto_secretbox_,PRIMITIVE)
#define crypto_secretbox_open         XCONCAT3(crypto_secretbox_,PRIMITIVE,_open)
#define crypto_secretbox_KEYBYTES     XCONCAT3(crypto_secretbox_,PRIMITIVE,_KEYBYTES)
#define crypto_secretbox_NONCEBYTES   XCONCAT3(crypto_secretbox_,PRIMITIVE,_NONCEBYTES)
#define crypto_secretbox_ZEROBYTES    XCONCAT3(crypto_secretbox_,PRIMITIVE,_ZEROBYTES)
#define crypto_secretbox_BOXZEROBYTES XCONCAT3(crypto_secretbox_,PRIMITIVE,_BOXZEROBYTES)

#define MAXTEST_BYTES 1024

static unsigned char *k;
static unsigned char *n;
static unsigned char *c;

#define klen crypto_secretbox_KEYBYTES
#define nlen crypto_secretbox_NONCEBYTES

int main(void)
{
  unsigned int i,j,mlen;
  unsigned long long t[NRUNS];

  k  = calloc(klen,1);
  if(!k) fail("allocation of k failed");
  n  = calloc(nlen,1);
  if(!n) fail("allocation of n failed");
  c  = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES,1);
  if(!c) fail("allocation of c failed");

  for (j = 0;j < crypto_secretbox_ZEROBYTES;++j) c[j] = 0;

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_secretbox(c,c,crypto_secretbox_ZEROBYTES,n,k);
  }
  print_speed(XSTR(crypto_secretbox),crypto_secretbox_ZEROBYTES,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_secretbox_open(c,c,crypto_secretbox_ZEROBYTES,n,k);
  }
  print_speed(XSTR(crypto_secretbox_open),crypto_secretbox_ZEROBYTES,t,NRUNS);
 
  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j + crypto_box_ZEROBYTES;

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_secretbox(c,c,mlen,n,k);
    }
    print_speed(XSTR(crypto_secretbox),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_secretbox_open(c,c,mlen,n,k);
    }
    print_speed(XSTR(crypto_secretbox_open),mlen,t,NRUNS);
  }

  free(k);
  free(n);
  free(c);

  avr_end();
  return 0;
}
