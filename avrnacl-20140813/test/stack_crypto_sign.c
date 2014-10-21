/*
 * File:    test/stack_crypto_sign.c
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

#undef crypto_sign
#undef crypto_sign_open
#undef crypto_sign_keypair
#undef crypto_sign_SECRETKEYBYTES
#undef crypto_sign_PUBLICKEYBYTES
#undef crypto_sign_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_sign                XCONCAT(crypto_sign_,PRIMITIVE)
#define crypto_sign_open           XCONCAT3(crypto_sign_,PRIMITIVE,_open)
#define crypto_sign_keypair        XCONCAT3(crypto_sign_,PRIMITIVE,_keypair)
#define crypto_sign_SECRETKEYBYTES XCONCAT3(crypto_sign_,PRIMITIVE,_SECRETKEYBYTES)
#define crypto_sign_PUBLICKEYBYTES XCONCAT3(crypto_sign_,PRIMITIVE,_PUBLICKEYBYTES)
#define crypto_sign_BYTES          XCONCAT3(crypto_sign_,PRIMITIVE,_BYTES)

#define MAXTEST_BYTES 1024

#define pklen crypto_sign_PUBLICKEYBYTES
#define sklen crypto_sign_SECRETKEYBYTES

unsigned char pk[pklen];
unsigned char sk[sklen];
unsigned char sm[MAXTEST_BYTES + crypto_sign_BYTES]; 
crypto_uint16 smlen;
  
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

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_sign_keypair(pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_sign_keypair),-1,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_sign(sm,&smlen,sm,0,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_sign),0,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_sign_open(sm,&mlen,sm,smlen,pk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_sign_open),smlen,ctr);

  for(j=1;j<=MAXTEST_BYTES;j<<=1)
  {
    mlen = j;

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_sign(sm,&smlen,sm,mlen,sk);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_sign),mlen,ctr);

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_sign_open(sm,&mlen,sm,smlen,pk);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_sign_open),smlen,ctr);
  }

  avr_end();
  return 0;
}
