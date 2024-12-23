#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t memory[MEMORY_SIZE];

// Reseta a CPU para o estado inicial
void cpu_reset(CPU *cpu) {
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;
    cpu->sp = 0xFD; // Valor inicial padrão
    cpu->status = 0x34; // Flags padrão

    // O vetor de RESET (0xFFFC) contém o endereço inicial do PC
    cpu->pc = memory[0xFFFC] | (memory[0xFFFD] << 8);
}

// Carrega a ROM na memória
void cpu_load_rom(CPU *cpu, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Erro ao abrir ROM: %s\n", filename);
        exit(1);
    }

    fread(&memory[0xF000], 1, 0x1000, file); // Carrega a ROM no espaço 0xF000-0xFFFF
    fclose(file);

    // Inicializa a CPU
    cpu_reset(cpu);
}

// Simula um ciclo da CPU (execução de uma instrução)
void cpu_step(CPU *cpu) {
    uint8_t opcode = memory[cpu->pc++]; // Busca a instrução atual
    printf("Interpretando instrução:0x%02X .\n", opcode);
    
    switch (opcode) {
            
        case 0xA5: // LDA (Load Accumulator - Zero Page)
            cpu->a = memory[memory[cpu->pc++]];
            break;

        case 0xAA: // TAX (Transfer Accumulator to X)
            cpu->x = cpu->a;
            break;

        case 0xE8: // INX (Increment X Register)
            cpu->x++;
            break;

        case 0xC8: // INY (Increment Y Register)
            cpu->y++;
            break;

        case 0xCA: // DEX (Decrement X Register)
            cpu->x--;
            break;

        case 0x88: // DEY (Decrement Y Register)
            cpu->y--;
            break;

        case 0xD8: // CLD (Clear Decimal Flag)
            cpu->status &= ~(1 << 3); // Limpa o flag decimal (bit 3)
            break;

        case 0x78: // SEI (Set Interrupt Disable Flag)
            cpu->status |= (1 << 2); // Define o flag de desabilitar interrupção (bit 2)
            break;

        case 0xA2: // LDX (Load X Register - Imediato)
            cpu->x = memory[cpu->pc++]; // Carrega valor imediato para o registrador X
            break;

        case 0xA0: // LDY (Load Y Register - Imediato)
            cpu->y = memory[cpu->pc++];
            break;

        case 0x9A: // TXS (Transfer X to Stack Pointer)
            cpu->sp = cpu->x; // Transfere o valor de X para o ponteiro de pilha
            break;

        case 0x8A: // TXA (Transfer X to Accumulator)
            cpu->a = cpu->x; // Transfere o valor de X para o acumulador
            break;

        case 0x95: // STA (Store Accumulator - Zero Page,X)
            memory[(memory[cpu->pc++] + cpu->x) & 0xFF] = cpu->a; // Armazena o acumulador na memória (endereço zero page + X)
            break;

        case 0xD0: // BNE (Branch if Not Equal)
            if (!(cpu->status & 0x02)) { // Verifica se o flag Z (Zero) está limpo
                int8_t offset = (int8_t)memory[cpu->pc++];
                cpu->pc += offset; // Salta para o novo endereço
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;

        case 0x00: // BRK (Break - Interrupção)
            printf("Interrupção BRK chamada.\n");
            exit(0);
            break;        

        default:
            printf("Opcode desconhecido: 0x%02X\n", opcode);
            exit(1);
    }
}
