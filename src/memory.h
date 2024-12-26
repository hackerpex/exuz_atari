#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 0x10000 // 64 KB (MOS 6502, mas o 6507 usa menos)
extern uint8_t memory[MEMORY_SIZE];

void randomize_memory(); 
#endif // MEMORY_H