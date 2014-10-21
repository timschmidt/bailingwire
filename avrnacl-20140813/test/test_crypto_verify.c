/*
 * File:    test/test_crypto_verify.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Jul 30 12:16:08 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_verify/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <string.h>
#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_verify
#undef crypto_verify_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_verify           XCONCAT(crypto_verify_,PRIMITIVE)
#define crypto_verify_BYTES XCONCAT3(crypto_verify_,PRIMITIVE,_BYTES)


static unsigned char *x;
static unsigned char *y;


static const char *check(void)
{
  int r = crypto_verify(x,y);
  if (r == 0) 
  {
    if (memcmp(x,y,crypto_verify_BYTES)) return "different strings pass verify";
  } 
  else if (r == -1) 
  {
    if (!memcmp(x,y,crypto_verify_BYTES)) return "equal strings fail verify";
  } 
  else 
  {
    return "weird return value from verify";
  }
  return 0;
}

char checksum[2];

int main(void)
{
  long long tests;
  long long i;
  const char *c;

  x = calloc(crypto_verify_BYTES,1);
  if(!x) fail("allocation of x failed");
  y = calloc(crypto_verify_BYTES,1);
  if(!y) fail("allocation of y failed");

  for (tests = 0;tests < 100;++tests) 
  {
    randombytes(x,crypto_verify_BYTES);
    randombytes(y,crypto_verify_BYTES);

    c = check(); if (c) fail(c);
    for (i = 0;i < crypto_verify_BYTES;++i) y[i] = x[i];
    c = check(); if (c) fail(c);

    y[random() % crypto_verify_BYTES] = random();
    c = check(); if (c) fail(c);
    y[random() % crypto_verify_BYTES] = random();
    c = check(); if (c) fail(c);
    y[random() % crypto_verify_BYTES] = random();
    c = check(); if (c) fail(c);
  }

  checksum[0] = '0';
  checksum[1] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  free(x);
  free(y);

  avr_end();
  return 0;
}
