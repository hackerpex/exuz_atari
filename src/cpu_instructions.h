
#include <stdint.h>


//MODOS DE ENDEREÇAMENTO (ver tabela na documentação)
#define INVALID	0 // 1 byte
#define IMPLIED		1 // 1 byte
#define ACCUMULATOR	2 // 1 byte 
#define IMMEDIATE	3 // 2 byte
#define ZERO_PAGE	4 // 2 byte
#define ZERO_PAGE_X	5 // 2 byte
#define ZERO_PAGE_Y	6 // 2 byte
#define ABSOLUTE	7 // 3 byte
#define ABSOLUTE_X	8 // 3 byte
#define ABSOLUTE_Y	9 // 3 byte
#define JMP_INDIRECT	10 // 3 byte
#define INDIRECT	11 // 2 byte
#define INDIRECT_X	12 // 2 byte
#define INDIRECT_Y	13 // 2 byte
#define RELATIVE	14 // 2 byte

// MNEMONICS
#define ADC  0x69
#define AND  0x29
#define ASL  0x0A
#define BCC  0x90
#define BCS  0xB0
#define BEQ  0xF0
#define BIT  0x24
#define BMI  0x30
#define BNE  0xD0
#define BPL  0x10
#define BRK  0x00
#define BVC  0x50
#define BVS  0x70
#define CLC  0x18
#define CLD  0xD8
#define CLI  0x58
#define CLV  0xB8
#define CMP  0xC9
#define CPX  0xE0
#define CPY  0xC0
#define DEC  0xC6
#define DEX  0xCA
#define DEY  0x88
#define EOR  0x49
#define INC  0xE6
#define INX  0xE8
#define INY  0xC8
#define JMP  0x4C
#define JSR  0x20
#define LDA  0xA9
#define LDX  0xA2
#define LDY  0xA0
#define LSR  0x4A
#define NOP  0xEA
#define ORA  0x09
#define PHA  0x48
#define PHP  0x08
#define PLA  0x68
#define PLP  0x28
#define ROL  0x2A
#define ROR  0x6A
#define RTI  0x40
#define RTS  0x60
#define SBC  0xE9
#define SEC  0x38
#define SED  0xF8
#define SEI  0x78
#define STA  0x8D
#define STX  0x86
#define STY  0x84
#define TAX  0xAA
#define TAY  0xA8
#define TSX  0xBA
#define TXA  0x8A
#define TXS  0x9A
#define TYA  0x98



typedef struct {    
    const char *mnemonic;
    int cycles;
    int bytes;
    int mode;
    const char *description;
    const char *example;
} Instruction;

typedef struct {
    uint16_t address;
    const char *label;
} Symbol;

