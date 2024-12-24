// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.

#include "riot.h"
#include <stdio.h>
#include <string.h>

// Inicializa o RIOT
void riot_init(RIOT *riot) {
    memset(riot->ram, 0, sizeof(riot->ram));  // Limpa a RAM
    riot->timer = 0;                          // Zera o temporizador
    riot->io_port_a = 0xFF;                    // Define portas para entrada
    riot->io_port_b = 0xFF;
    riot->timer_underflow = false;
}

// Escreve no RIOT (RAM, portas ou temporizador)
void riot_write(RIOT *riot, uint16_t address, uint8_t value) {
    if (address < RIOT_RAM_SIZE) {
        // Escrita na RAM
        riot->ram[address] = value;
    } else if (address == 0x280) {
        // Escreve no temporizador
        riot->timer = value;
        riot->timer_underflow = false; // Reseta o flag de estouro
    } else if (address == 0x281) {
        // Escreve na porta A
        riot->io_port_a = value;
    } else if (address == 0x282) {
        // Escreve na porta B
        riot->io_port_b = value;
    } else {
        printf("Endereço inválido para escrita no RIOT: 0x%04X\n", address);
    }
}

// Lê do RIOT (RAM, portas ou temporizador)
uint8_t riot_read(RIOT *riot, uint16_t address) {
    if (address < RIOT_RAM_SIZE) {
        // Leitura da RAM
        return riot->ram[address];
    } else if (address == 0x280) {
        // Lê o temporizador
        return riot->timer;
    } else if (address == 0x281) {
        // Lê a porta A
        return riot->io_port_a;
    } else if (address == 0x282) {
        // Lê a porta B
        return riot->io_port_b;
    } else {
        printf("Endereço inválido para leitura no RIOT: 0x%04X\n", address);
        return 0;
    }
}

// Atualiza o temporizador a cada ciclo
void riot_tick(RIOT *riot) {
    if (riot->timer > 0) {
        riot->timer--;
    } else {
        riot->timer_underflow = true; // Define o flag de estouro
    }
}
