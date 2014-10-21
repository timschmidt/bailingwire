/*
 * File:    test/test_crypto_secretbox.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Jul 30 08:02:11 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_secretbox/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_secretbox
#undef crypto_secretbox_open
#undef crypto_secretbox_KEYBYTES
#undef crypto_secretbox_NONCEBYTES
#undef crypto_secretbox_ZEROBYTES
#undef crypto_secretbox_BOXZEROBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_secretbox              XCONCAT(crypto_secretbox_,PRIMITIVE)
#define crypto_secretbox_open         XCONCAT3(crypto_secretbox_,PRIMITIVE,_open)
#define crypto_secretbox_KEYBYTES     XCONCAT3(crypto_secretbox_,PRIMITIVE,_KEYBYTES)
#define crypto_secretbox_NONCEBYTES   XCONCAT3(crypto_secretbox_,PRIMITIVE,_NONCEBYTES)
#define crypto_secretbox_ZEROBYTES    XCONCAT3(crypto_secretbox_,PRIMITIVE,_ZEROBYTES)
#define crypto_secretbox_BOXZEROBYTES XCONCAT3(crypto_secretbox_,PRIMITIVE,_BOXZEROBYTES)

#define MAXTEST_BYTES 256

static unsigned char *k;
static unsigned char *n;
static unsigned char *m;
static unsigned char *c;
static unsigned char *t;
static unsigned char *k2;
static unsigned char *n2;
static unsigned char *m2;
static unsigned char *c2;
static unsigned char *t2;

#define klen crypto_secretbox_KEYBYTES
#define nlen crypto_secretbox_NONCEBYTES

char checksum[klen * 2 + 1];

int main(void)
{
  long long i;
  long long j;

  k  = calloc(klen+32,1);
  if(!k) fail("allocation of k failed");
  n  = calloc(nlen+32,1);
  if(!n) fail("allocation of n failed");
  m  = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES+32,1);
  if(!m) fail("allocation of m failed");
  c  = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES+32,1);
  if(!c) fail("allocation of c failed");
  t  = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES+32,1);
  if(!t) fail("allocation of t failed");
  k2 = calloc(klen+32,1);
  if(!k2) fail("allocation of k2 failed");
  n2 = calloc(nlen+32,1);
  if(!n2) fail("allocation of n2 failed");
  m2 = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES+32,1);
  if(!m2) fail("allocation of m2 failed");
  c2 = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES+32,1);
  if(!c2) fail("allocation of c2 failed");
  t2 = calloc(MAXTEST_BYTES + crypto_secretbox_ZEROBYTES+32,1);
  if(!t2) fail("allocation of t2 failed");

  k  += 16;
  n  += 16;
  m  += 16;
  c  += 16;
  t  += 16;
  k2 += 16;
  n2 += 16;
  m2 += 16;
  c2 += 16;
  t2 += 16;

  for (j = 0;j < crypto_secretbox_ZEROBYTES;++j) m[j] = 0;

  for (i = 0;i < MAXTEST_BYTES;++i) 
  {
    long long mlen = i + crypto_secretbox_ZEROBYTES;
    long long tlen = i + crypto_secretbox_ZEROBYTES;
    long long clen = i + crypto_secretbox_ZEROBYTES;

    for (j = -16;j < 0;++j) k[j] = random();
    for (j = -16;j < 0;++j) n[j] = random();
    for (j = -16;j < 0;++j) m[j] = random();
    for (j = klen;j < klen + 16;++j) k[j] = random();
    for (j = nlen;j < nlen + 16;++j) n[j] = random();
    for (j = mlen;j < mlen + 16;++j) m[j] = random();
    for (j = -16;j < klen + 16;++j) k2[j] = k[j];
    for (j = -16;j < nlen + 16;++j) n2[j] = n[j];
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];
    for (j = -16;j < clen + 16;++j) c2[j] = c[j] = random();

    if (crypto_secretbox(c,m,mlen,n,k) != 0) fail("crypto_secretbox returns nonzero");

    for (j = -16;j < mlen + 16;++j) if (m2[j] != m[j]) fail("crypto_secretbox overwrites m");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_secretbox overwrites n");
    for (j = -16;j < klen + 16;++j) if (k2[j] != k[j]) fail("crypto_secretbox overwrites k");
    for (j = -16;j < 0;++j) if (c2[j] != c[j]) fail("crypto_secretbox writes before output");
    for (j = clen;j < clen + 16;++j) if (c2[j] != c[j]) fail("crypto_secretbox writes after output");
    for (j = 0;j < crypto_secretbox_BOXZEROBYTES;++j)
      if (c[j] != 0) fail("crypto_secretbox does not clear extra bytes");

    for (j = -16;j < 0;++j) c[j] = random();
    for (j = clen;j < clen + 16;++j) c[j] = random();
    for (j = -16;j < clen + 16;++j) c2[j] = c[j];
    for (j = -16;j < tlen + 16;++j) t2[j] = t[j] = random();

    if (crypto_secretbox_open(t,c,clen,n,k) != 0) fail("crypto_secretbox_open returns nonzero");

    for (j = -16;j < clen + 16;++j) if (c2[j] != c[j]) fail("crypto_secretbox_open overwrites c");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_secretbox_open overwrites n");
    for (j = -16;j < klen + 16;++j) if (k2[j] != k[j]) fail("crypto_secretbox_open overwrites k");
    for (j = -16;j < 0;++j) if (t2[j] != t[j]) fail("crypto_secretbox_open writes before output");
    for (j = tlen;j < tlen + 16;++j) if (t2[j] != t[j]) fail("crypto_secretbox_open writes after output");
    for (j = 0;j < crypto_secretbox_ZEROBYTES;++j)
      if (t[j] != 0) fail("crypto_secretbox_open does not clear extra bytes");
    
    for (j = 0;j < i;++j) if (t[j] != m[j]) fail("plaintext does not match");
    
    for (j = 0;j < i;++j)
      k[j % klen] ^= c[j + crypto_secretbox_BOXZEROBYTES];
    crypto_secretbox(c,m,mlen,n,k);
    for (j = 0;j < i;++j)
      n[j % nlen] ^= c[j + crypto_secretbox_BOXZEROBYTES];
    crypto_secretbox(c,m,mlen,n,k);
    if (i == 0) m[crypto_secretbox_ZEROBYTES + 0] = 0;
    m[crypto_secretbox_ZEROBYTES + i] = m[crypto_secretbox_ZEROBYTES + 0];
    for (j = 0;j < i;++j)
      m[j + crypto_secretbox_ZEROBYTES] ^= c[j + crypto_secretbox_BOXZEROBYTES];
  }

  for (i = 0;i < klen;++i) {
    checksum[2 * i] = "0123456789abcdef"[15 & (k[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & k[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  k  -= 16;
  n  -= 16;
  m  -= 16;
  c  -= 16;
  t  -= 16;
  k2 -= 16;
  n2 -= 16;
  m2 -= 16;
  c2 -= 16;
  t2 -= 16;

  free(k);
  free(n);
  free(m);
  free(c);
  free(t);
  free(k2);
  free(n2);
  free(m2);
  free(c2);
  free(t2);

  avr_end();
  return 0;
}
