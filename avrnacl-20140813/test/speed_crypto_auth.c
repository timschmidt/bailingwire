/*
 * File:    test/speed_crypto_auth.c
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

#undef crypto_auth
#undef crypto_auth_verify
#undef crypto_auth_BYTES
#undef crypto_auth_KEYBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_auth             XCONCAT(crypto_auth_,PRIMITIVE)
#define crypto_auth_verify      XCONCAT3(crypto_auth_,PRIMITIVE,_verify)
#define crypto_auth_BYTES       XCONCAT3(crypto_auth_,PRIMITIVE,_BYTES)
#define crypto_auth_KEYBYTES    XCONCAT3(crypto_auth_,PRIMITIVE,_KEYBYTES)

#define MAXTEST_BYTES 1024

static unsigned char *h;
static unsigned char *m;
static unsigned char *k;

int main(void)
{
  unsigned int i,mlen;
  unsigned long long t[NRUNS];

  h = calloc(crypto_auth_BYTES+32,1);
  if(!h) fail("allocation of h failed");
  m = calloc(MAXTEST_BYTES+32,1);
  if(!m) fail("allocation of m failed");
  k = calloc(crypto_auth_KEYBYTES+32,1);
  if(!k) fail("allocation of k failed");


  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_auth(h,m,0,k);
  }
  print_speed(XSTR(crypto_auth),0,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_auth_verify(h,m,0,k);
  }
  print_speed(XSTR(crypto_auth_verify),0,t,NRUNS);


  for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
  {
    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_auth(h,m,mlen,k);
    }
    print_speed(XSTR(crypto_auth),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_auth_verify(h,m,mlen,k);
    }
    print_speed(XSTR(crypto_auth_verify),mlen,t,NRUNS);
  }

  free(h);
  free(m);
  free(k);

  avr_end();
  return 0;
}