// Definição das instruções
Instruction instructions[256] = {
     [0x00] = {"brk", 7, 1, IMPLIED, "Force Interrupt", "BRK"},
    [0x01] = {"ora", 6, 2, INDIRECT_X, "OR with Accumulator", "ORA ($20,X)"},
    [0x02] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x03] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x04] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x05] = {"ora", 3, 2, ZERO_PAGE, "OR with Accumulator", "ORA $20"},
    [0x06] = {"asl", 5, 2, ZERO_PAGE, "Arithmetic Shift Left", "ASL $20"},
    [0x07] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x08] = {"php", 3, 1, IMPLIED, "Push Processor Status", "PHP"},
    [0x09] = {"ora", 2, 2, IMMEDIATE, "OR with Accumulator", "ORA #$10"},
    [0x0A] = {"asl", 2, 1, ACCUMULATOR, "Arithmetic Shift Left", "ASL A"},
    [0x0B] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x0C] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x0D] = {"ora", 4, 3, ABSOLUTE, "OR with Accumulator", "ORA $2000"},
    [0x0E] = {"asl", 6, 3, ABSOLUTE, "Arithmetic Shift Left", "ASL $2000"},
    [0x0F] = {"---", 0, 0, INVALID, "Invalid ", "---"},

    [0x10] = {"bpl", 2, 2, RELATIVE, "Branch if Positive", "BPL $10"},
    [0x11] = {"ora", 5, 2, INDIRECT_Y, "OR with Accumulator", "ORA ($20),Y"},
    [0x12] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x13] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x14] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x15] = {"ora", 4, 2, ZERO_PAGE_X, "OR with Accumulator", "ORA $20,X"},
    [0x16] = {"asl", 6, 2, ZERO_PAGE_X, "Arithmetic Shift Left", "ASL $20,X"},
    [0x17] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x18] = {"clc", 2, 1, IMPLIED, "Clear Carry Flag", "CLC"},
    [0x19] = {"ora", 4, 3, ABSOLUTE_Y, "OR with Accumulator", "ORA $2000,Y"},
    [0x1A] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x1B] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x1C] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x1D] = {"ora", 4, 3, ABSOLUTE_X, "OR with Accumulator", "ORA $2000,X"},
    [0x1E] = {"asl", 7, 3, ABSOLUTE_X, "Arithmetic Shift Left", "ASL $2000,X"},
    [0x1F] = {"---", 0, 0, INVALID, "Invalid ", "---"},

    [0x20] = {"jsr", 6, 3, ABSOLUTE, "Jump to Subroutine", "JSR $2000"},
    [0x21] = {"and", 6, 2, INDIRECT_X, "AND with Accumulator", "AND ($20,X)"},
    [0x22] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x23] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x24] = {"bit", 3, 2, ZERO_PAGE, "Bit Test", "BIT $20"},
    [0x25] = {"and", 3, 2, ZERO_PAGE, "AND with Accumulator", "AND $20"},
    [0x26] = {"rol", 5, 2, ZERO_PAGE, "Rotate Left", "ROL $20"},
    [0x27] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x28] = {"plp", 4, 1, IMPLIED, "Pull Processor Status", "PLP"},
    [0x29] = {"and", 2, 2, IMMEDIATE, "AND with Accumulator", "AND #$10"},
    [0x2A] = {"rol", 2, 1, ACCUMULATOR, "Rotate Left", "ROL A"},
    [0x2B] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x2C] = {"bit", 4, 3, ABSOLUTE, "Bit Test", "BIT $2000"},
    [0x2D] = {"and", 4, 3, ABSOLUTE, "AND with Accumulator", "AND $2000"},
    [0x2E] = {"rol", 6, 3, ABSOLUTE, "Rotate Left", "ROL $2000"},
    [0x2F] = {"---", 0, 0, INVALID, "Invalid ", "---"},
     [0x30] = {"bmi", 2, 2, RELATIVE, "Branch if Minus", "BMI $10"},
    [0x31] = {"and", 5, 2, INDIRECT_Y, "AND with Accumulator", "AND ($20),Y"},
    [0x32] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x33] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x34] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x35] = {"and", 4, 2, ZERO_PAGE_X, "AND with Accumulator", "AND $20,X"},
    [0x36] = {"rol", 6, 2, ZERO_PAGE_X, "Rotate Left", "ROL $20,X"},
    [0x37] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x38] = {"sec", 2, 1, IMPLIED, "Set Carry Flag", "SEC"},
    [0x39] = {"and", 4, 3, ABSOLUTE_Y, "AND with Accumulator", "AND $2000,Y"},
    [0x3A] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x3B] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x3C] = {"---", 0, 0, INVALID, "Invalid ", "---"},
    [0x3D] = {"and", 4, 3, ABSOLUTE_X, "AND with Accumulator", "AND $2000,X"},
    [0x3E] = {"rol", 7, 3, ABSOLUTE_X, "Rotate Left", "ROL $2000,X"},
    [0x3F] = {"---", 0, 0, IMPLIED, "Invalid ", "---"},

    [0x40] = {"rti", 6, 1, IMPLIED, "Return from Interrupt", "RTI"},
    [0x41] = {"eor", 6, 2, INDIRECT_X, "Exclusive OR", "EOR ($20,X)"},
    [0x42] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x43] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x44] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x45] = {"eor", 3, 2, ZERO_PAGE, "Exclusive OR", "EOR $20"},
    [0x46] = {"lsr", 5, 2, ZERO_PAGE, "Logical Shift Right", "LSR $20"},
    [0x47] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x48] = {"pha", 3, 1, IMPLIED, "Push Accumulator", "PHA"},
    [0x49] = {"eor", 2, 2, IMMEDIATE, "Exclusive OR", "EOR #$10"},
    [0x4A] = {"lsr", 2, 1, ACCUMULATOR, "Logical Shift Right", "LSR A"},
    [0x4B] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x4C] = {"jmp", 3, 3, ABSOLUTE, "Jump to Address", "JMP $2000"},
    [0x4D] = {"eor", 4, 3, ABSOLUTE, "Exclusive OR", "EOR $2000"},
    [0x4E] = {"lsr", 6, 3, ABSOLUTE, "Logical Shift Right", "LSR $2000"},
    [0x4F] = {"---", 0, 0, INVALID, "Invalid", "---"},

     [0x50] = {"bvc", 2, 2, RELATIVE, "Branch if Overflow Clear", "BVC $10"},
    [0x51] = {"eor", 5, 2, INDIRECT_Y, "Exclusive OR", "EOR ($20),Y"},
    [0x52] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x53] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x54] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x55] = {"eor", 4, 2, ZERO_PAGE_X, "Exclusive OR", "EOR $20,X"},
    [0x56] = {"lsr", 6, 2, ZERO_PAGE_X, "Logical Shift Right", "LSR $20,X"},
    [0x57] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x58] = {"cli", 2, 1, IMPLIED, "Clear Interrupt Disable", "CLI"},
    [0x59] = {"eor", 4, 3, ABSOLUTE_Y, "Exclusive OR", "EOR $2000,Y"},
    [0x5A] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x5B] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x5C] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x5D] = {"eor", 4, 3, ABSOLUTE_X, "Exclusive OR", "EOR $2000,X"},
    [0x5E] = {"lsr", 7, 3, ABSOLUTE_X, "Logical Shift Right", "LSR $2000,X"},
    [0x5F] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0x60] = {"rts", 6, 1, IMPLIED, "Return from Subroutine", "RTS"},
    [0x61] = {"adc", 6, 2, INDIRECT_X, "Add with Carry", "ADC ($20,X)"},
    [0x62] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x63] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x64] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x65] = {"adc", 3, 2, ZERO_PAGE, "Add with Carry", "ADC $20"},
    [0x66] = {"ror", 5, 2, ZERO_PAGE, "Rotate Right", "ROR $20"},
    [0x67] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x68] = {"pla", 4, 1, IMPLIED, "Pull Accumulator", "PLA"},
    [0x69] = {"adc", 2, 2, IMMEDIATE, "Add with Carry", "ADC #$10"},
    [0x6A] = {"ror", 2, 1, ACCUMULATOR, "Rotate Right", "ROR A"},
    [0x6B] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x6C] = {"jmp", 5, 3, INDIRECT, "Jump to Address Indirect", "JMP ($2000)"},
    [0x6D] = {"adc", 4, 3, ABSOLUTE, "Add with Carry", "ADC $2000"},
    [0x6E] = {"ror", 6, 3, ABSOLUTE, "Rotate Right", "ROR $2000"},
    [0x6F] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0x70] = {"bvs", 2, 2, RELATIVE, "Branch if Overflow Set", "BVS $10"},
    [0x71] = {"adc", 5, 2, INDIRECT_Y, "Add with Carry", "ADC ($20),Y"},
    [0x72] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x73] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x74] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x75] = {"adc", 4, 2, ZERO_PAGE_X, "Add with Carry", "ADC $20,X"},
    [0x76] = {"ror", 6, 2, ZERO_PAGE_X, "Rotate Right", "ROR $20,X"},
    [0x77] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x78] = {"sei", 2, 1, IMPLIED, "Set Interrupt Disable", "SEI"},
    [0x79] = {"adc", 4, 3, ABSOLUTE_Y, "Add with Carry", "ADC $2000,Y"},
    [0x7A] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x7B] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x7C] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x7D] = {"adc", 4, 3, ABSOLUTE_X, "Add with Carry", "ADC $2000,X"},
    [0x7E] = {"ror", 7, 3, ABSOLUTE_X, "Rotate Right", "ROR $2000,X"},
    [0x7F] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0x80] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x81] = {"sta", 6, 2, INDIRECT_X, "Store Accumulator", "STA ($20,X)"},
    [0x82] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x83] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x84] = {"sty", 3, 2, ZERO_PAGE, "Store Y Register", "STY $20"},
    [0x85] = {"sta", 3, 2, ZERO_PAGE, "Store Accumulator", "STA $20"},
    [0x86] = {"stx", 3, 2, ZERO_PAGE, "Store X Register", "STX $20"},
    [0x87] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x88] = {"dey", 2, 1, IMPLIED, "Decrement Y Register", "DEY"},
    [0x89] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x8A] = {"txa", 2, 1, IMPLIED, "Transfer X to Accumulator", "TXA"},
    [0x8B] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x8C] = {"sty", 4, 3, ABSOLUTE, "Store Y Register", "STY $2000"},
    [0x8D] = {"sta", 4, 3, ABSOLUTE, "Store Accumulator", "STA $2000"},
    [0x8E] = {"stx", 4, 3, ABSOLUTE, "Store X Register", "STX $2000"},
    [0x8F] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0x90] = {"bcc", 2, 2, RELATIVE, "Branch if Carry Clear", "BCC $10"},
    [0x91] = {"sta", 6, 2, INDIRECT_Y, "Store Accumulator", "STA ($20),Y"},
    [0x92] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x93] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x94] = {"sty", 4, 2, ZERO_PAGE_X, "Store Y Register", "STY $20,X"},
    [0x95] = {"sta", 4, 2, ZERO_PAGE_X, "Store Accumulator", "STA $20,X"},
    [0x96] = {"stx", 4, 2, ZERO_PAGE_Y, "Store X Register", "STX $20,Y"},
    [0x97] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x98] = {"tya", 2, 1, IMPLIED, "Transfer Y to Accumulator", "TYA"},
    [0x99] = {"sta", 5, 3, ABSOLUTE_Y, "Store Accumulator", "STA $2000,Y"},
    [0x9A] = {"txs", 2, 1, IMPLIED, "Transfer X to Stack Pointer", "TXS"},
    [0x9B] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x9C] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x9D] = {"sta", 5, 3, ABSOLUTE_X, "Store Accumulator", "STA $2000,X"},
    [0x9E] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0x9F] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0xA0] = {"ldy", 2, 2, IMMEDIATE, "Load Y Register", "LDY #$10"},
    [0xA1] = {"lda", 6, 2, INDIRECT_X, "Load Accumulator", "LDA ($20,X)"},
    [0xA2] = {"ldx", 2, 2, IMMEDIATE, "Load X Register", "LDX #$10"},
    [0xA3] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xA4] = {"ldy", 3, 2, ZERO_PAGE, "Load Y Register", "LDY $20"},
    [0xA5] = {"lda", 3, 2, ZERO_PAGE, "Load Accumulator", "LDA $20"},
    [0xA6] = {"ldx", 3, 2, ZERO_PAGE, "Load X Register", "LDX $20"},
    [0xA7] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xA8] = {"tay", 2, 1, IMPLIED, "Transfer Accumulator to Y", "TAY"},
    [0xA9] = {"lda", 2, 2, IMMEDIATE, "Load Accumulator", "LDA #$10"},
    [0xAA] = {"tax", 2, 1, IMPLIED, "Transfer Accumulator to X", "TAX"},
    [0xAB] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xAC] = {"ldy", 4, 3, ABSOLUTE, "Load Y Register", "LDY $2000"},
    [0xAD] = {"lda", 4, 3, ABSOLUTE, "Load Accumulator", "LDA $2000"},
    [0xAE] = {"ldx", 4, 3, ABSOLUTE, "Load X Register", "LDX $2000"},
    [0xAF] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0xB0] = {"bcs", 2, 2, RELATIVE, "Branch if Carry Set", "BCS $10"},
    [0xB1] = {"lda", 5, 2, INDIRECT_Y, "Load Accumulator", "LDA ($20),Y"},
    [0xB2] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xB3] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xB4] = {"ldy", 4, 2, ZERO_PAGE_X, "Load Y Register", "LDY $20,X"},
    [0xB5] = {"lda", 4, 2, ZERO_PAGE_X, "Load Accumulator", "LDA $20,X"},
    [0xB6] = {"ldx", 4, 2, ZERO_PAGE_Y, "Load X Register", "LDX $20,Y"},
    [0xB7] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xB8] = {"clv", 2, 1, IMPLIED, "Clear Overflow Flag", "CLV"},
    [0xB9] = {"lda", 4, 3, ABSOLUTE_Y, "Load Accumulator", "LDA $2000,Y"},
    [0xBA] = {"tsx", 2, 1, IMPLIED, "Transfer Stack Pointer to X", "TSX"},
    [0xBB] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xBC] = {"ldy", 4, 3, ABSOLUTE_X, "Load Y Register", "LDY $2000,X"},
    [0xBD] = {"lda", 4, 3, ABSOLUTE_X, "Load Accumulator", "LDA $2000,X"},
    [0xBE] = {"ldx", 4, 3, ABSOLUTE_Y, "Load X Register", "LDX $2000,Y"},
    [0xBF] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0xC0] = {"cpy", 2, 2, IMMEDIATE, "Compare Y Register", "CPY #$10"},
    [0xC1] = {"cmp", 6, 2, INDIRECT_X, "Compare Accumulator", "CMP ($20,X)"},
    [0xC2] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xC3] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xC4] = {"cpy", 3, 2, ZERO_PAGE, "Compare Y Register", "CPY $20"},
    [0xC5] = {"cmp", 3, 2, ZERO_PAGE, "Compare Accumulator", "CMP $20"},
    [0xC6] = {"dec", 5, 2, ZERO_PAGE, "Decrement Memory", "DEC $20"},
    [0xC7] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xC8] = {"iny", 2, 1, IMPLIED, "Increment Y Register", "INY"},
    [0xC9] = {"cmp", 2, 2, IMMEDIATE, "Compare Accumulator", "CMP #$10"},
    [0xCA] = {"dex", 2, 1, IMPLIED, "Decrement X Register", "DEX"},
    [0xCB] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xCC] = {"cpy", 4, 3, ABSOLUTE, "Compare Y Register", "CPY $2000"},
    [0xCD] = {"cmp", 4, 3, ABSOLUTE, "Compare Accumulator", "CMP $2000"},
    [0xCE] = {"dec", 6, 3, ABSOLUTE, "Decrement Memory", "DEC $2000"},
    [0xCF] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0xD0] = {"bne", 2, 2, RELATIVE, "Branch if Not Equal", "BNE $10"},
    [0xD1] = {"cmp", 5, 2, INDIRECT_Y, "Compare Accumulator", "CMP ($20),Y"},
    [0xD2] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xD3] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xD4] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xD5] = {"cmp", 4, 2, ZERO_PAGE_X, "Compare Accumulator", "CMP $20,X"},
    [0xD6] = {"dec", 6, 2, ZERO_PAGE_X, "Decrement Memory", "DEC $20,X"},
    [0xD7] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xD8] = {"cld", 2, 1, IMPLIED, "Clear Decimal Mode", "CLD"},
    [0xD9] = {"cmp", 4, 3, ABSOLUTE_Y, "Compare Accumulator", "CMP $2000,Y"},
    [0xDA] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xDB] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xDC] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xDD] = {"cmp", 4, 3, ABSOLUTE_X, "Compare Accumulator", "CMP $2000,X"},
    [0xDE] = {"dec", 7, 3, ABSOLUTE_X, "Decrement Memory", "DEC $2000,X"},
    [0xDF] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0xE0] = {"cpx", 2, 2, IMMEDIATE, "Compare X Register", "CPX #$10"},
    [0xE1] = {"sbc", 6, 2, INDIRECT_X, "Subtract with Carry", "SBC ($20,X)"},
    [0xE2] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xE3] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xE4] = {"cpx", 3, 2, ZERO_PAGE, "Compare X Register", "CPX $20"},
    [0xE5] = {"sbc", 3, 2, ZERO_PAGE, "Subtract with Carry", "SBC $20"},
    [0xE6] = {"inc", 5, 2, ZERO_PAGE, "Increment Memory", "INC $20"},
    [0xE7] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xE8] = {"inx", 2, 1, IMPLIED, "Increment X Register", "INX"},
    [0xE9] = {"sbc", 2, 2, IMMEDIATE, "Subtract with Carry", "SBC #$10"},
    [0xEA] = {"nop", 2, 1, IMPLIED, "No Operation", "NOP"},
    [0xEB] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xEC] = {"cpx", 4, 3, ABSOLUTE, "Compare X Register", "CPX $2000"},
    [0xED] = {"sbc", 4, 3, ABSOLUTE, "Subtract with Carry", "SBC $2000"},
    [0xEE] = {"inc", 6, 3, ABSOLUTE, "Increment Memory", "INC $2000"},
    [0xEF] = {"---", 0, 0, INVALID, "Invalid", "---"},

    [0xF0] = {"beq", 2, 2, RELATIVE, "Branch if Equal", "BEQ $10"},
    [0xF1] = {"sbc", 5, 2, INDIRECT_Y, "Subtract with Carry", "SBC ($20),Y"},
    [0xF2] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xF3] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xF4] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xF5] = {"sbc", 4, 2, ZERO_PAGE_X, "Subtract with Carry", "SBC $20,X"},
    [0xF6] = {"inc", 6, 2, ZERO_PAGE_X, "Increment Memory", "INC $20,X"},
    [0xF7] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xF8] = {"sed", 2, 1, IMPLIED, "Set Decimal Mode", "SED"},
    [0xF9] = {"sbc", 4, 3, ABSOLUTE_Y, "Subtract with Carry", "SBC $2000,Y"},
    [0xFA] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xFB] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xFC] = {"---", 0, 0, INVALID, "Invalid", "---"},
    [0xFD] = {"sbc", 4, 3, ABSOLUTE_X, "Subtract with Carry", "SBC $2000,X"},
    [0xFE] = {"inc", 7, 3, ABSOLUTE_X, "Increment Memory", "INC $2000,X"},
    [0xFF] = {"---", 0, 0, INVALID, "Invalid", "---"}
};
    


