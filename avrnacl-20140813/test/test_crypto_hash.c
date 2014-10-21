/*
 * File:    test/test_crypto_hash.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Fri Jul 25 12:44:42 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_hash/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_hash
#undef crypto_hash_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_hash             XCONCAT(crypto_hash_,PRIMITIVE)
#define crypto_hash_BYTES XCONCAT3(crypto_hash_,PRIMITIVE,_BYTES)

#define MAXTEST_BYTES (1024 + crypto_hash_BYTES)

static unsigned char *h;
static unsigned char *h2;
static unsigned char *m;
static unsigned char *m2;

char checksum[crypto_hash_BYTES * 2 + 1];

int main(void)
{
  long long i;
  long long j;

  h = calloc(crypto_hash_BYTES+32,1);
  if(!h) fail("allocation of h failed");
  h2 = calloc(crypto_hash_BYTES+32,1);
  if(!h2) fail("allocation of h2 failed");
  m = calloc(MAXTEST_BYTES+32,1);
  if(!m) fail("allocation of m failed");
  m2 = calloc(MAXTEST_BYTES+32,1);
  if(!m2) fail("allocation of m2 failed");

  h  += 16;
  h2 += 16;
  m  += 16;
  m2 += 16;


  for (i = 0;i < MAXTEST_BYTES;++i) 
  {
    long long hlen = crypto_hash_BYTES;
    long long mlen = i;
    for (j = -16;j < 0;++j) h[j] = random();
    for (j = hlen;j < hlen + 16;++j) h[j] = random();
    for (j = -16;j < hlen + 16;++j) h2[j] = h[j];
    for (j = -16;j < 0;++j) m[j] = random();
    for (j = mlen;j < mlen + 16;++j) m[j] = random();
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];
    if (crypto_hash(h,m,mlen) != 0) fail("crypto_hash returns nonzero");
    for (j = -16;j < mlen + 16;++j) if (m2[j] != m[j]) fail("crypto_hash writes to input");
    for (j = -16;j < 0;++j) if (h2[j] != h[j]) fail("crypto_hash writes before output");
    for (j = hlen;j < hlen + 16;++j) if (h2[j] != h[j]) fail("crypto_hash writes after output");
    if (crypto_hash(m2,m2,mlen) != 0) fail("crypto_hash returns nonzero");
    for (j = 0;j < hlen;++j) if (m2[j] != h[j]) fail("crypto_hash does not handle overlap");
    for (j = 0;j < mlen;++j) m[j] ^= h[j % hlen];
    m[mlen] = h[0];
  }
  if (crypto_hash(h,m,MAXTEST_BYTES) != 0) fail("crypto_hash returns nonzero");

  for (i = 0;i < crypto_hash_BYTES;++i) 
  {
    checksum[2 * i] = "0123456789abcdef"[15 & (h[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & h[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  h  -= 16;
  h2 -= 16;
  m  -= 16;
  m2 -= 16;

  free(h);
  free(h2);
  free(m);
  free(m2);

  avr_end();
  return 0;
}
