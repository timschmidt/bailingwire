/*
 * File:    test/test_crypto_dh.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Jul 30 12:16:08 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_dh/try.c version 20110504by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_dh
#undef crypto_dh_keypair
#undef crypto_dh_SECRETKEYBYTES
#undef crypto_dh_PUBLICKEYBYTES
#undef crypto_dh_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_dh                XCONCAT(crypto_dh_,PRIMITIVE)
#define crypto_dh_keypair        XCONCAT3(crypto_dh_,PRIMITIVE,_keypair)
#define crypto_dh_SECRETKEYBYTES XCONCAT3(crypto_dh_,PRIMITIVE,_SECRETKEYBYTES)
#define crypto_dh_PUBLICKEYBYTES XCONCAT3(crypto_dh_,PRIMITIVE,_PUBLICKEYBYTES)
#define crypto_dh_BYTES          XCONCAT3(crypto_dh_,PRIMITIVE,_BYTES)

static unsigned char *pk1;
static unsigned char *sk1;
static unsigned char *pk2;
static unsigned char *sk2;
static unsigned char *s1;
static unsigned char *s2;

char checksum[crypto_dh_BYTES * 2 + 1];

int main(void)
{
  long long loop;
  long long i;

  pk1 = calloc(crypto_dh_PUBLICKEYBYTES+32,1);
  if(!pk1) fail("allocation of pk1 failed");
  pk2 = calloc(crypto_dh_PUBLICKEYBYTES+32,1);
  if(!pk2) fail("allocation of pk2 failed");
  sk1 = calloc(crypto_dh_SECRETKEYBYTES+32,1);
  if(!sk1) fail("allocation of sk1 failed");
  sk2 = calloc(crypto_dh_SECRETKEYBYTES+32,1);
  if(!sk2) fail("allocation of sk2 failed");
  s1 = calloc(crypto_dh_BYTES+32,1);
  if(!s1) fail("allocation of s1 failed");
  s2 = calloc(crypto_dh_BYTES+32,1);
  if(!s2) fail("allocation of s2 failed");

  pk1 += 16;
  pk2 += 16;
  sk1 += 16;
  sk2 += 16;
  s1  += 16;
  s2  += 16;

  for (loop = 0;loop < 5;++loop) 
  {
    if (crypto_dh_keypair(pk1,sk1) != 0) fail("crypto_dh_keypair returns nonzero");
    if (crypto_dh_keypair(pk2,sk2) != 0) fail("crypto_dh_keypair returns nonzero");
    if (crypto_dh(s1,pk2,sk1) != 0) fail("crypto_dh returns nonzero");
    if (crypto_dh(s2,pk1,sk2) != 0) fail("crypto_dh returns nonzero");
    for (i = 0;i < crypto_dh_BYTES;++i)
      if (s1[i] != s2[i])
        fail("crypto_dh does not match");
  }

  /* XXX: do some long-term checksum */
  checksum[0] = '0';
  checksum[1] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  pk1 -= 16;
  pk2 -= 16;
  sk1 -= 16;
  sk2 -= 16;
  s1  -= 16;
  s2  -= 16;

  free(pk1);
  free(pk2);
  free(sk1);
  free(sk2);
  free(s1);
  free(s2);

  avr_end();
  return 0;
}
