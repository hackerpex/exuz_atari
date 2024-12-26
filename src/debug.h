#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include <stdio.h>
#include "cpu.h"

int cpu_delay = 16; // Velocidade de execução (16 = 1 instrução por frame)

void init_debug();
void update_debug(CPU *cpu,uint8_t *memory);

#endif // DEBUG_H