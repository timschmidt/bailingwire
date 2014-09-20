/*
 *  HardwareSerial.h - Hardware serial library for Wiring
 *  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
 * 
 *  This file is part of the bailingwire firmware.
 *
 *  Bailingwire is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Bailingwire is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Bailingwire.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Modified 28 September 2010 by Mark Sproul
 * Modified 09 September 2014 by Timothy Schmidt
 */

#ifndef DRIVER_ATTINY_H
#define DRIVER_ATTINY_H

#if !defined(SERIAL_PORT) 
#define SERIAL_PORT 0
#endif

// The presence of the UBRRH register is used to detect a UART.
#define UART_PRESENT(port) ((port == 0 && (defined(UBRRH) || defined(UBRR0H))) || \
						(port == 1 && defined(UBRR1H)) || (port == 2 && defined(UBRR2H)) || \
						(port == 3 && defined(UBRR3H)))				
						
// These are macros to build serial port register names for the selected SERIAL_PORT (C preprocessor
// requires two levels of indirection to expand macro values properly)
#define SERIAL_REGNAME(registerbase,number,suffix) SERIAL_REGNAME_INTERNAL(registerbase,number,suffix)
#if SERIAL_PORT == 0 && (!defined(UBRR0H) || !defined(UDR0)) // use un-numbered registers if necessary
#define SERIAL_REGNAME_INTERNAL(registerbase,number,suffix) registerbase##suffix
#else
#define SERIAL_REGNAME_INTERNAL(registerbase,number,suffix) registerbase##number##suffix
#endif

// Registers used by MarlinSerial class (these are expanded 
// depending on selected serial port
#define M_UCSRxA SERIAL_REGNAME(UCSR,SERIAL_PORT,A) // defines M_UCSRxA to be UCSRnA where n is the serial port number
#define M_UCSRxB SERIAL_REGNAME(UCSR,SERIAL_PORT,B) 
#define M_RXENx SERIAL_REGNAME(RXEN,SERIAL_PORT,)    
#define M_TXENx SERIAL_REGNAME(TXEN,SERIAL_PORT,)    
#define M_RXCIEx SERIAL_REGNAME(RXCIE,SERIAL_PORT,)    
#define M_UDREx SERIAL_REGNAME(UDRE,SERIAL_PORT,)    
#define M_UDRx SERIAL_REGNAME(UDR,SERIAL_PORT,)  
#define M_UBRRxH SERIAL_REGNAME(UBRR,SERIAL_PORT,H)
#define M_UBRRxL SERIAL_REGNAME(UBRR,SERIAL_PORT,L)
#define M_RXCx SERIAL_REGNAME(RXC,SERIAL_PORT,)
#define M_USARTx_RX_vect SERIAL_REGNAME(USART,SERIAL_PORT,_RX_vect)
#define M_U2Xx SERIAL_REGNAME(U2X,SERIAL_PORT,)



#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0


#ifndef AT90USB
// Define constants and variables for buffering incoming serial data.  We're
// using a ring buffer (I think), in which rx_buffer_head is the index of the
// location to which to write the next incoming character and rx_buffer_tail
// is the index of the location from which to read.
#define RX_BUFFER_SIZE 128


struct ring_buffer
{
  unsigned char buffer[RX_BUFFER_SIZE];
  int head;
  int tail;
};

#if UART_PRESENT(SERIAL_PORT)
  extern ring_buffer rx_buffer;
#endif

class MarlinSerial //: public Stream
{

  public:
    MarlinSerial();
    void begin(long);
    void end();
    int peek(void);
    int read(void);
    void flush(void);
    
