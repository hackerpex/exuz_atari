#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tia.h"
#include "riot.h"
#include "log.h"





void log_operation(uint8_t opcode, CPU *cpu)
{

    char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
    sprintf(messageBuffer, " PC: 0x%04X | Opcode: 0x%02X | A: 0x%02X | X: 0x%02X | Y: 0x%02X | SP: 0x%02X | Status: 0x%02X\n",
        cpu->pc, opcode, cpu->a, cpu->x, cpu->y, cpu->sp, cpu->ps);
    log_message(1, messageBuffer);
}

// Reseta a CPU para o estado inicial
void cpu_reset(CPU *cpu)
{
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;
    cpu->sp = 0xFD;     // Ponteiro para a pilha na memória (stack)
    cpu->ps = 0x34; // program status

    // O vetor de RESET (0xFFFC) contém o endereço inicial do PC
    cpu->pc = rom[0xFFFC] | (rom[0xFFFD] << 8);
}

// Carrega a ROM na memória
void cpu_load_rom(CPU *cpu, const char *filename)
{

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir ROM: %s\n", filename);
        exit(1);
    }

    fread(&rom[0xF000], 1, 0x1000, file); // Carrega a ROM no espaço 0xF000-0xFFFF
    fclose(file);

    // Inicializa a CPU
    cpu_reset(cpu);
}

