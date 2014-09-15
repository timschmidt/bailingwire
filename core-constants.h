#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

#include <avr/pgmspace.h>

/*prog_char      - a signed char (1 byte) -127 to 128
 *prog_uchar     - an unsigned char (1 byte) 0 to 255
 *prog_int16_t   - a signed int (2 bytes) -32,767 to 32,768
 *prog_uint16_t  - an unsigned int (2 bytes) 0 to 65,535
 *prog_int32_t   - a signed long (4 bytes) -2,147,483,648 to * 2,147,483,647.
 *prog_uint32_t  - an unsigned long (4 bytes) 0 to 4,294,967,295
 */

array prog_char[3] PROGMEM = ["a", "b", "c"];
  
#endif // CORE_CONSTANTS_H
