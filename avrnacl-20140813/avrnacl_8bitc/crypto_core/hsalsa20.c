/*
 * File:    avrnacl_8bitc/crypto_core/hsalsa20.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

/*
 * Based on tweetnacl.c version 20140427.
 * by Daniel J. Bernstein, Wesley Janssen, Tanja Lange, and Peter Schwabe
 */

#include "avrnacl.h"

static crypto_uint32 L32(crypto_uint32 x,int c) 
{ 
  return (x << c) | (x >> (32 - c)); 
}

static crypto_uint32 ld32(const unsigned char *x)
{
  crypto_uint32 u = x[3];
  u = (u<<8)|x[2];
  u = (u<<8)|x[1];
  return (u<<8)|x[0];
}

static void st32(unsigned char *x,crypto_uint32 u)
{
  int i;
  for(i=0;i<4;i++)
  { 
    x[i] = u; 
    u >>= 8; 
  }
}

static void core(unsigned char *out,const unsigned char *in,const unsigned char *k,const unsigned char *c)
{
  crypto_uint32 w[16],x[16],y[16],t[4];
  int i,j,m;

  for(i=0;i<4;i++)
  {
    x[5*i] = ld32(c+4*i);
    x[1+i] = ld32(k+4*i);
    x[6+i] = ld32(in+4*i);
    x[11+i] = ld32(k+16+4*i);
  }

  for(i=0;i<16;i++)
    y[i] = x[i];

  for(i=0;i<20;i++)
  {
    for(j=0;j<4;j++)
    {
      for(m=0;m<4;m++) 
        t[m] = x[(5*j+4*m)%16];
      t[1] ^= L32(t[0]+t[3], 7);
      t[2] ^= L32(t[1]+t[0], 9);
      t[3] ^= L32(t[2]+t[1],13);
      t[0] ^= L32(t[3]+t[2],18);
      for(m=0;m<4;m++) 
        w[4*j+(j+m)%4] = t[m];
    }
    for(m=0;m<16;m++) 
      x[m] = w[m];
  }

  for(i=0;i<16;i++) 
    x[i] += y[i];
  for(i=0;i<4;i++) 
  {
    x[5*i] -= ld32(c+4*i);
    x[6+i] -= ld32(in+4*i);
  }
  for(i=0;i<4;i++) 
  {
    st32(out+4*i,x[5*i]);
    st32(out+16+4*i,x[6+i]);
  }
}

int crypto_core_hsalsa20(unsigned char *out,const unsigned char *in,const unsigned char *k,const unsigned char *c)
{
  core(out,in,k,c);
  return 0;
}