// Simula um ciclo da CPU (execução de uma instrução)
void cpu_step(CPU *cpu)
{
    uint8_t opcode = rom[cpu->pc]; // Busca a instrução atual
    // printf("Interpretando instrução:0x%02X .\n", opcode);
    log_operation(opcode, cpu);

    cpu->pc++; // Avança para a próxima instrução
    switch (opcode)
    {

    case 0xA9:                                                                        // LDA (Load Accumulator - Imediato)
        cpu->a = rom[cpu->pc++];                                                   // Carrega o valor imediato no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza o flag Z (Zero)
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza o flag N (Negativo)
        break;

    case 0xA5: // LDA (Load Accumulator - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++];                                             // Lê o endereço na página zero
        cpu->a = rom[addr];                                                        // Carrega o valor no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;

    case 0xAA: // TAX (Transfer Accumulator to X)
        cpu->x = cpu->a;
        break;

    case 0xE8: // INX
        cpu->x++;
        cpu->ps = (cpu->x == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->x & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0xC8: // INY (Increment Y Register)
        cpu->y++;
        cpu->ps = (cpu->y == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->y & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0xCA:                                                                        // DEX (Decrement X Register)
        cpu->x = (uint8_t)(cpu->x - 1);                                               // Garante wrap-around
        cpu->ps = (cpu->x == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->x & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0x88:                                                                        // DEY (Decrement Y Register)
        cpu->y = (uint8_t)(cpu->y - 1);                                               // Garante wrap-around
        cpu->ps = (cpu->y == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->y & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0xD8:                    // CLD (Clear Decimal Flag)
        cpu->ps &= ~(1 << 3); // Limpa o flag decimal (bit 3)
        break;

    case 0x78:                   // SEI (Set Interrupt Disable Flag)
        cpu->ps |= (1 << 2); // Define o flag de desabilitar interrupção (bit 2)
        break;

    case 0x0A:                                                                        // ASL (Arithmetic Shift Left - Acumulador)
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza o flag C (Carry)
        cpu->a <<= 1;                                                                 // Desloca o acumulador 1 bit para a esquerda
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza o flag Z (Zero)
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza o flag N (Negativo)
        break;

    case 0xA2:                                                                        // LDX (Load X Register - Imediato)
        cpu->x = rom[cpu->pc++];                                                   // Carrega valor imediato para o registrador X
        cpu->ps = (cpu->x == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->x & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0xA0:                                                                        // LDY (Load Y Register - Imediato)
        cpu->y = rom[cpu->pc++];                                                   // Carrega valor imediato para o registrador Y
        cpu->ps = (cpu->y == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->y & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0x9A:            // TXS (Transfer X to Stack Pointer)
        cpu->sp = cpu->x; // Transfere o valor de X para o ponteiro de pilha
        break;

    case 0x8A:                                                                        // TXA (Transfer X to Accumulator)
        cpu->a = cpu->x;                                                              // Transfere o valor de X para o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;

    case 0x85:                              // STA (Store Accumulator - Zero Page)
        rom[rom[cpu->pc++]] = cpu->a; // Armazena o valor do acumulador em um endereço de zero page
        break;

    case 0x86:                              // STX (Store X Register - Zero Page)
        rom[rom[cpu->pc++]] = cpu->x; // Armazena o valor do registrador X em um endereço de zero page
        break;

    case 0x95:                                                // STA (Store Accumulator - Zero Page,X)
        rom[(rom[cpu->pc++] + cpu->x) & 0xFF] = cpu->a; // Armazena o acumulador na memória (endereço zero page + X)
        break;

    case 0xD0: // BNE (Branch if Not Equal)
        if (!(cpu->ps & 0x02))
        { // Verifica se o flag Z (Zero) está limpo
            int8_t offset = (int8_t)rom[cpu->pc++];
            cpu->pc += offset; // Salta para o novo endereço
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;

    case 0x4C:                                                  // JMP (Jump to Address)
        cpu->pc = rom[cpu->pc] | (rom[cpu->pc + 1] << 8); // Salta para o endereço especificado
        break;

    case 0x20: // JSR (Jump to Subroutine)
    {

        cpu->sp--;
        rom[0x0100 + cpu->sp] = ((cpu->pc + 1) >> 8) & 0xFF; // Byte alto
        cpu->sp--;
        rom[0x0100 + cpu->sp] = (cpu->pc + 1) & 0xFF; // Byte baixo

        uint16_t originalAddress = cpu->pc + 1;

        uint16_t addr = rom[cpu->pc] | (rom[cpu->pc + 1] << 8); // Novo endereço para saltar
        cpu->pc = addr;
        char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
        sprintf(messageBuffer, "JSR: Salto para 0x%04X, endereço salvo: 0x%04X", addr, originalAddress);
        log_message(1, messageBuffer);
    }
    break;
    case 0x60: // RTS (Return from Subroutine)
    {
        // Recupera o endereço salvo na pilha
        uint16_t low = rom[0x0100 + cpu->sp++];  // Byte baixo
        uint16_t high = rom[0x0100 + cpu->sp++]; // Byte alto

        uint16_t addr = ((high << 8) | low) + 1; // Corrige o endereço (+1 para próxima instrução)
        cpu->pc = addr;                          // Salta para o endereço

        char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
        sprintf(messageBuffer, "JSR: Salto para 0x%04X", addr);
        log_message(1, messageBuffer);
    }
    break;

    case 0x38:               // SEC (Set Carry Flag)
        cpu->ps |= 0x01; // Define o flag C (Carry)
        break;

    case 0xE9: // SBC (Subtract with Borrow - Imediato)
    {
        uint8_t value = rom[cpu->pc++];                                                 // Obtém o valor imediato
        uint16_t temp = cpu->a - value - ((cpu->ps & 0x01) ? 0 : 1);                   // Subtração com carry invertido
        cpu->ps = (temp > 0xFF) ? (cpu->ps & ~0x01) : (cpu->ps | 0x01);        // Atualiza o flag C (Carry)
        cpu->ps = ((temp & 0xFF) == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02); // Atualiza o flag Z (Zero)
        cpu->ps = (temp & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);        // Atualiza o flag N (Negativo)
        cpu->a = temp & 0xFF;                                                              // Armazena o resultado no acumulador
    }
    break;
    case 0x29:                                                                        // AND (Logical AND - Imediato)
        cpu->a &= rom[cpu->pc++];                                                  // Faz operação lógica AND entre o acumulador e o valor imediato
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza o flag Z (Zero)
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza o flag N (Negativo)
        break;
    case 0x18:                // CLC (Clear Carry Flag)
        cpu->ps &= ~0x01; // Limpa o flag C (Carry)
        break;
    case 0x69: // ADC (Add with Carry - Imediato)
    {
        uint8_t value = rom[cpu->pc++];                                                 // Obtém o valor imediato
        uint16_t temp = cpu->a + value + ((cpu->ps & 0x01) ? 1 : 0);                   // Soma com carry
        cpu->ps = (temp > 0xFF) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01);        // Atualiza o flag C (Carry)
        cpu->ps = ((temp & 0xFF) == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02); // Atualiza o flag Z (Zero)
        cpu->ps = (temp & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);        // Atualiza o flag N (Negativo)
        cpu->a = temp & 0xFF;                                                              // Armazena o resultado no acumulador
    }
    break;
    case 0x10: // BPL (Branch if Positive)
        if (!(cpu->ps & 0x80))
        {                                              // Verifica se o flag N (Negativo) está limpo
            int8_t offset = (int8_t)rom[cpu->pc++]; // Lê o deslocamento como valor assinado
            cpu->pc += offset;                         // Salta para o novo endereço
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;
    case 0x09:                                                                        // ORA (Logical Inclusive OR - Imediato)
        cpu->a |= rom[cpu->pc++];                                                  // Faz operação lógica OR entre o acumulador e o valor imediato
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza o flag Z (Zero)
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza o flag N (Negativo)
        break;
    case 0x94:                                                // STY (Store Y Register - Zero Page,X)
        rom[(rom[cpu->pc++] + cpu->x) & 0xFF] = cpu->y; // Armazena o valor do registrador Y em um endereço de zero page com deslocamento X
        break;

    case 0xB4:                                                                        // LDY (Load Y Register - Zero Page,X)
        cpu->y = rom[(rom[cpu->pc++] + cpu->x) & 0xFF];                         // Carrega o valor de zero page + X no registrador Y
        cpu->ps = (cpu->y == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->y & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0x4A:                                                                        // LSR (Logical Shift Right - Acumulador)
        cpu->ps = (cpu->a & 0x01) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza o flag C (Carry)
        cpu->a >>= 1;                                                                 // Desloca o acumulador 1 bit para a direita
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza o flag Z (Zero)
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza o flag N (Negativo)
        break;
    case 0xA8:                                                                        // TAY (Transfer Accumulator to Y)
        cpu->y = cpu->a;                                                              // Transfere o valor do acumulador para o registrador Y
        cpu->ps = (cpu->y == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->y & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0xBD: // LDA (Load Accumulator - Absolute,X)
    {
        uint16_t addr = (rom[cpu->pc++] | (rom[cpu->pc++] << 8)) + cpu->x;      // Calcula o endereço absoluto com deslocamento X
        cpu->a = rom[addr];                                                        // Carrega o valor no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x2A: // ROL (Rotate Left - Acumulador)
    {
        uint8_t carry = (cpu->ps & 0x01);                                         // Salva o estado atual do carry
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza o carry com o bit 7
        cpu->a = (cpu->a << 1) | carry;                                               // Rotaciona o acumulador e adiciona o carry no bit 0
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x98:                                                                        // TYA (Transfer Y to Accumulator)
        cpu->a = cpu->y;                                                              // Transfere o valor do registrador Y para o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0xA6:                                                                        // LDX (Load X Register - Zero Page)
        cpu->x = rom[rom[cpu->pc++]];                                           // Carrega o valor de zero page para o registrador X
        cpu->ps = (cpu->x == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->x & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0xE6: // INC (Increment rom - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++];                                                   // Obtém o endereço de zero page
        rom[addr]++;                                                                     // Incrementa o valor na memória
        cpu->ps = (rom[addr] == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (rom[addr] & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x2D: // AND (Logical AND - Absolute)
    {

        uint16_t v1 = rom[cpu->pc++]; // Obtém o endereço absoluto

        uint16_t v2 = rom[cpu->pc++]; // Obtém o endereço absoluto

        uint16_t addr = v1 | v2; // Obtém o endereço absoluto

        uint16_t operando = rom[addr];
        cpu->a &= operando;                                                           // Aplica operação lógica AND com o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N

        char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
        sprintf(messageBuffer, "OUTRO addr:0x%04X , operando:0x%04X a:0x%04X status:0x%02X, pc:0x%04X, v1:0x%04X, v2:0x%04X", addr, operando, cpu->a, cpu->ps, cpu->pc, v1, v2);
        log_message(1, messageBuffer);
    }
    break;
    case 0xF0: // BEQ (Branch if Equal)
        if (cpu->ps & 0x02)
        {                                              // Verifica o flag Z (Zero)
            int8_t offset = (int8_t)rom[cpu->pc++]; // Obtém o deslocamento com sinal
            cpu->pc += offset;                         // Aplica o deslocamento
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;
    case 0x49:                                                                        // EOR (Exclusive OR - Imediato)
        cpu->a ^= rom[cpu->pc++];                                                  // Aplica operação XOR entre o acumulador e o operando imediato
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0x8D: // STA (Store Accumulator - Absolute)
    {
        uint16_t addr = rom[cpu->pc++] | (rom[cpu->pc++] << 8); // Obtém o endereço absoluto
        rom[addr] = cpu->a;                                        // Armazena o valor do acumulador na memória
    }
    break;
    case 0xE0: // CPX (Compare X Register - Imediato)
    {
        uint8_t value = rom[cpu->pc++];                                              // Obtém o valor imediato
        uint8_t result = cpu->x - value;                                                // Subtrai o valor do registrador X
        cpu->ps = (result == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);     // Atualiza Z
        cpu->ps = (result & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);   // Atualiza N
        cpu->ps = (cpu->x >= value) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza C
    }
    break;
    case 0x84:                              // STY (Store Y Register - Zero Page)
        rom[rom[cpu->pc++]] = cpu->y; // Armazena o valor do registrador Y em um endereço de zero page
        break;
    case 0x25:                                                                        // AND (Logical AND - Zero Page)
        cpu->a &= rom[rom[cpu->pc++]];                                          // Aplica operação lógica AND com o acumulador e o endereço de zero page
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0x30: // BMI (Branch if Minus)
        if (cpu->ps & 0x80)
        {                                              // Verifica se o flag N (Negative) está definido
            int8_t offset = (int8_t)rom[cpu->pc++]; // Obtém o deslocamento com sinal
            cpu->pc += offset;                         // Aplica o deslocamento
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;
    case 0x05:                                                                        // ORA (Logical Inclusive OR - Zero Page)
        cpu->a |= rom[rom[cpu->pc++]];                                          // Aplica operação lógica OR com o acumulador e o endereço de zero page
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0xB5:                                                                        // LDA (Load Accumulator - Zero Page,X)
        cpu->a = rom[(rom[cpu->pc++] + cpu->x) & 0xFF];                         // Carrega o valor de zero page + X no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0x08:                                           // PHP (Push Processor Status)
        rom[0x0100 + cpu->sp--] = cpu->ps | 0x10; // Empurra o registrador de status na pilha com o bit 4 definido
        break;
    case 0x28:                                    // PLP (Pull Processor Status)
        cpu->ps = rom[0x0100 + ++cpu->sp]; // Puxa o registrador de status da pilha
        cpu->ps |= 0x20;                      // Garante que o bit 5 esteja sempre definido
        break;
    case 0x90: // BCC (Branch if Carry Clear)
        if (!(cpu->ps & 0x01))
        {                                              // Verifica se o flag C (Carry) está limpo
            int8_t offset = (int8_t)rom[cpu->pc++]; // Obtém o deslocamento com sinal
            cpu->pc += offset;                         // Aplica o deslocamento
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;
    case 0x66: // ROR (Rotate Right - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++]; // Obtém o endereço de zero page
        uint8_t value = rom[addr];
        uint8_t carry = (cpu->ps & 0x01) << 7;                                   // Salva o carry como bit mais significativo
        cpu->ps = (value & 0x01) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza o carry
        value = (value >> 1) | carry;                                                // Rotaciona para a direita
        rom[addr] = value;                                                        // Atualiza o valor na memória
        cpu->ps = (value == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (value & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x26: // ROL (Rotate Left - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++]; // Obtém o endereço de zero page
        uint8_t value = rom[addr];
        uint8_t carry = (cpu->ps & 0x01);                                        // Obtém o carry atual
        cpu->ps = (value & 0x80) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza o carry com o bit 7
        value = (value << 1) | carry;                                                // Rotaciona para a esquerda
        rom[addr] = value;                                                        // Atualiza o valor na memória
        cpu->ps = (value == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (value & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0xB1: // LDA (Load Accumulator - Indirect,Y)
    {
        uint16_t addr = rom[rom[cpu->pc++]] | (rom[rom[cpu->pc] + 1] << 8); // Obtém o endereço indireto
        addr += cpu->y;                                                                 // Aplica o deslocamento Y
        cpu->a = rom[addr];                                                          // Carrega o valor no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);     // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);   // Atualiza N
    }
    break;
    case 0x45:                                                                        // EOR (Exclusive OR - Zero Page)
        cpu->a ^= rom[rom[cpu->pc++]];                                          // Aplica operação XOR entre o acumulador e o endereço de zero page
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        break;
    case 0xEA: // NOP (No Operation)
        // Nenhuma operação é realizada, apenas avança para a próxima instrução
        break;
    case 0x75: // ADC (Add with Carry - Zero Page,X)
    {
        uint8_t addr = (rom[cpu->pc++] + cpu->x) & 0xFF;                           // Endereço na página zero com deslocamento X
        uint16_t sum = cpu->a + rom[addr] + (cpu->ps & 0x01);                  // Soma incluindo o carry
        cpu->ps = (sum > 0xFF) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01);    // Atualiza o Carry
        cpu->a = (uint8_t)sum;                                                        // Armazena o resultado
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0xB0: // BCS (Branch if Carry Set)
        if (cpu->ps & 0x01)
        {                                              // Verifica se o flag C (Carry) está definido
            int8_t offset = (int8_t)rom[cpu->pc++]; // Obtém o deslocamento com sinal
            cpu->pc += offset;                         // Aplica o deslocamento
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;
    case 0xAD: // LDA (Load Accumulator - Absolute)
    {
        uint16_t addr = rom[cpu->pc++] | (rom[cpu->pc++] << 8);                 // Obtém o endereço absoluto
        cpu->a = rom[addr];                                                        // Carrega o valor no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0xE4: // CPX (Compare X Register - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++];                                               // Obtém o endereço de zero page
        uint8_t value = rom[addr];                                                   // Lê o valor na memória
        uint8_t result = cpu->x - value;                                                // Subtrai o valor de X
        cpu->ps = (result == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);     // Atualiza Z
        cpu->ps = (result & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);   // Atualiza N
        cpu->ps = (cpu->x >= value) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza C
    }
    break;
    case 0xA4: // LDY (Load Y Register - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++];                                             // Obtém o endereço de zero page
        cpu->y = rom[addr];                                                        // Carrega o valor no registrador Y
        cpu->ps = (cpu->y == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->y & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0xC0: // CPY (Compare Y Register - Imediato)
    {
        uint8_t value = rom[cpu->pc++];                                              // Obtém o valor imediato
        uint8_t result = cpu->y - value;                                                // Subtrai o valor do registrador Y
        cpu->ps = (result == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);     // Atualiza Z
        cpu->ps = (result & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);   // Atualiza N
        cpu->ps = (cpu->y >= value) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza C
    }
    break;
    case 0xB9: // LDA (Load Accumulator - Absolute,Y)
    {
        uint16_t addr = (rom[cpu->pc++] | (rom[cpu->pc++] << 8)) + cpu->y;      // Calcula o endereço absoluto com deslocamento Y
        cpu->a = rom[addr];                                                        // Carrega o valor no acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0xC9: // CMP (Compare Accumulator - Imediato)
    {
        uint8_t value = rom[cpu->pc++];                                              // Obtém o valor imediato
        uint8_t result = cpu->a - value;                                                // Subtrai o valor do acumulador
        cpu->ps = (result == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);     // Atualiza Z
        cpu->ps = (result & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);   // Atualiza N
        cpu->ps = (cpu->a >= value) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza C
    }
    break;
    case 0x39: // AND (Logical AND - Absolute,Y)
    {
        uint16_t addr = (rom[cpu->pc++] | (rom[cpu->pc++] << 8)) + cpu->y;      // Calcula o endereço absoluto com deslocamento Y
        cpu->a &= rom[addr];                                                       // Aplica operação lógica AND com o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0xC6: // DEC (Decrement rom - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++];                                                   // Obtém o endereço de zero page
        rom[addr]--;                                                                     // Decrementa o valor na memória
        cpu->ps = (rom[addr] == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (rom[addr] & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x99: // STA (Store Accumulator - Absolute,Y)
    {
        uint16_t addr = (rom[cpu->pc++] | (rom[cpu->pc++] << 8)) + cpu->y; // Calcula o endereço absoluto com deslocamento Y
        rom[addr] = cpu->a;                                                   // Armazena o valor do acumulador no endereço calculado
    }
    break;
    case 0xF6: // INC (Increment rom - Zero Page,X)
    {
        uint8_t addr = (rom[cpu->pc++] + cpu->x) & 0xFF;                                 // Calcula o endereço na página zero com deslocamento X
        rom[addr]++;                                                                     // Incrementa o valor na memória
        cpu->ps = (rom[addr] == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (rom[addr] & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x07: // SLO (Shift Left and OR with Accumulator - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++]; // Obtém o endereço de zero page
        uint8_t value = rom[addr];
        cpu->ps = (value & 0x80) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01);  // Atualiza o Carry
        value <<= 1;                                                                  // Desloca o valor para a esquerda
        rom[addr] = value;                                                         // Atualiza o valor na memória
        cpu->a |= value;                                                              // OR lógico com o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x04:     // NOP (No Operation - Zero Page)
        cpu->pc++; // Avança para a próxima instrução (ignora o operando de zero page)
        break;
    case 0x40: // RTI (Return from Interrupt)
    {
        cpu->ps = rom[0x0100 + ++cpu->sp];   // Restaura o status da pilha
        uint16_t low = rom[0x0100 + ++cpu->sp];  // Recupera o byte baixo do endereço da pilha
        uint16_t high = rom[0x0100 + ++cpu->sp]; // Recupera o byte alto
        cpu->pc = (high << 8) | low;                // Reconstrói o endereço
    }
    break;
    case 0xF9: // SBC (Subtract with Carry - Absolute,Y)
    {
        uint16_t addr = (rom[cpu->pc++] | (rom[cpu->pc++] << 8)) + cpu->y;      // Calcula o endereço absoluto com deslocamento Y
        uint8_t value = rom[addr] ^ 0xFF;                                          // Complementa o valor (para subtração)
        uint16_t result = cpu->a + value + (cpu->ps & 0x01);                      // Soma o complemento e o carry
        cpu->ps = (result > 0xFF) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza C
        cpu->a = result & 0xFF;                                                       // Atualiza o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x6A: // ROR (Rotate Right - Acumulador)
    {
        uint8_t carry = cpu->ps & 0x01;                                           // Armazena o carry atual
        uint8_t result = (cpu->a >> 1) | (carry << 7);                                // Rotaciona para a direita
        cpu->ps = (cpu->a & 0x01) ? (cpu->ps | 0x01) : (cpu->ps & ~0x01); // Atualiza C
        cpu->a = result;                                                              // Atualiza o acumulador
        cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02);   // Atualiza Z
        cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
    }
    break;
    case 0x24: // BIT (Bit Test - Zero Page)
    {
        uint8_t addr = rom[cpu->pc++];                                              // Obtém o endereço de zero page
        uint8_t value = rom[addr];                                                  // Lê o valor na memória
        cpu->ps = (value & cpu->a) ? (cpu->ps & ~0x02) : (cpu->ps | 0x02); // Atualiza Z
        cpu->ps = (value & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80);   // Atualiza N
        cpu->ps = (value & 0x40) ? (cpu->ps | 0x40) : (cpu->ps & ~0x40);   // Atualiza V
    }
    break;
    case 0x50: // BVC (Branch if Overflow Clear)
        if (!(cpu->ps & 0x40))
        {                                              // Verifica se o flag V (Overflow) está limpo
            int8_t offset = (int8_t)rom[cpu->pc++]; // Obtém o deslocamento com sinal
            cpu->pc += offset;                         // Aplica o deslocamento
        }
        else
        {
            cpu->pc++; // Avança para a próxima instrução
        }
        break;
        case 0x2C: // BIT (Absolute)
        {
            // Obtém o endereço absoluto
            uint16_t addr = rom[cpu->pc++] | (rom[cpu->pc++] << 8);

            // Lê o valor da memória no endereço calculado
            uint8_t value = rom[addr];

            // Atualiza as flags:
            cpu->ps = (value & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Flag Negative (N)
            cpu->ps = (value & 0x40) ? (cpu->ps | 0x40) : (cpu->ps & ~0x40); // Flag Overflow (V)
            cpu->ps = (cpu->a & value) ? (cpu->ps & ~0x02) : (cpu->ps | 0x02); // Flag Zero (Z)
        }
        break;        
        case 0x48: // PHA (Push Accumulator)
        {
            rom[0x0100 + cpu->sp--] = cpu->a; // Empilha o valor do acumulador na stack
        }
        break;

        case 0x68: // PLA (Pull Accumulator)
        {
            cpu->a = rom[0x0100 + ++cpu->sp]; // Puxa o valor do acumulador da stack

            // Atualiza as flags Z e N com base no valor carregado
            cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02); // Z flag
            cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // N flag
        }
        break;        
        // case 0x01: // ORA (Logical Inclusive OR - Indirect,X)
        //     {
        //         uint8_t zp_addr = (rom[cpu->pc++] + cpu->x) & 0xFF; // Endereço zero page com deslocamento X
        //         uint16_t addr = rom[zp_addr] | (rom[(zp_addr + 1) & 0xFF] << 8); // Endereço indireto
        //         cpu->a |= rom[addr]; // Operação lógica OR com o acumulador
        //         cpu->ps = (cpu->a == 0) ? (cpu->ps | 0x02) : (cpu->ps & ~0x02); // Atualiza Z
        //         cpu->ps = (cpu->a & 0x80) ? (cpu->ps | 0x80) : (cpu->ps & ~0x80); // Atualiza N
        //     }
        //     break;

    case 0x00: // BRK (Break - Interrupção)
        printf("Interrupção BRK chamada.\n");
        // exit(0);
        break;
    default:
        printf("Opcode desconhecido: 0x%02X\n", opcode);
        // exit(1);
    }
}
