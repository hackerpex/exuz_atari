#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_instructions.h"
#include "memory.h"


#define MAX_LABELS 256


typedef struct {
    uint16_t address;
    char label[10];
} Label;

Label labels[MAX_LABELS];
int label_count = 0;

// Função para buscar ou criar labels
const char* get_label(uint16_t address) {
    for (int i = 0; i < label_count; i++) {
        if (labels[i].address == address) {
            return labels[i].label;
        }
    }

    if (label_count < MAX_LABELS) {
        snprintf(labels[label_count].label, sizeof(labels[label_count].label), "L%04X", address);
        labels[label_count].address = address;
        return labels[label_count++].label;
    }

    return "???";
}

// Funções para resolver símbolos
const char* resolve_symbol(uint16_t address, Symbol *symbols, int count) {
    for (int i = 0; i < count; i++) {
        if (symbols[i].address == address) {
            return symbols[i].label;
        }
    }
    return NULL;
}

// Função principal do disassembler
void decompile(uint8_t *rom) {
    
    
    FILE *out = fopen("game.asm", "w");

    if ( !out) {
        perror("Erro ao abrir arquivos");
        exit(1);
    }

  

    uint16_t start = rom[0xFFFC] | (rom[0xFFFD] << 8); // Endereço inicial da loginca do jogo

    uint16_t pc = 0xF000; // Endereço inicial fictício
    
    pc = start; 
    
    while (pc < 0xFFFF) {
        uint8_t opcode = rom[pc];
        Instruction instr = instructions[opcode];

        const char *signalLabel = NULL;
        const char *ioLabel = NULL;

       

        fprintf(out, "%04X  ", pc);
        
        fprintf(out, "%02X ", opcode);
        pc++;

        if (instr.mnemonic) {
            fprintf(out, "%-4s", instr.mnemonic);

            int8_t offset = 0x00;
            uint16_t addr = pc ;
            uint8_t value = 0;
            uint8_t mValue = 0;
            // Operandos (exemplo para imediato e endereçamento absoluto)            
            if (instr.mode == RELATIVE) { // Branch     
                offset = rom[pc++];
                addr = pc + offset;                         
               // fprintf(out, " %s", get_label(addr));
            } else if (instr.mode == IMMEDIATE) { // Imediato
                mValue = rom[pc++];
               
                // fprintf(out, " #$%02X", value);
            }
            else if (instr.mode == ZERO_PAGE_X) { // Imediato
                value = rom[pc];
                fprintf(out, " $%02X", value);
                signalLabel = resolve_symbol(value, signalSymbols, SIGNAL_COUNT);
                ioLabel = resolve_symbol(value, ioSymbols, IO_COUNT);
                // fprintf(out, " #$%02X", value);
            }
             else if (instr.mode == ABSOLUTE) { // Absoluto
                uint16_t low = rom[pc++];
                uint16_t high = rom[pc++];
                value = high;
                addr = low | (high << 8);
                fprintf(out, " $%02X", value);
                signalLabel = resolve_symbol(value, signalSymbols, SIGNAL_COUNT);
                ioLabel = resolve_symbol(value, ioSymbols, IO_COUNT);
            }

              // Verifica se o endereço possui um símbolo
            
           
            if (mValue  > 0) {  
                 fprintf(out,"   #$%02X ", mValue);
            } 
             // Formata a saída com símbolo, se disponível
            if (signalLabel) {
                 fprintf(out," %s ;%d,%d ", signalLabel,instr.cycles,instr.bytes);
            } else if (ioLabel) {
                fprintf(out," %s  ;%d,%d ",   ioLabel,instr.cycles,instr.bytes);
            } else {
                 fprintf(out,"  ;%d,%d ",  instr.cycles,instr.bytes);
            }
            if (value > 0) {
                fprintf(out, "; #$%02X", value);
            }
            
            fprintf(out, "\n");
        } else {
            fprintf(out, " .byte $%02X\n", opcode);
        }
    }

    fclose(out);
}