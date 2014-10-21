/*
 * File:    test/speed_crypto_dh.c
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

#undef crypto_dh
#undef crypto_dh_keypair
#undef crypto_dh_SECRETKEYBYTES
#undef crypto_dh_PUBLICKEYBYTES
#undef crypto_dh_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_dh                XCONCAT(crypto_dh_,PRIMITIVE)
#define crypto_dh_keypair        XCONCAT3(crypto_dh_,PRIMITIVE,_keypair)
#define crypto_dh_SECRETKEYBYTES XCONCAT3(crypto_dh_,PRIMITIVE,_SECRETKEYBYTES)
#define crypto_dh_PUBLICKEYBYTES XCONCAT3(crypto_dh_,PRIMITIVE,_PUBLICKEYBYTES)
#define crypto_dh_BYTES          XCONCAT3(crypto_dh_,PRIMITIVE,_BYTES)

static unsigned char *pk;
static unsigned char *sk;
static unsigned char *s;

int main(void)
{
  unsigned int i;
  unsigned long long t[NRUNS];

  pk = calloc(crypto_dh_PUBLICKEYBYTES,1);
  if(!pk) fail("allocation of pk failed");
  sk = calloc(crypto_dh_SECRETKEYBYTES,1);
  if(!sk) fail("allocation of sk failed");
  s = calloc(crypto_dh_BYTES,1);
  if(!s) fail("allocation of s failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_dh_keypair(pk,sk);
  }
  print_speed(XSTR(crypto_dh_keypair),-1,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_dh(s,pk,sk);
  }
  print_speed(XSTR(crypto_dh),-1,t,NRUNS);

  free(pk);
  free(sk);
  free(s);

  avr_end();
  return 0;
}
