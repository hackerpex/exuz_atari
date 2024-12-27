#ifndef INPUT_H
#define INPUT_H


#include "memory.h" // Para manipular o mapeamento da memória

#include <stdint.h>
#include <stdbool.h>

// Inicialização dos inputs
void input_init();

// Atualiza os inputs
void input_update(bool *is_running, uint8_t *memory);

// Lê o estado de um endereço mapeado
uint8_t input_read(uint16_t addr);

// Escreve em um endereço mapeado (caso necessário)
void input_write(uint16_t addr, uint8_t value);

#endif // INPUT_H
