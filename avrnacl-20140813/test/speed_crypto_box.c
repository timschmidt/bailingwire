/*
 * File:    test/speed_crypto_box.c
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

#undef crypto_box
#undef crypto_box_open
#undef crypto_box_keypair
#undef crypto_box_beforenm
#undef crypto_box_afternm
#undef crypto_box_open_afternm
#undef crypto_box_PUBLICKEYBYTES
#undef crypto_box_SECRETKEYBYTES
#undef crypto_box_BEFORENMBYTES
#undef crypto_box_NONCEBYTES
#undef crypto_box_ZEROBYTES
#undef crypto_box_BOXZEROBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_box                XCONCAT(crypto_box_,PRIMITIVE)
#define crypto_box_open           XCONCAT3(crypto_box_,PRIMITIVE,_open)
#define crypto_box_keypair        XCONCAT3(crypto_box_,PRIMITIVE,_keypair)
#define crypto_box_beforenm       XCONCAT3(crypto_box_,PRIMITIVE,_beforenm)
#define crypto_box_afternm        XCONCAT3(crypto_box_,PRIMITIVE,_afternm)
#define crypto_box_open_afternm   XCONCAT3(crypto_box_,PRIMITIVE,_open_afternm)
#define crypto_box_PUBLICKEYBYTES XCONCAT3(crypto_box_,PRIMITIVE,_PUBLICKEYBYTES)
#define crypto_box_SECRETKEYBYTES XCONCAT3(crypto_box_,PRIMITIVE,_SECRETKEYBYTES)
#define crypto_box_BEFORENMBYTES  XCONCAT3(crypto_box_,PRIMITIVE,_BEFORENMBYTES)
#define crypto_box_NONCEBYTES     XCONCAT3(crypto_box_,PRIMITIVE,_NONCEBYTES)
#define crypto_box_ZEROBYTES      XCONCAT3(crypto_box_,PRIMITIVE,_ZEROBYTES)
#define crypto_box_BOXZEROBYTES   XCONCAT3(crypto_box_,PRIMITIVE,_BOXZEROBYTES)

#define MAXTEST_BYTES 1024

static unsigned char *sk;
static unsigned char *pk;
static unsigned char *s;
static unsigned char *n;
static unsigned char *c;

#define sklen crypto_box_SECRETKEYBYTES
#define pklen crypto_box_PUBLICKEYBYTES
#define nlen crypto_box_NONCEBYTES
#define slen crypto_box_BEFORENMBYTES

int main(void)
{
  unsigned int i,j,mlen;
  unsigned long long t[NRUNS];

  sk  = calloc(sklen,1);
  if(!sk) fail("allocation of sk failed");
  pk  = calloc(pklen,1);
  if(!pk) fail("allocation of pk failed");
  n    = calloc(nlen,1);
  if(!n) fail("allocation of n failed");
  c    = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES,1);
  if(!c) fail("allocation of c failed");
  s    = calloc(slen,1);
  if(!s) fail("allocation of s failed");

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_box_keypair(pk,sk);
  }
  print_speed(XSTR(crypto_box_keypair),-1,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_box_beforenm(s,pk,sk);
  }
  print_speed(XSTR(crypto_box_beforenm),-1,t,NRUNS);


  for (j = 0;j < crypto_box_ZEROBYTES;++j) c[j] = 0;

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_box(c,c,crypto_box_ZEROBYTES,n,pk,sk);
  }
  print_speed(XSTR(crypto_box),crypto_box_ZEROBYTES,t,NRUNS);

  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_box_open(c,c,crypto_box_ZEROBYTES,n,pk,sk);
  }
  print_speed(XSTR(crypto_box_open),crypto_box_ZEROBYTES,t,NRUNS);
 
  for(i=0;i<NRUNS;i++)
  {
    t[i] = cpucycles();
    crypto_box_afternm(c,c,crypto_box_ZEROBYTES,n,s);
  }
  print_speed(XSTR(crypto_box_afternm),crypto_box_ZEROBYTES,t,NRUNS);
      

  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j + crypto_box_ZEROBYTES;

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_box(c,c,mlen,n,pk,sk);
    }
    print_speed(XSTR(crypto_box),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_box_open(c,c,mlen,n,pk,sk);
    }
    print_speed(XSTR(crypto_box_open),mlen,t,NRUNS);

    for(i=0;i<NRUNS;i++)
    {
      t[i] = cpucycles();
      crypto_box_afternm(c,c,mlen,n,s);
    }
    print_speed(XSTR(crypto_box_afternm),mlen,t,NRUNS);
  }

  free(sk);
  free(pk);
  free(n);
  free(c);
  free(s);

  avr_end();
  return 0;
}
