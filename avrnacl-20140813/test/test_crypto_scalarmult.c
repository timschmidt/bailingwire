/*
 * File:    test/test_crypto_scalarmult.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Fri Jul 25 12:44:42 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_scalarmult/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

#undef crypto_scalarmult
#undef crypto_scalarmult_base
#undef crypto_scalarmult_BYTES
#undef crypto_scalarmult_SCALARBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)

#define crypto_scalarmult             XCONCAT(crypto_scalarmult_,PRIMITIVE)
#define crypto_scalarmult_base        XCONCAT3(crypto_scalarmult_,PRIMITIVE,_base)
#define crypto_scalarmult_BYTES       XCONCAT3(crypto_scalarmult_,PRIMITIVE,_BYTES)
#define crypto_scalarmult_SCALARBYTES XCONCAT3(crypto_scalarmult_,PRIMITIVE,_SCALARBYTES)

#define mlen crypto_scalarmult_SCALARBYTES
#define nlen crypto_scalarmult_SCALARBYTES
#define plen crypto_scalarmult_BYTES
#define qlen crypto_scalarmult_BYTES
#define rlen crypto_scalarmult_BYTES

static unsigned char *m;
static unsigned char *n;
static unsigned char *p;
static unsigned char *q;
static unsigned char *r;

static unsigned char *m2;
static unsigned char *n2;
static unsigned char *p2;
static unsigned char *q2;
static unsigned char *r2;


static char checksum[crypto_scalarmult_BYTES * 2 + 1];

static const unsigned char badn[32] = {0x56,0x2c,0x1e,0xb5,0xfd,0xb2,0x81,0x29,
                                       0xbd,0x37,0x49,0x58,0x35,0xd4,0xb1,0x30,
                                       0x7d,0xdb,0x57,0x38,0x80,0x12,0x17,0x42,
                                       0xf7,0x13,0xf1,0x05,0x67,0x69,0xd5,0xbf};

int main(void)
{
  long long i;
  long long j;
  long long tests;

  m = calloc(mlen+32,1);
  if(!m) fail("allocation of m failed");
  n = calloc(nlen+32,1);
  if(!n) fail("allocation of n failed");
  p = calloc(plen+32,1);
  if(!p) fail("allocation of p failed");
  q = calloc(qlen+32,1);
  if(!q) fail("allocation of q failed");
  r = calloc(rlen+32,1);
  if(!r) fail("allocation of r failed");
  m2 = calloc(mlen + crypto_scalarmult_BYTES+32,1);
  if(!m2) fail("allocation of m2 failed");
  n2 = calloc(nlen + crypto_scalarmult_BYTES+32,1);
  if(!n2) fail("allocation of n2 failed");
  p2 = calloc(plen + crypto_scalarmult_BYTES+32,1);
  if(!p2) fail("allocation of p2 failed");
  q2 = calloc(qlen + crypto_scalarmult_BYTES+32,1);
  if(!q2) fail("allocation of q2 failed");
  r2 = calloc(rlen + crypto_scalarmult_BYTES+32,1);
  if(!r2) fail("allocation of r2 failed");

  m += 16;
  n += 16;
  p += 16;
  q += 16;
  r += 16;
  m2 += 16;
  n2 += 16;
  p2 += 16;
  q2 += 16;
  r2 += 16;

  for (i = 0;i < mlen;++i) m[i] = i;
  for (i = 0;i < nlen;++i) n[i] = i + 1;
  for (i = 0;i < plen;++i) p[i] = i + 2;
  for (i = 0;i < qlen;++i) q[i] = i + 3;
  for (i = 0;i < rlen;++i) r[i] = i + 4;

  for (i = -16;i < 0;++i) p[i] = random();
  for (i = -16;i < 0;++i) n[i] = random();
  for (i = plen;i < plen + 16;++i) p[i] = random();
  for (i = nlen;i < nlen + 16;++i) n[i] = random();
  for (i = -16;i < plen + 16;++i) p2[i] = p[i];
  for (i = -16;i < nlen + 16;++i) n2[i] = n[i];

  if (crypto_scalarmult_base(p,n) != 0) fail("crypto_scalarmult_base returns nonzero");

  for (i = -16;i < nlen + 16;++i) if (n2[i] != n[i]) fail("crypto_scalarmult_base overwrites input");
  for (i = -16;i < 0;++i) if (p2[i] != p[i]) fail("crypto_scalarmult_base writes before output");
  for (i = plen;i < plen + 16;++i) if (p2[i] != p[i]) fail("crypto_scalarmult_base writes after output");

  crypto_scalarmult_base(p,badn);

  for (tests = 0;tests < 5;++tests) 
  {
    for (i = -16;i < 0;++i) q[i] = random();
    for (i = -16;i < 0;++i) p[i] = random();
    for (i = -16;i < 0;++i) m[i] = random();
    for (i = qlen;i < qlen + 16;++i) q[i] = random();
    for (i = plen;i < plen + 16;++i) p[i] = random();
    for (i = mlen;i < mlen + 16;++i) m[i] = random();
    for (i = -16;i < qlen + 16;++i) q2[i] = q[i];
    for (i = -16;i < plen + 16;++i) p2[i] = p[i];
    for (i = -16;i < mlen + 16;++i) m2[i] = m[i];

    if (crypto_scalarmult(q,m,p) != 0) fail("crypto_scalarmult returns nonzero");

    for (i = -16;i < mlen + 16;++i) if (m2[i] != m[i]) fail("crypto_scalarmult overwrites n input");
    for (i = -16;i < plen + 16;++i) if (p2[i] != p[i]) fail("crypto_scalarmult overwrites p input");
    for (i = -16;i < 0;++i) if (q2[i] != q[i]) fail("crypto_scalarmult writes before output");
    for (i = qlen;i < qlen + 16;++i) if (q2[i] != q[i]) fail("crypto_scalarmult writes after output");

    if (crypto_scalarmult(m2,m2,p) != 0) fail("crypto_scalarmult returns nonzero");
    for (i = 0;i < qlen;++i) if (q[i] != m2[i]) fail("crypto_scalarmult does not handle n overlap");
    for (i = 0;i < qlen;++i) m2[i] = m[i];

    if (crypto_scalarmult(p2,m2,p2) != 0) fail("crypto_scalarmult returns nonzero");
    for (i = 0;i < qlen;++i) if (q[i] != p2[i]) fail("crypto_scalarmult does not handle p overlap");

    if (crypto_scalarmult(r,n,q) != 0) fail("crypto_scalarmult returns nonzero");
    if (crypto_scalarmult(q,n,p) != 0) fail("crypto_scalarmult returns nonzero");
    if (crypto_scalarmult(p,m,q) != 0) fail("crypto_scalarmult returns nonzero");
    for (j = 0;j < plen;++j) if (p[j] != r[j]) fail("crypto_scalarmult not associative");
    for (j = 0;j < mlen;++j) m[j] ^= q[j % qlen];
    for (j = 0;j < nlen;++j) n[j] ^= p[j % plen];
  }

  for (i = 0;i < crypto_scalarmult_BYTES;++i) {
    checksum[2 * i] = "0123456789abcdef"[15 & (p[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & p[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  m -= 16;
  n -= 16;
  p -= 16;
  q -= 16;
  r -= 16;
  m2 -= 16;
  n2 -= 16;
  p2 -= 16;
  q2 -= 16;
  r2 -= 16;

  free(m);
  free(n);
  free(p);
  free(q);
  free(r);
  free(m2);
  free(n2);
  free(p2);
  free(q2);
  free(r2);

  avr_end();
  return 0;
}
