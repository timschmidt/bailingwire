/*
 * File:    test/speed_crypto_stream.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 6 10:05:25 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "cpucycles.h"
#include "fail.h"
#include "avr.h"

#undef crypto_stream
#undef crypto_stream_xor
#undef crypto_stream_KEYBYTES
#undef crypto_stream_NONCEBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_stream            XCONCAT(crypto_stream_,PRIMITIVE)
#define crypto_stream_xor        XCONCAT3(crypto_stream_,PRIMITIVE,_xor)
#define crypto_stream_KEYBYTES   XCONCAT3(crypto_stream_,PRIMITIVE,_KEYBYTES)
#define crypto_stream_NONCEBYTES XCONCAT3(crypto_stream_,PRIMITIVE,_NONCEBYTES)

#define MAXTEST_BYTES 1024

static unsigned char *k;
static unsigned char *n;
static unsigned char *c;

int main(void)
{
  unsigned int i,mlen;
  unsigned long long t[NRUNS];

  k = calloc(crypto_stream_KEYBYTES,1);
  if(!k) fail("allocation of k failed");
  n = calloc(crypto_stream_NONCEBYTES,1);
  if(!n) fail("allocation of n failed");
  c = calloc(MAXTEST_BYTES,1);
  if(!c) fail("allocation of c failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_stream(c,0,n,k);
  }
  print_speed(XSTR(crypto_stream),0,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_stream_xor(c,c,0,n,k);
  }
  print_speed(XSTR(crypto_stream_xor),0,t,NRUNS);


  for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
  {
    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_stream(c,mlen,n,k);
    }
    print_speed(XSTR(crypto_stream),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_stream_xor(c,c,mlen,n,k);
    }
    print_speed(XSTR(crypto_stream_xor),mlen,t,NRUNS);
  }

  free(k);
  free(n);
  free(c);

  avr_end();
  return 0;
}
