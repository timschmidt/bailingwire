/*
 * File:    test/speed_crypto_sign.c
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

#undef crypto_sign
#undef crypto_sign_open
#undef crypto_sign_keypair
#undef crypto_sign_SECRETKEYBYTES
#undef crypto_sign_PUBLICKEYBYTES
#undef crypto_sign_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_sign                XCONCAT(crypto_sign_,PRIMITIVE)
#define crypto_sign_open           XCONCAT3(crypto_sign_,PRIMITIVE,_open)
#define crypto_sign_keypair        XCONCAT3(crypto_sign_,PRIMITIVE,_keypair)
#define crypto_sign_SECRETKEYBYTES XCONCAT3(crypto_sign_,PRIMITIVE,_SECRETKEYBYTES)
#define crypto_sign_PUBLICKEYBYTES XCONCAT3(crypto_sign_,PRIMITIVE,_PUBLICKEYBYTES)
#define crypto_sign_BYTES          XCONCAT3(crypto_sign_,PRIMITIVE,_BYTES)

#define MAXTEST_BYTES 1024
  
#define pklen crypto_sign_PUBLICKEYBYTES
#define sklen crypto_sign_SECRETKEYBYTES

static unsigned char *pk;
static unsigned char *sk;
static unsigned char *sm; 
crypto_uint16 smlen;

int main(void)
{
  unsigned int i,j,mlen;
  unsigned long long t[NRUNS];

  pk  = calloc(pklen,1);
  if(!pk) fail("allocation of pk failed");
  sk  = calloc(sklen,1);
  if(!sk) fail("allocation of sk failed");
  sm  = calloc(MAXTEST_BYTES + crypto_sign_BYTES,1);
  if(!sm) fail("allocation of sm failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_sign_keypair(pk,sk);
  }
  print_speed(XSTR(crypto_sign_keypair),-1,t,NRUNS);


  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_sign(sm,&smlen,sm,0,sk);
  }
  print_speed(XSTR(crypto_sign),0,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_sign_open(sm,&mlen,sm,smlen,pk);
  }
  print_speed(XSTR(crypto_sign_open),smlen,t,NRUNS);
 

  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j;

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_sign(sm,&smlen,sm,mlen,sk);
    }
    print_speed(XSTR(crypto_sign),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_sign_open(sm,&mlen,sm,smlen,pk);
    }
    print_speed(XSTR(crypto_sign_open),smlen,t,NRUNS);
  }

  free(pk);
  free(sk);
  free(sm);

  avr_end();
  return 0;
}
