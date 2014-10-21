/*
 * File:    test/stack_crypto_core.c
 * Author:  Michael Hutter, Peter Schwabe
 * Version: Wed Aug 13 04:15:13 2014 +0200
 * Public Domain
 */

#include <stdlib.h>
#include "avrnacl.h"
#include "print.h"
#include "fail.h"
#include "avr.h"

#undef crypto_core
#undef crypto_core_OUTPUTBYTES
#undef crypto_core_INPUTBYTES
#undef crypto_core_KEYBYTES
#undef crypto_core_CONSTBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_core             XCONCAT(crypto_core_,PRIMITIVE)
#define crypto_core_OUTPUTBYTES XCONCAT3(crypto_core_,PRIMITIVE,_OUTPUTBYTES)
#define crypto_core_INPUTBYTES  XCONCAT3(crypto_core_,PRIMITIVE,_INPUTBYTES)
#define crypto_core_KEYBYTES    XCONCAT3(crypto_core_,PRIMITIVE,_KEYBYTES)
#define crypto_core_CONSTBYTES  XCONCAT3(crypto_core_,PRIMITIVE,_CONSTBYTES)

#define hlen crypto_core_OUTPUTBYTES
#define nlen crypto_core_INPUTBYTES
#define klen crypto_core_KEYBYTES
#define clen crypto_core_CONSTBYTES
 
static unsigned char h[hlen];
static unsigned char n[nlen];
static unsigned char k[klen];
static unsigned char c[clen];

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
    crypto_core(h,n,k,c);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_core),-1,ctr);

  avr_end();
  return 0;
}