Symbol signalSymbols[] = {
    {0x00, "VSYNC"},   // Vertical sync signal
    {0x01, "VBLANK"},  // Vertical blanking interval control
    {0x02, "WSYNC"},   // Wait for horizontal sync
    {0x03, "RSYNC"},   // Reset horizontal sync counter
    {0x04, "NUSIZ0"},  // Size and copies of player 0
    {0x05, "NUSIZ1"},  // Size and copies of player 1
    {0x06, "COLUP0"},  // Color and luminance for player 0
    {0x07, "COLUP1"},  // Color and luminance for player 1
    {0x08, "COLUPF"},  // Color and luminance for playfield
    {0x09, "COLUBK"},  // Color and luminance for background
    {0x0A, "CTRLPF"},  // Control playfield and ball
    {0x0B, "REFP0"},   // Reflect player 0
    {0x0C, "REFP1"},   // Reflect player 1
    {0x0D, "PF0"},     // Playfield register 0
    {0x0E, "PF1"},     // Playfield register 1
    {0x0F, "PF2"},     // Playfield register 2
    {0x10, "RESP0"},   // Reset player 0 position
    {0x11, "RESP1"},   // Reset player 1 position
    {0x12, "RESM0"},   // Reset missile 0 position
    {0x13, "RESM1"},   // Reset missile 1 position
    {0x14, "RESBL"},   // Reset ball position
    {0x15, "AUDC0"},   // Audio control for channel 0
    {0x16, "AUDC1"},   // Audio control for channel 1
    {0x17, "AUDF0"},   // Audio frequency for channel 0
    {0x18, "AUDF1"},   // Audio frequency for channel 1
    {0x19, "AUDV0"},   // Audio volume for channel 0
    {0x1A, "AUDV1"},   // Audio volume for channel 1
    {0x1B, "GRP0"},    // Graphics for player 0
    {0x1C, "GRP1"},    // Graphics for player 1
    {0x1D, "ENAM0"},   // Enable missile 0
    {0x1E, "ENAM1"},   // Enable missile 1
    {0x1F, "ENABL"},   // Enable ball
    {0x20, "HMP0"},    // Horizontal motion for player 0
    {0x21, "HMP1"},    // Horizontal motion for player 1
    {0x22, "HMM0"},    // Horizontal motion for missile 0
    {0x23, "HMM1"},    // Horizontal motion for missile 1
    {0x24, "HMBL"},    // Horizontal motion for ball
    {0x25, "VDELP0"},  // Vertical delay for player 0
    {0x26, "VDELP1"},  // Vertical delay for player 1
    {0x27, "VDELBL"},  // Vertical delay for ball
    {0x28, "RESMP0"},  // Reset missile 0 to player 0
    {0x29, "RESMP1"},  // Reset missile 1 to player 1
    {0x2A, "HMOVE"},   // Apply horizontal motion
    {0x2B, "HMCLR"},   // Clear horizontal motion registers
    {0x2C, "CXCLR"},   // Clear collision registers
    {0x2D, "$2D"},     // Undefined/Unused
    {0x2E, "$2E"},     // Undefined/Unused
    {0x2F, "$2F"},     // Undefined/Unused
    {0x30, "CXM0P"},   // Collision: missile 0 and player
    {0x31, "CXM1P"},   // Collision: missile 1 and player
    {0x32, "CXP0FB"},  // Collision: player 0 and playfield/ball
    {0x33, "CXP1FB"},  // Collision: player 1 and playfield/ball
    {0x34, "CXM0FB"},  // Collision: missile 0 and playfield/ball
    {0x35, "CXM1FB"},  // Collision: missile 1 and playfield/ball
    {0x36, "CXBLPF"},  // Collision: ball and playfield
    {0x37, "CXPPMM"},  // Collision: players and missiles
    {0x38, "INPT0"},   // Input port 0
    {0x39, "INPT1"},   // Input port 1
    {0x3A, "INPT2"},   // Input port 2
    {0x3B, "INPT3"},   // Input port 3
    {0x3C, "INPT4"},   // Input port 4
    {0x3D, "INPT5"}    // Input port 5
};