    FORCE_INLINE int available(void)
    {
      return (unsigned int)(RX_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % RX_BUFFER_SIZE;
    }
    
    FORCE_INLINE void write(uint8_t c)
    {
      while (!((M_UCSRxA) & (1 << M_UDREx)))
        ;

      M_UDRx = c;
    }
    
    
    FORCE_INLINE void checkRx(void)
    {
      if((M_UCSRxA & (1<<M_RXCx)) != 0) {
        unsigned char c  =  M_UDRx;
        int i = (unsigned int)(rx_buffer.head + 1) % RX_BUFFER_SIZE;

        // if we should be storing the received character into the location
        // just before the tail (meaning that the head would advance to the
        // current location of the tail), we're about to overflow the buffer
        // and so we don't write the character or advance the head.
        if (i != rx_buffer.tail) {
          rx_buffer.buffer[rx_buffer.head] = c;
          rx_buffer.head = i;
        }
      }
    }
    
    
    private:
    void printNumber(unsigned long, uint8_t);
    void printFloat(double, uint8_t);
    
    
  public:
    
    FORCE_INLINE void write(const char *str)
    {
      while (*str)
        write(*str++);
    }


    FORCE_INLINE void write(const uint8_t *buffer, size_t size)
    {
      while (size--)
        write(*buffer++);
    }

    FORCE_INLINE void print(const String &s)
    {
      for (int i = 0; i < (int)s.length(); i++) {
        write(s[i]);
      }
    }
    
    FORCE_INLINE void print(const char *str)
    {
      write(str);
    }
    void print(char, int = BYTE);
    void print(unsigned char, int = BYTE);
    void print(int, int = DEC);
    void print(unsigned int, int = DEC);
    void print(long, int = DEC);
    void print(unsigned long, int = DEC);
    void print(double, int = 2);

    void println(const String &s);
    void println(const char[]);
    void println(char, int = BYTE);
    void println(unsigned char, int = BYTE);
    void println(int, int = DEC);
    void println(unsigned int, int = DEC);
    void println(long, int = DEC);
    void println(unsigned long, int = DEC);
    void println(double, int = 2);
    void println(void);
};

extern MarlinSerial MSerial;
#endif // !AT90USB


// begin MarlinSerial.cpp
#ifndef AT90USB
// this next line disables the entire HardwareSerial.cpp, 
// this is so I can support Attiny series and any other chip without a uart
#if defined(UBRRH) || defined(UBRR0H) || defined(UBRR1H) || defined(UBRR2H) || defined(UBRR3H)

#if UART_PRESENT(SERIAL_PORT)
  ring_buffer rx_buffer  =  { { 0 }, 0, 0 };
#endif

FORCE_INLINE void store_char(unsigned char c)
{
  int i = (unsigned int)(rx_buffer.head + 1) % RX_BUFFER_SIZE;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if (i != rx_buffer.tail) {
    rx_buffer.buffer[rx_buffer.head] = c;
    rx_buffer.head = i;
  }
}


//#elif defined(SIG_USART_RECV)
#if defined(M_USARTx_RX_vect)
  // fixed by Mark Sproul this is on the 644/644p
  //SIGNAL(SIG_USART_RECV)
  SIGNAL(M_USARTx_RX_vect)
  {
    unsigned char c  =  M_UDRx;
    store_char(c);
  }
#endif

// Constructors ////////////////////////////////////////////////////////////////

MarlinSerial::MarlinSerial()
{

}

// Public Methods //////////////////////////////////////////////////////////////

void MarlinSerial::begin(long baud)
{
  uint16_t baud_setting;
  bool useU2X = true;

#if F_CPU == 16000000UL && SERIAL_PORT == 0
  // hardcoded exception for compatibility with the bootloader shipped
  // with the Duemilanove and previous boards and the firmware on the 8U2
  // on the Uno and Mega 2560.
  if (baud == 57600) {
    useU2X = false;
  }
#endif
  
  if (useU2X) {
    M_UCSRxA = 1 << M_U2Xx;
    baud_setting = (F_CPU / 4 / baud - 1) / 2;
  } else {
    M_UCSRxA = 0;
    baud_setting = (F_CPU / 8 / baud - 1) / 2;
  }

  // assign the baud_setting, a.k.a. ubbr (USART Baud Rate Register)
  M_UBRRxH = baud_setting >> 8;
  M_UBRRxL = baud_setting;

  sbi(M_UCSRxB, M_RXENx);
  sbi(M_UCSRxB, M_TXENx);
  sbi(M_UCSRxB, M_RXCIEx);
}

void MarlinSerial::end()
{
  cbi(M_UCSRxB, M_RXENx);
  cbi(M_UCSRxB, M_TXENx);
  cbi(M_UCSRxB, M_RXCIEx);  
}



int MarlinSerial::peek(void)
{
  if (rx_buffer.head == rx_buffer.tail) {
    return -1;
  } else {
    return rx_buffer.buffer[rx_buffer.tail];
  }
}

int MarlinSerial::read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (rx_buffer.head == rx_buffer.tail) {
    return -1;
  } else {
    unsigned char c = rx_buffer.buffer[rx_buffer.tail];
    rx_buffer.tail = (unsigned int)(rx_buffer.tail + 1) % RX_BUFFER_SIZE;
    return c;
  }
}

