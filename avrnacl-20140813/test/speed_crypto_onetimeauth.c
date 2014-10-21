/*
 * File:    test/speed_crypto_onetimeauth.c
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

#undef crypto_onetimeauth
#undef crypto_onetimeauth_verify
#undef crypto_onetimeauth_BYTES
#undef crypto_onetimeauth_KEYBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_onetimeauth             XCONCAT(crypto_onetimeauth_,PRIMITIVE)
#define crypto_onetimeauth_verify      XCONCAT3(crypto_onetimeauth_,PRIMITIVE,_verify)
#define crypto_onetimeauth_BYTES       XCONCAT3(crypto_onetimeauth_,PRIMITIVE,_BYTES)
#define crypto_onetimeauth_KEYBYTES    XCONCAT3(crypto_onetimeauth_,PRIMITIVE,_KEYBYTES)

#define MAXTEST_BYTES 1024

static unsigned char *h;
static unsigned char *m;
static unsigned char *k;

int main(void)
{
  unsigned int i,mlen;
  unsigned long long t[NRUNS];

  h  = calloc(crypto_onetimeauth_BYTES,1);
  if(!h) fail("allocation of h failed");
  m  = calloc(MAXTEST_BYTES,1);
  if(!m) fail("allocation of m failed");
  k  = calloc(crypto_onetimeauth_KEYBYTES,1);
  if(!k) fail("allocation of k failed");


  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_onetimeauth(h,m,0,k);
  }
  print_speed(XSTR(crypto_onetimeauth),0,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_onetimeauth_verify(h,m,0,k);
  }
  print_speed(XSTR(crypto_onetimeauth_verify),0,t,NRUNS);


  for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
  {
    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_onetimeauth(h,m,mlen,k);
    }
    print_speed(XSTR(crypto_onetimeauth),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_onetimeauth_verify(h,m,mlen,k);
    }
    print_speed(XSTR(crypto_onetimeauth_verify),mlen,t,NRUNS);
  }

  free(h);
  free(m);
  free(k);

  avr_end();
  return 0;
}
