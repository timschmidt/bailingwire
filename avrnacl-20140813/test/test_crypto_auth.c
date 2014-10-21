/*
 * File:    test/test_crypto_auth.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Jul 30 12:16:08 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_auth/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_auth
#undef crypto_auth_verify
#undef crypto_auth_BYTES
#undef crypto_auth_KEYBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_auth             XCONCAT(crypto_auth_,PRIMITIVE)
#define crypto_auth_verify      XCONCAT3(crypto_auth_,PRIMITIVE,_verify)
#define crypto_auth_BYTES       XCONCAT3(crypto_auth_,PRIMITIVE,_BYTES)
#define crypto_auth_KEYBYTES    XCONCAT3(crypto_auth_,PRIMITIVE,_KEYBYTES)

#define MAXTEST_BYTES 256

static void truncsha512(unsigned char h[32], const unsigned char *m, unsigned long long mlen)
{
  unsigned char t[64];
  int i;
  crypto_hash_sha512(t,m,mlen);
  for(i=0;i<32;i++)
    h[i] = t[i+32];
}

static unsigned char *h;
static unsigned char *m;
static unsigned char *k;
static unsigned char *h2;
static unsigned char *m2;
static unsigned char *k2;

char checksum[crypto_auth_BYTES * 2 + 1];

int main (void)
{
  long long i;
  long long j;

  h = calloc(crypto_auth_BYTES+32,1);
  if(!h) fail("allocation of h failed");
  m = calloc(MAXTEST_BYTES+32,1);
  if(!m) fail("allocation of m failed");
  k = calloc(crypto_auth_KEYBYTES+32,1);
  if(!k) fail("allocation of k failed");
  h2 = calloc(crypto_auth_BYTES+32,1);
  if(!h2) fail("allocation of h2 failed");
  m2 = calloc(MAXTEST_BYTES + crypto_auth_BYTES+32,1);
  if(!m2) fail("allocation of m2 failed");
  k2 = calloc(crypto_auth_KEYBYTES + crypto_auth_BYTES+32,1);
  if(!k2) fail("allocation of k2 failed");

  h  += 16;
  m  += 16;
  k  += 16;
  h2 += 16;
  m2 += 16;
  k2 += 16;

  for (i = 0;i < MAXTEST_BYTES;++i) 
  {
    long long mlen = i;
    long long klen = crypto_auth_KEYBYTES;
    long long hlen = crypto_auth_BYTES;

    for (j = -16;j < 0;++j) h[j] = random();
    for (j = -16;j < 0;++j) k[j] = random();
    for (j = -16;j < 0;++j) m[j] = random();
    for (j = hlen;j < hlen + 16;++j) h[j] = random();
    for (j = klen;j < klen + 16;++j) k[j] = random();
    for (j = mlen;j < mlen + 16;++j) m[j] = random();
    for (j = -16;j < hlen + 16;++j) h2[j] = h[j];
    for (j = -16;j < klen + 16;++j) k2[j] = k[j];
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];

    if (crypto_auth(h,m,mlen,k) != 0) fail("crypto_auth returns nonzero");

    for (j = -16;j < klen + 16;++j) if (k[j] != k2[j]) fail("crypto_auth overwrites k");
    for (j = -16;j < mlen + 16;++j) if (m[j] != m2[j]) fail("crypto_auth overwrites m");
    for (j = -16;j < 0;++j) if (h[j] != h2[j]) fail("crypto_auth writes before output");
    for (j = hlen;j < hlen + 16;++j) if (h[j] != h2[j]) fail("crypto_auth writes after output");

    for (j = -16;j < 0;++j) h[j] = random();
    for (j = -16;j < 0;++j) k[j] = random();
    for (j = -16;j < 0;++j) m[j] = random();
    for (j = hlen;j < hlen + 16;++j) h[j] = random();
    for (j = klen;j < klen + 16;++j) k[j] = random();
    for (j = mlen;j < mlen + 16;++j) m[j] = random();
    for (j = -16;j < hlen + 16;++j) h2[j] = h[j];
    for (j = -16;j < klen + 16;++j) k2[j] = k[j];
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];

    if (crypto_auth(m2,m2,mlen,k) != 0) fail("crypto_auth returns nonzero");
    for (j = 0;j < hlen;++j) if (m2[j] != h[j]) fail("crypto_auth does not handle m overlap");
    for (j = 0;j < hlen;++j) m2[j] = m[j];
    if (crypto_auth(k2,m2,mlen,k2) != 0) fail("crypto_auth returns nonzero");
    for (j = 0;j < hlen;++j) if (k2[j] != h[j]) fail("crypto_auth does not handle k overlap");
    for (j = 0;j < hlen;++j) k2[j] = k[j];

    if (crypto_auth_verify(h,m,mlen,k) != 0) fail("crypto_auth_verify returns nonzero");

    for (j = -16;j < hlen + 16;++j) if (h[j] != h2[j]) fail("crypto_auth overwrites h");
    for (j = -16;j < klen + 16;++j) if (k[j] != k2[j]) fail("crypto_auth overwrites k");
    for (j = -16;j < mlen + 16;++j) if (m[j] != m2[j]) fail("crypto_auth overwrites m");

    //crypto_hash_sha256(h2,h,hlen);
    truncsha512(h2,h,hlen);
    for (j = 0;j < klen;++j) k[j] ^= h2[j % 32];
    if (crypto_auth(h,m,mlen,k) != 0) fail("crypto_auth returns nonzero");
    if (crypto_auth_verify(h,m,mlen,k) != 0) fail("crypto_auth_verify returns nonzero");
    
    //crypto_hash_sha256(h2,h,hlen);
    truncsha512(h2,h,hlen);
    for (j = 0;j < mlen;++j) m[j] ^= h2[j % 32];
    m[mlen] = h2[0];
  }
  if (crypto_auth(h,m,MAXTEST_BYTES,k) != 0) fail("crypto_auth returns nonzero");
  if (crypto_auth_verify(h,m,MAXTEST_BYTES,k) != 0) fail("crypto_auth_verify returns nonzero");

  for (i = 0;i < crypto_auth_BYTES;++i) {
    checksum[2 * i] = "0123456789abcdef"[15 & (h[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & h[i]];
  }
  checksum[2 * i] = 0;
  
  print("Checksum: ");
  print(checksum);
  print("\n");

  h  -= 16;
  m  -= 16;
  k  -= 16;
  h2 -= 16;
  m2 -= 16;
  k2 -= 16;

  free(h);
  free(m);
  free(k);
  free(h2);
  free(m2);
  free(k2);

  avr_end();
  return 0;
}
