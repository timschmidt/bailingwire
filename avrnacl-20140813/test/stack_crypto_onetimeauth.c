/*
 * File:    test/stack_crypto_onetimeauth.c
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

#undef crypto_onetimeauth
#undef crypto_onetimeauth_verify
#undef crypto_onetimeauth_BYTES
#undef crypto_onetimeauth_KEYBYTES

#define CONCAT(x,y) x ## y
#define CONCAT3(x,y,z) x ## y ## z
#define XCONCAT(x,y) CONCAT(x,y)
#define XCONCAT3(x,y,z) CONCAT3(x,y,z)
#define XSTR(s) STR(s)
#define STR(s) #s

#define crypto_onetimeauth             XCONCAT(crypto_onetimeauth_,PRIMITIVE)
#define crypto_onetimeauth_verify      XCONCAT3(crypto_onetimeauth_,PRIMITIVE,_verify)
#define crypto_onetimeauth_BYTES       XCONCAT3(crypto_onetimeauth_,PRIMITIVE,_BYTES)
#define crypto_onetimeauth_KEYBYTES    XCONCAT3(crypto_onetimeauth_,PRIMITIVE,_KEYBYTES)

#define MAXTEST_BYTES 1024

unsigned char h[crypto_onetimeauth_BYTES];
unsigned char m[MAXTEST_BYTES];
unsigned char k[crypto_onetimeauth_KEYBYTES];

unsigned int i,mlen;

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
    crypto_onetimeauth(h,m,0,k);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_onetimeauth),0,ctr);

  for(i=0;i<5;i++)
  {
    canary = random();
    WRITE_CANARY(&a);
    crypto_onetimeauth_verify(h,m,0,k);
    newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
    ctr = (newctr>ctr)?newctr:ctr;
  }
  print_stack(XSTR(crypto_onetimeauth_verify),0,ctr);


  for(mlen=1;mlen<=MAXTEST_BYTES;mlen<<=1)
  {
    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_onetimeauth(h,m,mlen,k);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_onetimeauth),mlen,ctr);

    for(i=0;i<5;i++)
    {
      canary = random();
      WRITE_CANARY(&a);
      crypto_onetimeauth_verify(h,m,mlen,k);
      newctr =(unsigned int)&a - (unsigned int)&_end - stack_count(canary);
      ctr = (newctr>ctr)?newctr:ctr;
    }
    print_stack(XSTR(crypto_onetimeauth_verify),mlen,ctr);
  }

  avr_end();
  return 0;
}
