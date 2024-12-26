// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.


#ifndef CPU_H
#define CPU_H


#include "memory.h"
#include <stdint.h>
#include <stdbool.h>

// Registradores da CPU
typedef struct {
    uint8_t a;      // Acumulador
    uint8_t x;      // Registrador X
    uint8_t y;      // Registrador Y
    uint8_t sp;     // Ponteiro de pilha
    uint16_t pc;    // Contador de programa
    uint8_t status; // Registrador de status (flags)
} CPU;

// Memória

// Funções
void init_cpu_log();
void cpu_reset(CPU *cpu);
void cpu_step(CPU *cpu); // Executa uma instrução
void cpu_load_rom(CPU *cpu, const char *filename);

#endif
