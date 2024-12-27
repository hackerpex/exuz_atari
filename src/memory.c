
#include "memory.h"

#include <stdlib.h> // Para srand() e rand()
#include <time.h>   // Para time()

void randomize_memory( uint8_t * memory) {
    srand((unsigned int)time(NULL)); // Inicializa o gerador de números aleatórios com base no tempo
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = rand() % 256; // Gera valores aleatórios entre 0x00 e 0xFF
    }
}