/*
 * File:    avrnacl_8bitc/shared/bigint.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 12 08:23:16 2014 +0200
 * Public Domain
 */

#include "avrnacl.h"
#include "bigint.h"

unsigned char bigint_add(unsigned char *r, const unsigned char *a, const unsigned char *b, unsigned int len) 
{
  unsigned int i;
  crypto_uint16 tmp = 0;
  for (i=0; i<len; i++) 
  {
    tmp = a[i] + b[i] + tmp;
    r[i] = tmp & 0xff;
    tmp >>= 8;
  }
  return (unsigned char)tmp;
}

unsigned char bigint_sub(unsigned char *r, const unsigned char *a, const unsigned char *b, unsigned int len) 
{
  unsigned int i;
  crypto_uint16 tmp = 0;
  for (i=0; i<len; i++) 
  {
    tmp = a[i] - b[i] - tmp;
    r[i] = tmp & 0xff;
    tmp >>= 15;
  }
  return (unsigned char)tmp;
}

void bigint_mul(unsigned char *r, const unsigned char *a, const unsigned char *b, unsigned int len) 
{
  unsigned int i,j;
  crypto_uint16 t;
  for(i=0;i<2*len;i++)
    r[i] = 0;

  for (i=0; i<len; i++) {
    t = 0;
    for (j=0; j<len; j++) {
      t=r[i+j]+a[i]*b[j] + (t>>8);
      r[i+j]=(t & 0xFF);
    }
    r[i+len]=(t>>8);
  }
}

static void bigint_mul16c(unsigned char r[34], const unsigned char a[17], const unsigned char b[17]) 
{
  unsigned char t0[9], t1[9],t[18], i;
  int u;
  bigint_mul(r, a, b, 8);
  bigint_mul(r+16, a+8, b+8, 9);

  t0[8] = a[16] + bigint_add(t0,a,a+8,8);
  t1[8] = b[16] + bigint_add(t1,b,b+8,8);
  bigint_mul(t,t0,t1,9);
  t[17] -= bigint_sub(t,t,r+16,17);
  u = t[16];
  //t[16] -= bigint_sub(t,t,r,16);
  u -= bigint_sub(t,t,r,16);
  t[16] = u & 0xff;
  u>>=15;
  t[17] -= u;
  u = bigint_add(r+8,r+8,t,17);
  for(i=25;i<34;i++)
  {
    u += r[i];
    r[i] = u & 0xff;
    u >>= 8;
  }
}

static void bigint_mul16(unsigned char r[32], const unsigned char a[16], const unsigned char b[16]) 
{
  unsigned char t0[9], t1[9],t[18], i;
  int u;
  bigint_mul(r, a, b, 8);
  bigint_mul(r+16, a+8, b+8, 8);
  t0[8] = bigint_add(t0,a,a+8,8);
  t1[8] = bigint_add(t1,b,b+8,8);
  bigint_mul(t,t0,t1,9);
  t[16] -= bigint_sub(t,t,r,16);
  t[16] -= bigint_sub(t,t,r+16,16);
  u = bigint_add(r+8,r+8,t,17);
  for(i=25;i<32;i++)
  {
    u += r[i];
    r[i] = u & 0xff;
    u >>= 8;
  }
}

void bigint_mul32(unsigned char *r, const unsigned char *a, const unsigned char *b) 
{
  unsigned char t0[17], t1[17],t[34], i;
  int u;
  bigint_mul16(r, a, b);
  bigint_mul16(r+32, a+16, b+16);
  t0[16] = bigint_add(t0,a,a+16,16);
  t1[16] = bigint_add(t1,b,b+16,16);
  bigint_mul16c(t,t0,t1);
  t[32] -= bigint_sub(t,t,r,32);
  t[32] -= bigint_sub(t,t,r+32,32);
  u = bigint_add(r+16,r+16,t,33);
  for(i=49;i<64;i++)
  {
    u += r[i];
    r[i] = u & 0xff;
    u >>= 8;
  }
}


void bigint_cmov(unsigned char *r, const unsigned char *x, unsigned char b, unsigned int len)
{
  unsigned int i;
  unsigned char mask = b;
  mask = -mask;
  for(i=0;i<len;i++) 
    r[i] ^= mask & (x[i] ^ r[i]);
}

