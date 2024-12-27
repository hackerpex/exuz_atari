#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 0x10000 // 64 KB (MOS 6502, mas o 6507 usa menos)


#define ROM_SIZE 0x10000 // 64 KB (MOS 6502, mas o 6507 usa menos)


void randomize_memory( uint8_t * memory); 
#endif // MEMORY_H