/*
 * File:    test/test_crypto_core.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Fri Jul 25 12:44:42 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_core/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_core
#undef crypto_core_OUTPUTBYTES
#undef crypto_core_INPUTBYTES
#undef crypto_core_KEYBYTES
#undef crypto_core_CONSTBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_core             XCONCAT(crypto_core_,PRIMITIVE)
#define crypto_core_OUTPUTBYTES XCONCAT3(crypto_core_,PRIMITIVE,_OUTPUTBYTES)
#define crypto_core_INPUTBYTES  XCONCAT3(crypto_core_,PRIMITIVE,_INPUTBYTES)
#define crypto_core_KEYBYTES    XCONCAT3(crypto_core_,PRIMITIVE,_KEYBYTES)
#define crypto_core_CONSTBYTES  XCONCAT3(crypto_core_,PRIMITIVE,_CONSTBYTES)

static unsigned char *h;
static unsigned char *n;
static unsigned char *k;
static unsigned char *c;
static unsigned char *h2;
static unsigned char *n2;
static unsigned char *k2;
static unsigned char *c2;

#define hlen crypto_core_OUTPUTBYTES
#define nlen crypto_core_INPUTBYTES
#define klen crypto_core_KEYBYTES
#define clen crypto_core_CONSTBYTES

static unsigned char newbyte(void)
{
  unsigned long long x;
  long long j;
  x = 8675309;
  for (j = 0;j < hlen;++j) { x += h[j]; x *= x; x += (x >> 31); }
  for (j = 0;j < nlen;++j) { x += n[j]; x *= x; x += (x >> 31); }
  for (j = 0;j < klen;++j) { x += k[j]; x *= x; x += (x >> 31); }
  for (j = 0;j < clen;++j) { x += c[j]; x *= x; x += (x >> 31); }
  for (j = 0;j < 100;++j)  { x +=   j ; x *= x; x += (x >> 31); }
  return x;
}

char checksum[hlen * 2 + 1];

int main(void)
{
  long long i;
  long long j;

  h = calloc(hlen+32,1);
  if(!h) fail("allocation of h failed");
  n = calloc(nlen+32,1);
  if(!n) fail("allocation of n failed");
  k = calloc(klen+32,1);
  if(!k) fail("allocation of k failed");
  c = calloc(clen+32,1);
  if(!c) fail("allocation of c failed");
  h2 = calloc(hlen+32,1);
  if(!h2) fail("allocation of h2 failed");
  n2 = calloc(nlen + crypto_core_OUTPUTBYTES+32,1);
  if(!n2) fail("allocation of n2 failed");
  k2 = calloc(klen + crypto_core_OUTPUTBYTES+32,1);
  if(!k2) fail("allocation of k2 failed");
  c2 = calloc(clen + crypto_core_OUTPUTBYTES+32,1);
  if(!c2) fail("allocation of c2 failed");

  h += 16;
  n += 16;
  k += 16;
  c += 16;
  h2 += 16;
  n2 += 16;
  k2 += 16;
  c2 += 16;

  for (i = 0;i <100;++i) 
  {
    randombytes(h-16,16);
    randombytes(n-16,16);
    randombytes(k-16,16);
    randombytes(c-16,16);
    randombytes(h+hlen,16);
    randombytes(n+nlen,16);
    randombytes(k+klen,16);
    randombytes(c+clen,16);
    for (j = -16;j < hlen + 16;++j) h2[j] = h[j];
    for (j = -16;j < nlen + 16;++j) n2[j] = n[j];
    for (j = -16;j < klen + 16;++j) k2[j] = k[j];
    for (j = -16;j < clen + 16;++j) c2[j] = c[j];

    if (crypto_core(h,n,k,c) != 0) fail("crypto_core returns nonzero");
    for (j = -16;j < 0;++j) if (h2[j] != h[j]) fail("crypto_core writes before output");
    for (j = hlen;j < hlen + 16;++j) if (h2[j] != h[j]) fail("crypto_core writes after output");
    for (j = -16;j < klen + 16;++j) if (k2[j] != k[j]) fail("crypto_core writes to k");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_core writes to n");
    for (j = -16;j < clen + 16;++j) if (c2[j] != c[j]) fail("crypto_core writes to c");

    if (crypto_core(n2,n2,k,c) != 0) fail("crypto_core returns nonzero");
    for (j = 0;j < hlen;++j) if (h[j] != n2[j]) fail("crypto_core does not handle n overlap");
    for (j = 0;j < hlen;++j) n2[j] = n[j];
    if (crypto_core(k2,n2,k2,c) != 0) fail("crypto_core returns nonzero");
    for (j = 0;j < hlen;++j) if (h[j] != k2[j]) fail("crypto_core does not handle k overlap");
    for (j = 0;j < hlen;++j) k2[j] = k[j];
    if (crypto_core(c2,n2,k2,c2) != 0) fail("crypto_core returns nonzero");
    for (j = 0;j < hlen;++j) if (h[j] != c2[j]) fail("crypto_core does not handle c overlap");
    for (j = 0;j < hlen;++j) c2[j] = c[j];

    for (j = 0;j < nlen;++j) n[j] = newbyte();
    if (crypto_core(h,n,k,c) != 0) fail("crypto_core returns nonzero");
    for (j = 0;j < klen;++j) k[j] = newbyte();
    if (crypto_core(h,n,k,c) != 0) fail("crypto_core returns nonzero");
    for (j = 0;j < clen;++j) c[j] = newbyte();
  }

  for (i = 0;i < hlen;++i) {
    checksum[2 * i] = "0123456789abcdef"[15 & (h[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & h[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  h -= 16;
  n -= 16;
  k -= 16;
  c -= 16;
  h2 -= 16;
  n2 -= 16;
  k2 -= 16;
  c2 -= 16;

  free(h);
  free(n);
  free(k);
  free(c);
  free(h2);
  free(n2);
  free(k2);
  free(c2);

  avr_end();
  return 0;
}

