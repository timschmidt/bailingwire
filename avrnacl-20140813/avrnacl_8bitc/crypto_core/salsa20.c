/*
 * File:    avrnacl_8bitc/crypto_core/salsa20.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Tue Aug 5 05:39:21 2014 +0200
 * Public Domain
 */

#define ROUNDS 20

#include "bigint.h"

typedef struct {
  unsigned char v[4];
} myu32;

static void myu32_load_littleendian(myu32 *r, const unsigned char *x)
{
  r->v[0] = x[0];
  r->v[1] = x[1];
  r->v[2] = x[2];
  r->v[3] = x[3];
}

static void myu32_store_littleendian(unsigned char *r, myu32 *x)
{
  r[0] = x->v[0];
  r[1] = x->v[1];
  r[2] = x->v[2];
  r[3] = x->v[3];
}

static void myu32_xor(myu32 *r, const myu32 *x, const myu32 *y)
{
  r->v[0] = x->v[0] ^ y->v[0];
  r->v[1] = x->v[1] ^ y->v[1];
  r->v[2] = x->v[2] ^ y->v[2];
  r->v[3] = x->v[3] ^ y->v[3];
}

static void myu32_add(myu32 *r, const myu32 *x, const myu32 *y)
{
  bigint_add(r->v, x->v, y->v, 4);
}

static void myu32_rol(myu32 *r, unsigned char n)
{
  myu32 t = *r;
  unsigned char u = (32-n) >> 3;
  unsigned char l = (32-n) & 7;
  unsigned char i;
  for(i=0;i<4;i++)
    r->v[i] = (t.v[(i+u+1)&3] << (8-l)) | (t.v[(i+u)&3] >> l);
}

static void quarterround(myu32 *a, myu32 *b, myu32 *c, myu32 *d)
{
  myu32 t;
  myu32_add(&t, a, b);
  myu32_rol(&t, 7);
  myu32_xor(c, c, &t);
  myu32_add(&t, c, a);
  myu32_rol(&t, 9);
  myu32_xor(d, d, &t);
  myu32_add(&t, d, c);
  myu32_rol(&t, 13);
  myu32_xor(b, b, &t);
  myu32_add(&t, b, d);
  myu32_rol(&t, 18);
  myu32_xor(a, a, &t);
}

int crypto_core_salsa20(
        unsigned char *out,
  const unsigned char *in,
  const unsigned char *k,
  const unsigned char *c
)
{
  myu32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;
  myu32 j0, j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14, j15;
  unsigned char i;

  myu32_load_littleendian(&x0, c + 0);
  myu32_load_littleendian(&j0, c + 0);
  myu32_load_littleendian(&x1, k + 0);
  myu32_load_littleendian(&j1, k + 0);
  myu32_load_littleendian(&x2, k + 4);
  myu32_load_littleendian(&j2, k + 4);
  myu32_load_littleendian(&x3, k + 8);
  myu32_load_littleendian(&j3, k + 8);
  myu32_load_littleendian(&x4, k + 12);
  myu32_load_littleendian(&j4, k + 12);
  myu32_load_littleendian(&x5, c + 4);
  myu32_load_littleendian(&j5, c + 4);
  myu32_load_littleendian(&x6, in + 0);
  myu32_load_littleendian(&j6, in + 0);
  myu32_load_littleendian(&x7, in + 4);
  myu32_load_littleendian(&j7, in + 4);
  myu32_load_littleendian(&x8, in + 8);
  myu32_load_littleendian(&j8, in + 8);
  myu32_load_littleendian(&x9, in + 12);
  myu32_load_littleendian(&j9, in + 12);
  myu32_load_littleendian(&x10, c + 8);
  myu32_load_littleendian(&j10, c + 8);
  myu32_load_littleendian(&x11, k + 16);
  myu32_load_littleendian(&j11, k + 16);
  myu32_load_littleendian(&x12, k + 20);
  myu32_load_littleendian(&j12, k + 20);
  myu32_load_littleendian(&x13, k + 24);
  myu32_load_littleendian(&j13, k + 24);
  myu32_load_littleendian(&x14, k + 28);
  myu32_load_littleendian(&j14, k + 28);
  myu32_load_littleendian(&x15, c + 12);
  myu32_load_littleendian(&j15, c + 12);

  for (i = ROUNDS;i > 0;i -= 2) 
  {
    quarterround( &x0, &x12,  &x4,  &x8);
    quarterround( &x5,  &x1,  &x9, &x13);
    quarterround(&x10,  &x6, &x14,  &x2);
    quarterround(&x15, &x11,  &x3,  &x7);
    quarterround( &x0,  &x3,  &x1,  &x2);
    quarterround( &x5,  &x4,  &x6,  &x7);
    quarterround(&x10,  &x9, &x11,  &x8);
    quarterround(&x15, &x14, &x12, &x13);
  }

  myu32_add(&x0,  &x0,  &j0);
  myu32_add(&x1,  &x1,  &j1);
  myu32_add(&x2,  &x2,  &j2);
  myu32_add(&x3,  &x3,  &j3);
  myu32_add(&x4,  &x4,  &j4);
  myu32_add(&x5,  &x5,  &j5);
  myu32_add(&x6,  &x6,  &j6);
  myu32_add(&x7,  &x7,  &j7);
  myu32_add(&x8,  &x8,  &j8);
  myu32_add(&x9,  &x9,  &j9);
  myu32_add(&x10, &x10, &j10);
  myu32_add(&x11, &x11, &j11);
  myu32_add(&x12, &x12, &j12);
  myu32_add(&x13, &x13, &j13);
  myu32_add(&x14, &x14, &j14);
  myu32_add(&x15, &x15, &j15);

  myu32_store_littleendian(out +  0,&x0);
  myu32_store_littleendian(out +  4,&x1);
  myu32_store_littleendian(out +  8,&x2);
  myu32_store_littleendian(out + 12,&x3);
  myu32_store_littleendian(out + 16,&x4);
  myu32_store_littleendian(out + 20,&x5);
  myu32_store_littleendian(out + 24,&x6);
  myu32_store_littleendian(out + 28,&x7);
  myu32_store_littleendian(out + 32,&x8);
  myu32_store_littleendian(out + 36,&x9);
  myu32_store_littleendian(out + 40,&x10);
  myu32_store_littleendian(out + 44,&x11);
  myu32_store_littleendian(out + 48,&x12);
  myu32_store_littleendian(out + 52,&x13);
  myu32_store_littleendian(out + 56,&x14);
  myu32_store_littleendian(out + 60,&x15);

  return 0;
}
