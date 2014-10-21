/*
 * File:    test/stack_crypto_box.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "fail.h"
#include "avr.h"

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
#define XSTR(s) STR(s)
#define STR(s) #s

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

#define MAXTEST_BYTES 1024

#define sklen crypto_box_SECRETKEYBYTES
#define pklen crypto_box_PUBLICKEYBYTES
#define nlen crypto_box_NONCEBYTES
#define slen crypto_box_BEFORENMBYTES

unsigned char sk[sklen];
unsigned char pk[pklen];
unsigned char s[slen];
unsigned char n[nlen];
unsigned char c[MAXTEST_BYTES + crypto_box_ZEROBYTES];
  
unsigned int i,j,mlen;

unsigned int ctr=0,newctr;
unsigned char canary;
volatile unsigned char *p;
extern unsigned char _end; 
extern unsigned char __stack; 

static unsigned int stack_count(unsigned char canary)
{
  const unsigned char *p = &_end;
  unsigned int c = 0;
  while(*p == canary && p <= &__stack)
  {
    p++;
    c++;
  }
  return c;
} 

#define WRITE_CANARY(X) {p=X;while(p>= &_end) *(p--) = canary;}

unsigned char *doof;

int main(void)
{
  volatile unsigned char a; /* Mark the beginning of the stack */

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_box_keypair(pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_box_keypair),-1,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_box_beforenm(s,pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_box_beforenm),-1,ctr);

  for (j = 0;j < crypto_box_ZEROBYTES;++j) c[j] = 0;

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_box(c,c,crypto_box_ZEROBYTES,n,pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_box),crypto_box_ZEROBYTES,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_box_open(c,c,crypto_box_ZEROBYTES,n,pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_box_open),crypto_box_ZEROBYTES,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_box_afternm(c,c,crypto_box_ZEROBYTES,n,s);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_box_afternm),crypto_box_ZEROBYTES,ctr);
     

  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j + crypto_box_ZEROBYTES;

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_box(c,c,mlen,n,pk,sk);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_box),mlen,ctr);

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_box_open(c,c,mlen,n,pk,sk);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_box_open),mlen,ctr);

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_box_afternm(c,c,mlen,n,s);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_box_afternm),mlen,ctr);
  }

  avr_end();
  return 0;
}