void MarlinSerial::flush()
{
  // don't reverse this or there may be problems if the RX interrupt
  // occurs after reading the value of rx_buffer_head but before writing
  // the value to rx_buffer_tail; the previous value of rx_buffer_head
  // may be written to rx_buffer_tail, making it appear as if the buffer
  // don't reverse this or there may be problems if the RX interrupt
  // occurs after reading the value of rx_buffer_head but before writing
  // the value to rx_buffer_tail; the previous value of rx_buffer_head
  // may be written to rx_buffer_tail, making it appear as if the buffer
  // were full, not empty.
  rx_buffer.head = rx_buffer.tail;
}




/// imports from print.h




void MarlinSerial::print(char c, int base)
{
  print((long) c, base);
}

void MarlinSerial::print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

void MarlinSerial::print(int n, int base)
{
  print((long) n, base);
}

void MarlinSerial::print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}

void MarlinSerial::print(long n, int base)
{
  if (base == 0) {
    write(n);
  } else if (base == 10) {
    if (n < 0) {
      print('-');
      n = -n;
    }
    printNumber(n, 10);
  } else {
    printNumber(n, base);
  }
}

void MarlinSerial::print(unsigned long n, int base)
{
  if (base == 0) write(n);
  else printNumber(n, base);
}

void MarlinSerial::print(double n, int digits)
{
  printFloat(n, digits);
}

void MarlinSerial::println(void)
{
  print('\r');
  print('\n');  
}

void MarlinSerial::println(const String &s)
{
  print(s);
  println();
}

void MarlinSerial::println(const char c[])
{
  print(c);
  println();
}

void MarlinSerial::println(char c, int base)
{
  print(c, base);
  println();
}

void MarlinSerial::println(unsigned char b, int base)
{
  print(b, base);
  println();
}

void MarlinSerial::println(int n, int base)
{
  print(n, base);
  println();
}

void MarlinSerial::println(unsigned int n, int base)
{
  print(n, base);
  println();
}

void MarlinSerial::println(long n, int base)
{
  print(n, base);
  println();
}

void MarlinSerial::println(unsigned long n, int base)
{
  print(n, base);
  println();
}

void MarlinSerial::println(double n, int digits)
{
  print(n, digits);
  println();
}

// Private Methods /////////////////////////////////////////////////////////////

void MarlinSerial::printNumber(unsigned long n, uint8_t base)
{
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars. 
  unsigned long i = 0;

  if (n == 0) {
    print('0');
    return;
  } 

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}

void MarlinSerial::printFloat(double number, uint8_t digits) 
{ 
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint; 
  } 
}
// Preinstantiate Objects //////////////////////////////////////////////////////


MarlinSerial MSerial;
#endif // !AT90USB

#endif // DRIVER_ATTINY_H
