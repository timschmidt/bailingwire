/*
 * File:    test/stack_crypto_secretbox.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "cpucycles.h"
#include "fail.h"
#include "avr.h"

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
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_secretbox              XCONCAT(crypto_secretbox_,PRIMITIVE)
#define crypto_secretbox_open         XCONCAT3(crypto_secretbox_,PRIMITIVE,_open)
#define crypto_secretbox_KEYBYTES     XCONCAT3(crypto_secretbox_,PRIMITIVE,_KEYBYTES)
#define crypto_secretbox_NONCEBYTES   XCONCAT3(crypto_secretbox_,PRIMITIVE,_NONCEBYTES)
#define crypto_secretbox_ZEROBYTES    XCONCAT3(crypto_secretbox_,PRIMITIVE,_ZEROBYTES)
#define crypto_secretbox_BOXZEROBYTES XCONCAT3(crypto_secretbox_,PRIMITIVE,_BOXZEROBYTES)

#define MAXTEST_BYTES 1024

#define klen crypto_secretbox_KEYBYTES
#define nlen crypto_secretbox_NONCEBYTES

unsigned char k[klen];
unsigned char n[nlen];
unsigned char c[MAXTEST_BYTES + crypto_secretbox_ZEROBYTES];

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

int main(void)
{
  volatile unsigned char a; /* Mark the beginning of the stack */

  for (j = 0;j < crypto_secretbox_ZEROBYTES;++j) c[j] = 0;

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_secretbox(c,c,crypto_secretbox_ZEROBYTES,n,k);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_secretbox),crypto_secretbox_ZEROBYTES,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_secretbox_open(c,c,crypto_secretbox_ZEROBYTES,n,k);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_secretbox_open),crypto_secretbox_ZEROBYTES,ctr);


  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j + crypto_box_ZEROBYTES;

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_secretbox(c,c,mlen,n,k);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_secretbox),mlen,ctr);

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_secretbox_open(c,c,mlen,n,k);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_secretbox_open),mlen,ctr);
  }

  avr_end();
  return 0;
}
