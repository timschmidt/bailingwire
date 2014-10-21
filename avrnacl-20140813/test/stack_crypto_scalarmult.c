/*
 * File:    test/stack_crypto_scalarmult.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "fail.h"
#include "avr.h"

#undef crypto_scalarmult
#undef crypto_scalarmult_base
#undef crypto_scalarmult_BYTES
#undef crypto_scalarmult_SCALARBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_scalarmult             XCONCAT(crypto_scalarmult_,PRIMITIVE)
#define crypto_scalarmult_base        XCONCAT3(crypto_scalarmult_,PRIMITIVE,_base)
#define crypto_scalarmult_BYTES       XCONCAT3(crypto_scalarmult_,PRIMITIVE,_BYTES)
#define crypto_scalarmult_SCALARBYTES XCONCAT3(crypto_scalarmult_,PRIMITIVE,_SCALARBYTES)

#define nlen crypto_scalarmult_SCALARBYTES
#define qlen crypto_scalarmult_BYTES

unsigned char i;
unsigned char n[nlen];
unsigned char q[qlen];

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
    crypto_scalarmult(q,n,q);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_scalarmult),-1,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_scalarmult_base(q,n);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_scalarmult_base),-1,ctr);

  avr_end();
  return 0;
}
