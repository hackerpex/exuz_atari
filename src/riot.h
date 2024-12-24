// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.

#ifndef RIOT_H
#define RIOT_H

#include <stdint.h>
#include <stdbool.h>

// Definições para o temporizador
#define RIOT_RAM_SIZE 128
#define TIMER_START 0x0280

// Estrutura para o RIOT
typedef struct {
    uint8_t ram[RIOT_RAM_SIZE];  // RAM de 128 bytes
    uint8_t timer;               // Temporizador de 8 bits
    uint8_t io_port_a;           // Porta de entrada/saída A
    uint8_t io_port_b;           // Porta de entrada/saída B
    bool timer_underflow;        // Indica estouro do temporizador
} RIOT;

// Funções do RIOT
void riot_init(RIOT *riot);
void riot_write(RIOT *riot, uint16_t address, uint8_t value);
uint8_t riot_read(RIOT *riot, uint16_t address);
void riot_tick(RIOT *riot);

#endif // RIOT_H
