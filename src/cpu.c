#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tia.h"
#include "riot.h"

uint8_t memory[MEMORY_SIZE];


FILE *log_file;
// Função para inicializar o log
void init_cpu_log() {
    log_file = fopen("cpu.log", "w");
    if (!log_file) {
        fprintf(stderr, "Erro ao abrir ROM: %s\n", "cpu.log");
        exit(1);
    }
   

}


// Função para registrar informações no log
void log_operation(uint8_t opcode, CPU *cpu) {
    fprintf(log_file, "Opcode: 0x%02X | A: 0x%02X | X: 0x%02X | Y: 0x%02X | PC: 0x%04X | SP: 0x%02X | Status: 0x%02X\n",
            opcode, cpu->a, cpu->x, cpu->y, cpu->pc, cpu->sp, cpu->status);
    fflush(log_file); // Garante que os dados sejam gravados imediatamente
}
void log_message(const char *message) {
    fprintf(log_file, "Message: %s\n",message);            
    fflush(log_file); // Garante que os dados sejam gravados imediatamente
}

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
    uint8_t opcode = memory[cpu->pc]; // Busca a instrução atual
    // printf("Interpretando instrução:0x%02X .\n", opcode);
    log_operation(opcode, cpu);

    cpu->pc++; // Avança para a próxima instrução
    switch (opcode) {

         case 0xA9: // LDA (Load Accumulator - Imediato)
            cpu->a = memory[cpu->pc++]; // Carrega o valor imediato no acumulador
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
            break;
            
        case 0xA5: // LDA (Load Accumulator - Zero Page)
        {
            uint8_t addr = memory[cpu->pc++]; // Lê o endereço na página zero
            cpu->a = memory[addr];            // Carrega o valor no acumulador
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
        }
        break;

        case 0xAA: // TAX (Transfer Accumulator to X)
            cpu->x = cpu->a;
            break;

        case 0xE8: // INX
            cpu->x++;
            cpu->status = (cpu->x == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->x & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0xC8: // INY (Increment Y Register)
            cpu->y++;
            cpu->status = (cpu->y == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->y & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0xCA: // DEX (Decrement X Register)
            cpu->x = (uint8_t)(cpu->x - 1); // Garante wrap-around
            cpu->status = (cpu->x == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->x & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0x88: // DEY (Decrement Y Register)
            cpu->y = (uint8_t)(cpu->y - 1); // Garante wrap-around
            cpu->status = (cpu->y == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->y & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0xD8: // CLD (Clear Decimal Flag)
            cpu->status &= ~(1 << 3); // Limpa o flag decimal (bit 3)
            break;

        case 0x78: // SEI (Set Interrupt Disable Flag)
            cpu->status |= (1 << 2); // Define o flag de desabilitar interrupção (bit 2)
            break;
        
        case 0x0A: // ASL (Arithmetic Shift Left - Acumulador)
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o flag C (Carry)
            cpu->a <<= 1; // Desloca o acumulador 1 bit para a esquerda
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
            break;

        case 0xA2: // LDX (Load X Register - Imediato)
            cpu->x = memory[cpu->pc++]; // Carrega valor imediato para o registrador X
            cpu->status = (cpu->x == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->x & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0xA0: // LDY (Load Y Register - Imediato)
            cpu->y = memory[cpu->pc++]; // Carrega valor imediato para o registrador Y
            cpu->status = (cpu->y == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->y & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0x9A: // TXS (Transfer X to Stack Pointer)
            cpu->sp = cpu->x; // Transfere o valor de X para o ponteiro de pilha
            break;

        case 0x8A: // TXA (Transfer X to Accumulator)
            cpu->a = cpu->x; // Transfere o valor de X para o acumulador
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;

        case 0x85: // STA (Store Accumulator - Zero Page)
            memory[memory[cpu->pc++]] = cpu->a; // Armazena o valor do acumulador em um endereço de zero page
            break;

        case 0x86: // STX (Store X Register - Zero Page)
            memory[memory[cpu->pc++]] = cpu->x; // Armazena o valor do registrador X em um endereço de zero page
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

        case 0x4C: // JMP (Jump to Address)
            cpu->pc = memory[cpu->pc] | (memory[cpu->pc + 1] << 8); // Salta para o endereço especificado
            break;
        
        case 0x20: // JSR (Jump to Subroutine)
        {
            
            cpu->sp--;
            memory[0x0100 + cpu->sp] = ((cpu->pc + 1) >> 8) & 0xFF; // Byte alto
            cpu->sp--;
            memory[0x0100 + cpu->sp] = (cpu->pc + 1) & 0xFF; // Byte baixo


            uint16_t originalAddress = cpu->pc + 1;

            uint16_t addr = memory[cpu->pc] | (memory[cpu->pc + 1] << 8); // Novo endereço para saltar
            cpu->pc = addr;
            char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
            sprintf(messageBuffer, "JSR: Salto para 0x%04X, endereço salvo: 0x%04X", addr, originalAddress);
            log_message(messageBuffer);
            }
            break;
        case 0x60: // RTS (Return from Subroutine)
        {
            // Recupera o endereço salvo na pilha
            uint16_t low = memory[0x0100 + cpu->sp++]; // Byte baixo
            uint16_t high = memory[0x0100 + cpu->sp++]; // Byte alto
            
            uint16_t addr = ((high << 8) | low) + 1; // Corrige o endereço (+1 para próxima instrução)
            cpu->pc = addr; // Salta para o endereço

            char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
            sprintf(messageBuffer, "JSR: Salto para 0x%04X", addr);
            log_message(messageBuffer);

        }
            break;        

        case 0x38: // SEC (Set Carry Flag)
            cpu->status |= 0x01; // Define o flag C (Carry)
            break;     
        
        case 0xE9: // SBC (Subtract with Borrow - Imediato)
            {
                uint8_t value = memory[cpu->pc++]; // Obtém o valor imediato
                uint16_t temp = cpu->a - value - ((cpu->status & 0x01) ? 0 : 1); // Subtração com carry invertido
                cpu->status = (temp > 0xFF) ? (cpu->status & ~0x01) : (cpu->status | 0x01); // Atualiza o flag C (Carry)
                cpu->status = ((temp & 0xFF) == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
                cpu->status = (temp & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
                cpu->a = temp & 0xFF; // Armazena o resultado no acumulador
            }
            break;
        case 0x29: // AND (Logical AND - Imediato)
            cpu->a &= memory[cpu->pc++]; // Faz operação lógica AND entre o acumulador e o valor imediato
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
            break;
        case 0x18: // CLC (Clear Carry Flag)
            cpu->status &= ~0x01; // Limpa o flag C (Carry)
            break;
        case 0x69: // ADC (Add with Carry - Imediato)
            {
                uint8_t value = memory[cpu->pc++]; // Obtém o valor imediato
                uint16_t temp = cpu->a + value + ((cpu->status & 0x01) ? 1 : 0); // Soma com carry
                cpu->status = (temp > 0xFF) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o flag C (Carry)
                cpu->status = ((temp & 0xFF) == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
                cpu->status = (temp & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
                cpu->a = temp & 0xFF; // Armazena o resultado no acumulador
            }
            break;        
        case 0x10: // BPL (Branch if Positive)
            if (!(cpu->status & 0x80)) { // Verifica se o flag N (Negativo) está limpo
                int8_t offset = (int8_t)memory[cpu->pc++]; // Lê o deslocamento como valor assinado
                cpu->pc += offset; // Salta para o novo endereço
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;     
        case 0x09: // ORA (Logical Inclusive OR - Imediato)
            cpu->a |= memory[cpu->pc++]; // Faz operação lógica OR entre o acumulador e o valor imediato
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
            break;
        case 0x94: // STY (Store Y Register - Zero Page,X)
            memory[(memory[cpu->pc++] + cpu->x) & 0xFF] = cpu->y; // Armazena o valor do registrador Y em um endereço de zero page com deslocamento X
            break;

        case 0xB4: // LDY (Load Y Register - Zero Page,X)
            cpu->y = memory[(memory[cpu->pc++] + cpu->x) & 0xFF]; // Carrega o valor de zero page + X no registrador Y
            cpu->status = (cpu->y == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->y & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;
       case 0x4A: // LSR (Logical Shift Right - Acumulador)
            cpu->status = (cpu->a & 0x01) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o flag C (Carry)
            cpu->a >>= 1; // Desloca o acumulador 1 bit para a direita
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza o flag Z (Zero)
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza o flag N (Negativo)
            break;            
        case 0xA8: // TAY (Transfer Accumulator to Y)
            cpu->y = cpu->a; // Transfere o valor do acumulador para o registrador Y
            cpu->status = (cpu->y == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->y & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;
        case 0xBD: // LDA (Load Accumulator - Absolute,X)
            {
                uint16_t addr = (memory[cpu->pc++] | (memory[cpu->pc++] << 8)) + cpu->x; // Calcula o endereço absoluto com deslocamento X
                cpu->a = memory[addr]; // Carrega o valor no acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;  
        case 0x2A: // ROL (Rotate Left - Acumulador)
            {
                uint8_t carry = (cpu->status & 0x01); // Salva o estado atual do carry
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o carry com o bit 7
                cpu->a = (cpu->a << 1) | carry; // Rotaciona o acumulador e adiciona o carry no bit 0
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;   
        case 0x98: // TYA (Transfer Y to Accumulator)
            cpu->a = cpu->y; // Transfere o valor do registrador Y para o acumulador
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;    
        case 0xA6: // LDX (Load X Register - Zero Page)
            cpu->x = memory[memory[cpu->pc++]]; // Carrega o valor de zero page para o registrador X
            cpu->status = (cpu->x == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->x & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;   
        case 0xE6: // INC (Increment Memory - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                memory[addr]++; // Incrementa o valor na memória
                cpu->status = (memory[addr] == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (memory[addr] & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;   
        case 0x2D: // AND (Logical AND - Absolute)
            {

                uint16_t v1 = memory[cpu->pc++]; // Obtém o endereço absoluto
                
                uint16_t v2 = memory[cpu->pc++];// Obtém o endereço absoluto
                
                uint16_t addr = v1 | v2; // Obtém o endereço absoluto
                
                uint16_t operando = memory[addr];
                cpu->a &= operando; // Aplica operação lógica AND com o acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N

                char messageBuffer[128]; // Cria um buffer para armazenar a string formatada
                sprintf(messageBuffer, "OUTRO addr:0x%04X , operando:0x%04X a:0x%04X status:0x%02X, pc:0x%04X, v1:0x%04X, v2:0x%04X", addr, operando,cpu->a,cpu->status,cpu->pc,v1,v2);
                log_message(messageBuffer);


            }
            break;   
        case 0xF0: // BEQ (Branch if Equal)
            if (cpu->status & 0x02) { // Verifica o flag Z (Zero)
                int8_t offset = (int8_t)memory[cpu->pc++]; // Obtém o deslocamento com sinal
                cpu->pc += offset; // Aplica o deslocamento
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;   
        case 0x49: // EOR (Exclusive OR - Imediato)
            cpu->a ^= memory[cpu->pc++]; // Aplica operação XOR entre o acumulador e o operando imediato
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;   
        case 0x8D: // STA (Store Accumulator - Absolute)
            {
                uint16_t addr = memory[cpu->pc++] | (memory[cpu->pc++] << 8); // Obtém o endereço absoluto
                memory[addr] = cpu->a; // Armazena o valor do acumulador na memória
            }
            break;     
        case 0xE0: // CPX (Compare X Register - Imediato)
            {
                uint8_t value = memory[cpu->pc++]; // Obtém o valor imediato
                uint8_t result = cpu->x - value; // Subtrai o valor do registrador X
                cpu->status = (result == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (result & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
                cpu->status = (cpu->x >= value) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza C
            }
            break;     
        case 0x84: // STY (Store Y Register - Zero Page)
            memory[memory[cpu->pc++]] = cpu->y; // Armazena o valor do registrador Y em um endereço de zero page
            break;   
        case 0x25: // AND (Logical AND - Zero Page)
            cpu->a &= memory[memory[cpu->pc++]]; // Aplica operação lógica AND com o acumulador e o endereço de zero page
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;  
       case 0x30: // BMI (Branch if Minus)
            if (cpu->status & 0x80) { // Verifica se o flag N (Negative) está definido
                int8_t offset = (int8_t)memory[cpu->pc++]; // Obtém o deslocamento com sinal
                cpu->pc += offset; // Aplica o deslocamento
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;      
       case 0x05: // ORA (Logical Inclusive OR - Zero Page)
            cpu->a |= memory[memory[cpu->pc++]]; // Aplica operação lógica OR com o acumulador e o endereço de zero page
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;   
        case 0xB5: // LDA (Load Accumulator - Zero Page,X)
            cpu->a = memory[(memory[cpu->pc++] + cpu->x) & 0xFF]; // Carrega o valor de zero page + X no acumulador
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;     
       case 0x08: // PHP (Push Processor Status)
            memory[0x0100 + cpu->sp--] = cpu->status | 0x10; // Empurra o registrador de status na pilha com o bit 4 definido
            break;   
        case 0x28: // PLP (Pull Processor Status)
            cpu->status = memory[0x0100 + ++cpu->sp]; // Puxa o registrador de status da pilha
            cpu->status |= 0x20; // Garante que o bit 5 esteja sempre definido
            break;   
        case 0x90: // BCC (Branch if Carry Clear)
            if (!(cpu->status & 0x01)) { // Verifica se o flag C (Carry) está limpo
                int8_t offset = (int8_t)memory[cpu->pc++]; // Obtém o deslocamento com sinal
                cpu->pc += offset; // Aplica o deslocamento
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;  
        case 0x66: // ROR (Rotate Right - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                uint8_t value = memory[addr];
                uint8_t carry = (cpu->status & 0x01) << 7; // Salva o carry como bit mais significativo
                cpu->status = (value & 0x01) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o carry
                value = (value >> 1) | carry; // Rotaciona para a direita
                memory[addr] = value; // Atualiza o valor na memória
                cpu->status = (value == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (value & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;     
        case 0x26: // ROL (Rotate Left - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                uint8_t value = memory[addr];
                uint8_t carry = (cpu->status & 0x01); // Obtém o carry atual
                cpu->status = (value & 0x80) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o carry com o bit 7
                value = (value << 1) | carry; // Rotaciona para a esquerda
                memory[addr] = value; // Atualiza o valor na memória
                cpu->status = (value == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (value & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;     
        case 0xB1: // LDA (Load Accumulator - Indirect,Y)
            {
                uint16_t addr = memory[memory[cpu->pc++]] | (memory[memory[cpu->pc] + 1] << 8); // Obtém o endereço indireto
                addr += cpu->y; // Aplica o deslocamento Y
                cpu->a = memory[addr]; // Carrega o valor no acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;   
        case 0x45: // EOR (Exclusive OR - Zero Page)
            cpu->a ^= memory[memory[cpu->pc++]]; // Aplica operação XOR entre o acumulador e o endereço de zero page
            cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
            cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            break;  
        case 0xEA: // NOP (No Operation)
            // Nenhuma operação é realizada, apenas avança para a próxima instrução
            break; 
        case 0x75: // ADC (Add with Carry - Zero Page,X)
            {
                uint8_t addr = (memory[cpu->pc++] + cpu->x) & 0xFF; // Endereço na página zero com deslocamento X
                uint16_t sum = cpu->a + memory[addr] + (cpu->status & 0x01); // Soma incluindo o carry
                cpu->status = (sum > 0xFF) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o Carry
                cpu->a = (uint8_t)sum; // Armazena o resultado
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0xB0: // BCS (Branch if Carry Set)
            if (cpu->status & 0x01) { // Verifica se o flag C (Carry) está definido
                int8_t offset = (int8_t)memory[cpu->pc++]; // Obtém o deslocamento com sinal
                cpu->pc += offset; // Aplica o deslocamento
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;         
        case 0xAD: // LDA (Load Accumulator - Absolute)
            {
                uint16_t addr = memory[cpu->pc++] | (memory[cpu->pc++] << 8); // Obtém o endereço absoluto
                cpu->a = memory[addr]; // Carrega o valor no acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0xE4: // CPX (Compare X Register - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                uint8_t value = memory[addr]; // Lê o valor na memória
                uint8_t result = cpu->x - value; // Subtrai o valor de X
                cpu->status = (result == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (result & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
                cpu->status = (cpu->x >= value) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza C
            }
            break;   
        case 0xA4: // LDY (Load Y Register - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                cpu->y = memory[addr]; // Carrega o valor no registrador Y
                cpu->status = (cpu->y == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->y & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0xC0: // CPY (Compare Y Register - Imediato)
            {
                uint8_t value = memory[cpu->pc++]; // Obtém o valor imediato
                uint8_t result = cpu->y - value; // Subtrai o valor do registrador Y
                cpu->status = (result == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (result & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
                cpu->status = (cpu->y >= value) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza C
            }
            break;
        case 0xB9: // LDA (Load Accumulator - Absolute,Y)
            {
                uint16_t addr = (memory[cpu->pc++] | (memory[cpu->pc++] << 8)) + cpu->y; // Calcula o endereço absoluto com deslocamento Y
                cpu->a = memory[addr]; // Carrega o valor no acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0xC9: // CMP (Compare Accumulator - Imediato)
            {
                uint8_t value = memory[cpu->pc++]; // Obtém o valor imediato
                uint8_t result = cpu->a - value; // Subtrai o valor do acumulador
                cpu->status = (result == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (result & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
                cpu->status = (cpu->a >= value) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza C
            }
            break;            
        case 0x39: // AND (Logical AND - Absolute,Y)
            {
                uint16_t addr = (memory[cpu->pc++] | (memory[cpu->pc++] << 8)) + cpu->y; // Calcula o endereço absoluto com deslocamento Y
                cpu->a &= memory[addr]; // Aplica operação lógica AND com o acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0xC6: // DEC (Decrement Memory - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                memory[addr]--; // Decrementa o valor na memória
                cpu->status = (memory[addr] == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (memory[addr] & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0x99: // STA (Store Accumulator - Absolute,Y)
            {
                uint16_t addr = (memory[cpu->pc++] | (memory[cpu->pc++] << 8)) + cpu->y; // Calcula o endereço absoluto com deslocamento Y
                memory[addr] = cpu->a; // Armazena o valor do acumulador no endereço calculado
            }
            break;
        case 0xF6: // INC (Increment Memory - Zero Page,X)
            {
                uint8_t addr = (memory[cpu->pc++] + cpu->x) & 0xFF; // Calcula o endereço na página zero com deslocamento X
                memory[addr]++; // Incrementa o valor na memória
                cpu->status = (memory[addr] == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (memory[addr] & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
       case 0x07: // SLO (Shift Left and OR with Accumulator - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                uint8_t value = memory[addr];
                cpu->status = (value & 0x80) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza o Carry
                value <<= 1; // Desloca o valor para a esquerda
                memory[addr] = value; // Atualiza o valor na memória
                cpu->a |= value; // OR lógico com o acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;
        case 0x04: // NOP (No Operation - Zero Page)
            cpu->pc++; // Avança para a próxima instrução (ignora o operando de zero page)
            break;
        case 0x40: // RTI (Return from Interrupt)
            {
                cpu->status = memory[0x0100 + ++cpu->sp]; // Restaura o status da pilha
                uint16_t low = memory[0x0100 + ++cpu->sp]; // Recupera o byte baixo do endereço da pilha
                uint16_t high = memory[0x0100 + ++cpu->sp]; // Recupera o byte alto
                cpu->pc = (high << 8) | low; // Reconstrói o endereço
            }
            break;
        case 0xF9: // SBC (Subtract with Carry - Absolute,Y)
            {
                uint16_t addr = (memory[cpu->pc++] | (memory[cpu->pc++] << 8)) + cpu->y; // Calcula o endereço absoluto com deslocamento Y
                uint8_t value = memory[addr] ^ 0xFF; // Complementa o valor (para subtração)
                uint16_t result = cpu->a + value + (cpu->status & 0x01); // Soma o complemento e o carry
                cpu->status = (result > 0xFF) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza C
                cpu->a = result & 0xFF; // Atualiza o acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;     
        case 0x6A: // ROR (Rotate Right - Acumulador)
            {
                uint8_t carry = cpu->status & 0x01; // Armazena o carry atual
                uint8_t result = (cpu->a >> 1) | (carry << 7); // Rotaciona para a direita
                cpu->status = (cpu->a & 0x01) ? (cpu->status | 0x01) : (cpu->status & ~0x01); // Atualiza C
                cpu->a = result; // Atualiza o acumulador
                cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
                cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
            }
            break;    
        case 0x24: // BIT (Bit Test - Zero Page)
            {
                uint8_t addr = memory[cpu->pc++]; // Obtém o endereço de zero page
                uint8_t value = memory[addr]; // Lê o valor na memória
                cpu->status = (value & cpu->a) ? (cpu->status & ~0x02) : (cpu->status | 0x02); // Atualiza Z
                cpu->status = (value & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
                cpu->status = (value & 0x40) ? (cpu->status | 0x40) : (cpu->status & ~0x40); // Atualiza V
            }
            break;
        case 0x50: // BVC (Branch if Overflow Clear)
            if (!(cpu->status & 0x40)) { // Verifica se o flag V (Overflow) está limpo
                int8_t offset = (int8_t)memory[cpu->pc++]; // Obtém o deslocamento com sinal
                cpu->pc += offset; // Aplica o deslocamento
            } else {
                cpu->pc++; // Avança para a próxima instrução
            }
            break;                                  
        // case 0x01: // ORA (Logical Inclusive OR - Indirect,X)
        //     {
        //         uint8_t zp_addr = (memory[cpu->pc++] + cpu->x) & 0xFF; // Endereço zero page com deslocamento X
        //         uint16_t addr = memory[zp_addr] | (memory[(zp_addr + 1) & 0xFF] << 8); // Endereço indireto
        //         cpu->a |= memory[addr]; // Operação lógica OR com o acumulador
        //         cpu->status = (cpu->a == 0) ? (cpu->status | 0x02) : (cpu->status & ~0x02); // Atualiza Z
        //         cpu->status = (cpu->a & 0x80) ? (cpu->status | 0x80) : (cpu->status & ~0x80); // Atualiza N
        //     }
        //     break;                 

       case 0x00: // BRK (Break - Interrupção)
            printf("Interrupção BRK chamada.\n");
            exit(0);
            break;                                                                                                                                                                                                                      
        default:
            printf("Opcode desconhecido: 0x%02X\n", opcode);
            exit(1);
    }
   
}
