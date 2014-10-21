/*
 * File:    test/test_crypto_stream.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Thu Jul 24 14:04:59 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_stream/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"

#undef crypto_stream
#undef crypto_stream_xor
#undef crypto_stream_KEYBYTES
#undef crypto_stream_NONCEBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_stream            XCONCAT(crypto_stream_,PRIMITIVE)
#define crypto_stream_xor        XCONCAT3(crypto_stream_,PRIMITIVE,_xor)
#define crypto_stream_KEYBYTES   XCONCAT3(crypto_stream_,PRIMITIVE,_KEYBYTES)
#define crypto_stream_NONCEBYTES XCONCAT3(crypto_stream_,PRIMITIVE,_NONCEBYTES)

#define MAXTEST_BYTES 256

static unsigned char *k;
static unsigned char *n;
static unsigned char *m;
static unsigned char *c;
static unsigned char *s;
static unsigned char *k2;
static unsigned char *n2;
static unsigned char *m2;
static unsigned char *c2;
static unsigned char *s2;

char checksum[crypto_stream_KEYBYTES * 2 + 1];

static void fail(const char *error)
{
  print("ERROR: ");
  print(error);
  print("\n");
  avr_end();
  exit(-1);
}

int main(void)
{
  long long i;
  long long j;

  k = calloc(crypto_stream_KEYBYTES+32,1);
  if(!k) fail("allocation of k failed");
  n = calloc(crypto_stream_NONCEBYTES+32,1);
  if(!n) fail("allocation of n failed");
  m = calloc(MAXTEST_BYTES+32,1);
  if(!m) fail("allocation of m failed");
  c = calloc(MAXTEST_BYTES+32,1);
  if(!c) fail("allocation of c failed");
  s = calloc(MAXTEST_BYTES+32,1);
  if(!s) fail("allocation of s failed");
  k2 = calloc(crypto_stream_KEYBYTES+32,1);
  if(!k2) fail("allocation of k2 failed");
  n2 = calloc(crypto_stream_NONCEBYTES+32,1);
  if(!n2) fail("allocation of n2 failed");
  m2 = calloc(MAXTEST_BYTES+32,1);
  if(!m2) fail("allocation of m2 failed");
  c2 = calloc(MAXTEST_BYTES+32,1);
  if(!c2) fail("allocation of c2 failed");
  s2 = calloc(MAXTEST_BYTES+32,1);
  if(!s2) fail("allocation of s2 failed");

  k += 16;
  n += 16;
  m += 16;
  c += 16;
  s += 16;
  k2 += 16;
  n2 += 16;
  m2 += 16;
  c2 += 16;
  s2 += 16;

  for (i = 0;i < MAXTEST_BYTES;++i) 
  {
    long long mlen = i;
    long long clen = i;
    long long slen = i;
    long long klen = crypto_stream_KEYBYTES;
    long long nlen = crypto_stream_NONCEBYTES;
    randombytes(m-16,16);
    randombytes(c-16,16);
    randombytes(s-16,16);
    randombytes(n-16,16);
    randombytes(k-16,16);
    randombytes(m+mlen,16);
    randombytes(c+clen,16);
    randombytes(s+slen,16);
    randombytes(n+nlen,16);
    randombytes(k+klen,16);
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];
    for (j = -16;j < clen + 16;++j) c2[j] = c[j];
    for (j = -16;j < slen + 16;++j) s2[j] = s[j];
    for (j = -16;j < nlen + 16;++j) n2[j] = n[j];
    for (j = -16;j < klen + 16;++j) k2[j] = k[j];

    crypto_stream_xor(c,m,mlen,n,k);

    for (j = -16;j < mlen + 16;++j) if (m[j] != m2[j]) fail("crypto_stream_xor overwrites m");
    for (j = -16;j < slen + 16;++j) if (s[j] != s2[j]) fail("crypto_stream_xor overwrites s");
    for (j = -16;j < nlen + 16;++j) if (n[j] != n2[j]) fail("crypto_stream_xor overwrites n");
    for (j = -16;j < klen + 16;++j) if (k[j] != k2[j]) fail("crypto_stream_xor overwrites k");
    for (j = -16;j < 0;++j) if (c[j] != c2[j]) fail("crypto_stream_xor writes before output");
    for (j = clen;j < clen + 16;++j) if (c[j] != c2[j]) fail("crypto_stream_xor writes after output");

    for (j = -16;j < clen + 16;++j) c2[j] = c[j];

    crypto_stream(s,slen,n,k);

    for (j = -16;j < mlen + 16;++j) if (m[j] != m2[j]) fail("crypto_stream overwrites m");
    for (j = -16;j < clen + 16;++j) if (c[j] != c2[j]) fail("crypto_stream overwrites c");
    for (j = -16;j < nlen + 16;++j) if (n[j] != n2[j]) fail("crypto_stream overwrites n");
    for (j = -16;j < klen + 16;++j) if (k[j] != k2[j]) fail("crypto_stream overwrites k");
    for (j = -16;j < 0;++j) if (s[j] != s2[j]) fail("crypto_stream writes before output");
    for (j = slen;j < slen + 16;++j) if (s[j] != s2[j]) fail("crypto_stream writes after output");

    for (j = 0;j < mlen;++j)
      if ((s[j] ^ m[j]) != c[j]) fail("crypto_stream_xor does not match crypto_stream");

    for (j = 0;j < clen;++j) k[j % klen] ^= c[j];
    crypto_stream_xor(m,c,clen,n,k);
    crypto_stream(s,slen,n,k);
    for (j = 0;j < mlen;++j)
      if ((s[j] ^ m[j]) != c[j]) fail("crypto_stream_xor does not match crypto_stream");
    for (j = 0;j < mlen;++j) n[j % nlen] ^= m[j];
    m[mlen] = 0;
  }

  for (i = 0;i < crypto_stream_KEYBYTES;++i) 
  {
    checksum[2 * i]     = "0123456789abcdef"[15 & (k[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & k[i]];
  }
  checksum[2 * i] = 0;
  
  print("Checksum: ");
  print(checksum);
  print("\n");

  k -= 16;
  n -= 16;
  m -= 16;
  c -= 16;
  s -= 16;
  k2 -= 16;
  n2 -= 16;
  m2 -= 16;
  c2 -= 16;
  s2 -= 16;

  free(k);
  free(n);
  free(m);
  free(c);
  free(s);
  free(k2);
  free(n2);
  free(m2);
  free(c2);
  free(s2);

  avr_end();
  return 0;
}
