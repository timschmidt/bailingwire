/*
 * File:    test/test_crypto_box.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Jul 30 08:02:11 2014 +0200
 * Public Domain
 */

/*
 * Based on crypto_box/try.c version 20090118 by D. J. Bernstein
 * Public domain.
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "randombytes.h"
#include "avr.h"
#include "fail.h"

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

#define MAXTEST_BYTES 32

static unsigned char *ska;
static unsigned char *pka;
static unsigned char *skb;
static unsigned char *pkb;
static unsigned char *s;
static unsigned char *n;
static unsigned char *m;
static unsigned char *c;
static unsigned char *t;
static unsigned char *ska2;
static unsigned char *pka2;
static unsigned char *skb2;
static unsigned char *pkb2;
static unsigned char *s2;
static unsigned char *n2;
static unsigned char *m2;
static unsigned char *c2;
static unsigned char *t2;

#define sklen crypto_box_SECRETKEYBYTES
#define pklen crypto_box_PUBLICKEYBYTES
#define nlen crypto_box_NONCEBYTES
#define slen crypto_box_BEFORENMBYTES

char checksum[nlen * 2 + 1];

int main(void)
{
  long long i;
  long long j;

  ska  = calloc(sklen+32,1);
  if(!ska) fail("allocation of ska failed");
  pka  = calloc(pklen+32,1);
  if(!pka) fail("allocation of pka failed");
  skb  = calloc(sklen+32,1);
  if(!skb) fail("allocation of skb failed");
  pkb  = calloc(pklen+32,1);
  if(!pkb) fail("allocation of pkb failed");
  n    = calloc(nlen+32,1);
  if(!n) fail("allocation of n failed");
  m    = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES+32,1);
  if(!m) fail("allocation of m failed");
  c    = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES+32,1);
  if(!c) fail("allocation of c failed");
  t    = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES+32,1);
  if(!t) fail("allocation of t failed");
  s    = calloc(slen+32,1);
  if(!s) fail("allocation of s failed");
  ska2 = calloc(sklen+32,1);
  if(!ska2) fail("allocation of ska2 failed");
  pka2 = calloc(pklen+32,1);
  if(!pka2) fail("allocation of pka2 failed");
  skb2 = calloc(sklen+32,1);
  if(!skb2) fail("allocation of skb2 failed");
  pkb2 = calloc(pklen+32,1);
  if(!pkb2) fail("allocation of pkb2 failed");
  n2   = calloc(nlen+32,1);
  if(!n2) fail("allocation of n2 failed");
  m2   = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES+32,1);
  if(!m2) fail("allocation of m2 failed");
  c2   = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES+32,1);
  if(!c2) fail("allocation of c2 failed");
  t2   = calloc(MAXTEST_BYTES + crypto_box_ZEROBYTES+32,1);
  if(!t2) fail("allocation of t2 failed");
  s2   = calloc(slen+32,1);
  if(!s2) fail("allocation of s2 failed");


  ska  += 16;
  pka  += 16;
  skb  += 16;
  pkb  += 16;
  n    += 16;
  m    += 16;
  c    += 16;
  t    += 16;
  s    += 16;
  ska2 += 16;
  pka2 += 16;
  skb2 += 16;
  pkb2 += 16;
  n2   += 16;
  m2   += 16;
  c2   += 16;
  t2   += 16;
  s2   += 16;


  if (crypto_box_keypair(pka,ska) != 0) fail("crypto_box_keypair returns nonzero");
  if (crypto_box_keypair(pkb,skb) != 0) fail("crypto_box_keypair returns nonzero");

  for (j = 0;j < crypto_box_ZEROBYTES;++j) m[j] = 0;

  for (i = 0;i < MAXTEST_BYTES;i+=1+(i/4)) 
  {
    long long mlen = i + crypto_box_ZEROBYTES;
    long long tlen = i + crypto_box_ZEROBYTES;
    long long clen = i + crypto_box_ZEROBYTES;

    for (j = -16;j < 0;++j) ska[j] = random();
    for (j = -16;j < 0;++j) skb[j] = random();
    for (j = -16;j < 0;++j) pka[j] = random();
    for (j = -16;j < 0;++j) pkb[j] = random();
    for (j = -16;j < 0;++j) m[j] = random();
    for (j = -16;j < 0;++j) n[j] = random();

    for (j = sklen;j < sklen + 16;++j) ska[j] = random();
    for (j = sklen;j < sklen + 16;++j) skb[j] = random();
    for (j = pklen;j < pklen + 16;++j) pka[j] = random();
    for (j = pklen;j < pklen + 16;++j) pkb[j] = random();
    for (j = mlen;j < mlen + 16;++j) m[j] = random();
    for (j = nlen;j < nlen + 16;++j) n[j] = random();

    for (j = -16;j < sklen + 16;++j) ska2[j] = ska[j];
    for (j = -16;j < sklen + 16;++j) skb2[j] = skb[j];
    for (j = -16;j < pklen + 16;++j) pka2[j] = pka[j];
    for (j = -16;j < pklen + 16;++j) pkb2[j] = pkb[j];
    for (j = -16;j < mlen + 16;++j) m2[j] = m[j];
    for (j = -16;j < nlen + 16;++j) n2[j] = n[j];
    for (j = -16;j < clen + 16;++j) c2[j] = c[j] = random();

    if (crypto_box(c,m,mlen,n,pkb,ska) != 0) fail("crypto_box returns nonzero");

    for (j = -16;j < mlen + 16;++j) if (m2[j] != m[j]) fail("crypto_box overwrites m");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_box overwrites n");
    for (j = -16;j < 0;++j) if (c2[j] != c[j]) fail("crypto_box writes before output");
    for (j = clen;j < clen + 16;++j) if (c2[j] != c[j]) fail("crypto_box writes after output");
    for (j = 0;j < crypto_box_BOXZEROBYTES;++j)
      if (c[j] != 0) fail("crypto_box does not clear extra bytes");

    for (j = -16;j < sklen + 16;++j) if (ska2[j] != ska[j]) fail("crypto_box overwrites ska");
    for (j = -16;j < sklen + 16;++j) if (skb2[j] != skb[j]) fail("crypto_box overwrites skb");
    for (j = -16;j < pklen + 16;++j) if (pka2[j] != pka[j]) fail("crypto_box overwrites pka");
    for (j = -16;j < pklen + 16;++j) if (pkb2[j] != pkb[j]) fail("crypto_box overwrites pkb");

    for (j = -16;j < 0;++j) c[j] = random();
    for (j = clen;j < clen + 16;++j) c[j] = random();
    for (j = -16;j < clen + 16;++j) c2[j] = c[j];
    for (j = -16;j < tlen + 16;++j) t2[j] = t[j] = random();

    if (crypto_box_open(t,c,clen,n,pka,skb) != 0) fail("crypto_box_open returns nonzero");

    for (j = -16;j < clen + 16;++j) if (c2[j] != c[j]) fail("crypto_box_open overwrites c");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_box_open overwrites n");
    for (j = -16;j < 0;++j) if (t2[j] != t[j]) fail("crypto_box_open writes before output");
    for (j = tlen;j < tlen + 16;++j) if (t2[j] != t[j]) fail("crypto_box_open writes after output");
    for (j = 0;j < crypto_box_ZEROBYTES;++j)
      if (t[j] != 0) fail("crypto_box_open does not clear extra bytes");

    for (j = -16;j < sklen + 16;++j) if (ska2[j] != ska[j]) fail("crypto_box_open overwrites ska");
    for (j = -16;j < sklen + 16;++j) if (skb2[j] != skb[j]) fail("crypto_box_open overwrites skb");
    for (j = -16;j < pklen + 16;++j) if (pka2[j] != pka[j]) fail("crypto_box_open overwrites pka");
    for (j = -16;j < pklen + 16;++j) if (pkb2[j] != pkb[j]) fail("crypto_box_open overwrites pkb");

    for (j = 0;j < mlen;++j) if (t[j] != m[j]) fail("plaintext does not match");

    for (j = -16;j < slen + 16;++j) s2[j] = s[j] = random();
    if (crypto_box_beforenm(s,pkb,ska) != 0) fail("crypto_box_beforenm returns nonzero");
    for (j = -16;j < pklen + 16;++j) if (pka2[j] != pka[j]) fail("crypto_box_open overwrites pk");
    for (j = -16;j < sklen + 16;++j) if (skb2[j] != skb[j]) fail("crypto_box_open overwrites sk");
    for (j = -16;j < 0;++j) if (s2[j] != s[j]) fail("crypto_box_beforenm writes before output");
    for (j = slen;j < slen + 16;++j) if (s2[j] != s[j]) fail("crypto_box_beforenm writes after output");

    for (j = -16;j < slen + 16;++j) s2[j] = s[j];
    for (j = -16;j < tlen + 16;++j) t2[j] = t[j] = random();
    if (crypto_box_afternm(t,m,mlen,n,s) != 0) fail("crypto_box_afternm returns nonzero");
    for (j = -16;j < slen + 16;++j) if (s2[j] != s[j]) fail("crypto_box_afternm overwrites s");
    for (j = -16;j < mlen + 16;++j) if (m2[j] != m[j]) fail("crypto_box_afternm overwrites m");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_box_afternm overwrites n");
    for (j = -16;j < 0;++j) if (t2[j] != t[j]) fail("crypto_box_afternm writes before output");
    for (j = tlen;j < tlen + 16;++j) if (t2[j] != t[j]) fail("crypto_box_afternm writes after output");
    for (j = 0;j < crypto_box_BOXZEROBYTES;++j)
      if (t[j] != 0) fail("crypto_box_afternm does not clear extra bytes");
    for (j = 0;j < mlen;++j) if (t[j] != c[j]) fail("crypto_box_afternm does not match crypto_box");

    if (crypto_box_beforenm(s,pka,skb) != 0) fail("crypto_box_beforenm returns nonzero");

    for (j = -16;j < tlen + 16;++j) t2[j] = t[j] = random();
    if (crypto_box_open_afternm(t,c,clen,n,s) != 0) fail("crypto_box_open_afternm returns nonzero");
    for (j = -16;j < slen + 16;++j) if (s2[j] != s[j]) fail("crypto_box_open_afternm overwrites s");
    for (j = -16;j < mlen + 16;++j) if (m2[j] != m[j]) fail("crypto_box_open_afternm overwrites m");
    for (j = -16;j < nlen + 16;++j) if (n2[j] != n[j]) fail("crypto_box_open_afternm overwrites n");
    for (j = -16;j < 0;++j) if (t2[j] != t[j]) fail("crypto_box_open_afternm writes before output");
    for (j = tlen;j < tlen + 16;++j) if (t2[j] != t[j]) fail("crypto_box_open_afternm writes after output");
    for (j = 0;j < crypto_box_ZEROBYTES;++j)
      if (t[j] != 0) fail("crypto_box_open_afternm does not clear extra bytes");
    for (j = 0;j < mlen;++j) if (t[j] != m[j]) fail("crypto_box_open_afternm does not match crypto_box_open");

    for (j = 0;j < i;++j) n[j % nlen] ^= c[j + crypto_box_BOXZEROBYTES];
    if (i == 0) m[crypto_box_ZEROBYTES] = 0;
    m[i + crypto_box_ZEROBYTES] = m[crypto_box_ZEROBYTES];
    for (j = 0;j < i;++j) m[j + crypto_box_ZEROBYTES] ^= c[j + crypto_box_BOXZEROBYTES];
  }

  for (i = 0;i < nlen;++i) {
    checksum[2 * i] = "0123456789abcdef"[15 & (n[i] >> 4)];
    checksum[2 * i + 1] = "0123456789abcdef"[15 & n[i]];
  }
  checksum[2 * i] = 0;

  print("Checksum: ");
  print(checksum);
  print("\n");

  ska  -= 16;
  pka  -= 16;
  skb  -= 16;
  pkb  -= 16;
  n    -= 16;
  m    -= 16;
  c    -= 16;
  t    -= 16;
  s    -= 16;
  ska2 -= 16;
  pka2 -= 16;
  skb2 -= 16;
  pkb2 -= 16;
  n2   -= 16;
  m2   -= 16;
  c2   -= 16;
  t2   -= 16;
  s2   -= 16;


  free(ska);
  free(pka);
  free(skb);
  free(pkb);
  free(n);
  free(m);
  free(c);
  free(t);
  free(s);
  free(ska2);
  free(pka2);
  free(skb2);
  free(pkb2);
  free(n2);
  free(m2);
  free(c2);
  free(t2);
  free(s2);

  avr_end();
  return 0;
}
