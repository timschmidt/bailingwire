/*
 * File:    test/speed_crypto_hash.c
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

#undef crypto_hash
#undef crypto_hash_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_hash             XCONCAT(crypto_hash_,PRIMITIVE)
#define crypto_hash_BYTES XCONCAT3(crypto_hash_,PRIMITIVE,_BYTES)

#define MAXTEST_BYTES 1024

static unsigned char *h;
static unsigned char *m;

int main(void)
{
  unsigned int i,mlen;
  unsigned long long t[NRUNS];

  h  = calloc(crypto_hash_BYTES,1);
  if(!h) fail("allocation of h failed");
  m  = calloc(MAXTEST_BYTES,1);
  if(!m) fail("allocation of m failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_hash(h,m,0);
  }
  print_speed(XSTR(crypto_hash),0,t,NRUNS);

  for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
  {
    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_hash(h,m,mlen);
    }
    print_speed(XSTR(crypto_hash),mlen,t,NRUNS);
  }

  free(h);
  free(m);

  avr_end();
  return 0;
}
