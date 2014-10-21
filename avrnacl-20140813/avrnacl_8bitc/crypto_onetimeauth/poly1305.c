/*
 * File:    avrnacl_8bitc/crypto_onetimeauth/poly1305.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 6 13:19:40 2014 +0200
 * Public Domain
 */

#include "avrnacl.h"
#include "bigint.h"

static void add(unsigned char h[17],const unsigned char x[17])
{
  unsigned char c = 0;
  unsigned char i;
  unsigned char th;
  for(i=0;i<17;i++)
  {
    th = h[i];
    h[i] += x[i] + c;
    c = (h[i] < th) || (h[i] < x[i]) || (c && (h[i] == th));
  }
}

static const unsigned char minusp[17] = {
  5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 252
} ;

static void freeze(unsigned char h[17])
{
  unsigned char horig[17];
  unsigned char j,c;
  unsigned char negative;
  unsigned int t = (h[16]>>2) * 5;
  h[16] &= 0x3;
  h[0] += t & 0xff;
  c = h[0] < (t & 0xff);
  for(j=1;j<17;j++)
  {
    h[j] += c;
    c = (h[j] == 0) && c;
  }

  for (j = 0;j < 17;++j) 
    horig[j] = h[j];
  add(h,minusp);
  negative = -(h[16] >> 7);
  for (j = 0;j < 17;++j) 
    h[j] ^= negative & (horig[j] ^ h[j]);
}

static void mulmod(unsigned char h[17],const unsigned char r[17])
{
  unsigned char hr[34];
  unsigned char thr;
  unsigned char c;
  unsigned char i,k;
  unsigned int t;

  // Multiply
  bigint_mul(hr,h,r,17);

  // Reduce mod 2^136
  c = 0;
  for(i=16;i<32;i++)
  {
    t = (hr[i] >> 2) ^ ((hr[i+1] & 0x3) << 6);
    hr[i] &= 0x3;
    hr[i+1] &= 0xfc;
    t *= 5;
    thr = hr[i-16];
    hr[i-16] += (t & 0xff);
    c = (hr[i-16] < (t & 0xff)) || (hr[i-16] < thr);
    thr = hr[i-15];
    hr[i-15] += (t >> 8) + c;
    c = (hr[i-15] < (t >> 8)) || (hr[i-15] < thr);
    for(k=i-14;k<17;k++)
    {
      hr[k] += c;
      c = (hr[k] == 0) && c;
    }
  }
  t = (hr[32] >> 2) * 5;
  hr[16] += (t & 0xff);

  for(i=0;i<17;i++)
    h[i] = hr[i];
}


int crypto_onetimeauth_poly1305(unsigned char *out,const unsigned char *in,crypto_uint16 inlen,const unsigned char *k)
{
  unsigned char j;
  unsigned char r[17];
  unsigned char h[17];
  unsigned char c[17];

  r[0] = k[0];
  r[1] = k[1];
  r[2] = k[2];
  r[3] = k[3] & 15;
  r[4] = k[4] & 252;
  r[5] = k[5];
  r[6] = k[6];
  r[7] = k[7] & 15;
  r[8] = k[8] & 252;
  r[9] = k[9];
  r[10] = k[10];
  r[11] = k[11] & 15;
  r[12] = k[12] & 252;
  r[13] = k[13];
  r[14] = k[14];
  r[15] = k[15] & 15;
  r[16] = 0;

  for (j = 0;j < 17;++j) h[j] = 0;

  while (inlen > 0) 
  {
    for (j = 0;j < 17;++j) c[j] = 0;
    for (j = 0;(j < 16) && (j < inlen);++j) c[j] = in[j];
    c[j] = 1;
    in += j; inlen -= j;
    add(h,c);
    mulmod(h,r);
  }

  freeze(h);

  for (j = 0;j < 16;++j) c[j] = k[j + 16];
  c[16] = 0;
  add(h,c);
  for (j = 0;j < 16;++j) out[j] = h[j];
  return 0;
}

int crypto_onetimeauth_poly1305_verify(
    const unsigned char *h,
    const unsigned char *in,crypto_uint16 inlen,
    const unsigned char *k
    )
{
  unsigned char correct[16];
  crypto_onetimeauth_poly1305(correct,in,inlen,k);
  return crypto_verify_16(h,correct);
}
