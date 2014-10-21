/*
 * File:    avrnacl_8bitc/crypto_stream/salsa20.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 12 08:23:16 2014 +0200
 * Public Domain
 */

/*
 * Based on tweetnacl.c version 20140427.
 * by Daniel J. Bernstein, Wesley Janssen, Tanja Lange, and Peter Schwabe
 */

#include "avrnacl.h"
#include "bigint.h"

static const unsigned char sigma[16] = "expand 32-byte k";

int crypto_stream_salsa20_xor(
    unsigned char *c, 
    const unsigned char *m,crypto_uint16 mlen, 
    const unsigned char *n,const unsigned char *k
    )
{
  unsigned char z[16],x[64],u[8],i;

  for(i=0;i<8;i++) 
  {
    z[i] = n[i];
    z[i+8] = 0;
    u[i] = 0;
  }
  u[0] = 1;

  while (mlen >= 64) 
  {
    if(m)
    {
      crypto_core_salsa20(x,z,k,sigma);
      for(i=0;i<64;i++)
        c[i] = m[i] ^ x[i];
    }
    else
      crypto_core_salsa20(c,z,k,sigma);

    bigint_add(z+8,z+8,u,8);
    mlen -= 64;
    c += 64;
    if (m) m += 64;
  }
  if (mlen) 
  {
    crypto_core_salsa20(x,z,k,sigma);
    if(m)
      for(i=0;i<mlen;i++)
        c[i] = x[i] ^ m[i];
    else
      for(i=0;i<mlen;i++)
        c[i] = x[i];
  }
  return 0;
}

int crypto_stream_salsa20(
    unsigned char *c,crypto_uint16 clen,
    const unsigned char *n,
    const unsigned char *k
    )
{
  return crypto_stream_salsa20_xor(c,0,clen,n,k);
}