Symbol ioSymbols[] = {
    {0x280, "SWCHA"},   // I/O port A data register for joysticks
    {0x281, "SWACNT"},  // I/O port A data direction register
    {0x282, "SWCHB"},   // I/O port B data register for console switches
    {0x283, "SWBCNT"},  // I/O port B data direction register
    {0x284, "INTIM"},   // Timer output
    {0x285, "$0285"},  // Undefined/Reserved
    {0x286, "$0286"},  // Undefined/Reserved
    {0x287, "$0287"},  // Undefined/Reserved
    {0x288, "$0288"},  // Undefined/Reserved
    {0x289, "$0289"},  // Undefined/Reserved
    {0x28A, "$028A"},  // Undefined/Reserved
    {0x28B, "$028B"},  // Undefined/Reserved
    {0x28C, "$028C"},  // Undefined/Reserved
    {0x28D, "$028D"},  // Undefined/Reserved
    {0x28E, "$028E"},  // Undefined/Reserved
    {0x28F, "$028F"},  // Undefined/Reserved
    {0x290, "$0290"},  // Undefined/Reserved
    {0x291, "$0291"},  // Undefined/Reserved
    {0x292, "$0292"},  // Undefined/Reserved
    {0x293, "$0293"},  // Undefined/Reserved
    {0x294, "TIM1T"},   // Timer 1 clock interval
    {0x295, "TIM8T"},   // Timer 8 clock interval
    {0x296, "TIM64T"},  // Timer 64 clock interval
    {0x297, "T1024T"}   // Timer 1024 clock interval
};


#define SIGNAL_COUNT (sizeof(signalSymbols) / sizeof(Symbol))
#define IO_COUNT (sizeof(ioSymbols) / sizeof(Symbol))