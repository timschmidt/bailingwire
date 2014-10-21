/*
 * File:    test/stack_crypto_dh.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "fail.h"
#include "avr.h"

#undef crypto_dh
#undef crypto_dh_keypair
#undef crypto_dh_SECRETKEYBYTES
#undef crypto_dh_PUBLICKEYBYTES
#undef crypto_dh_BYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_dh                XCONCAT(crypto_dh_,PRIMITIVE)
#define crypto_dh_keypair        XCONCAT3(crypto_dh_,PRIMITIVE,_keypair)
#define crypto_dh_SECRETKEYBYTES XCONCAT3(crypto_dh_,PRIMITIVE,_SECRETKEYBYTES)
#define crypto_dh_PUBLICKEYBYTES XCONCAT3(crypto_dh_,PRIMITIVE,_PUBLICKEYBYTES)
#define crypto_dh_BYTES          XCONCAT3(crypto_dh_,PRIMITIVE,_BYTES)

unsigned char pk[crypto_dh_PUBLICKEYBYTES];
unsigned char sk[crypto_dh_SECRETKEYBYTES];
unsigned char s[crypto_dh_BYTES];

unsigned int i;

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
    crypto_dh_keypair(pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_dh_keypair),-1,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_dh(s,pk,sk);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_dh),-1,ctr);

  avr_end();
  return 0;
}
