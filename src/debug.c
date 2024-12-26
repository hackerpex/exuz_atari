#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "cpu.h"

// Função para inicializar o log
bool debug_enabled = false;
SDL_Window *memory_window = NULL;
SDL_Renderer *memory_renderer = NULL;
TTF_Font *font = NULL;

const char * lastOpration = "";

void init_font() {
    if (TTF_Init() == -1) {
        fprintf(stderr, "Erro ao inicializar TTF: %s\n", TTF_GetError());
        exit(1);
    }

    font = TTF_OpenFont("font.ttf", 16); 
    if (!font) {
        fprintf(stderr, "Erro ao carregar fonte: %s\n", TTF_GetError());
        exit(1);
    }
}

void register_operations() {    
    


    // printf("CPU inicializado com %d instruções registradas.\n", instruction_count);


    // printf("CPU inicializado com %d instruções registradas.\n", instruction_count);
}


void init_debug() {
   memory_window = SDL_CreateWindow("Memory Viewer",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     1200, 400, SDL_WINDOW_SHOWN); // Janela vertical para tabela

    if (!memory_window) {
        fprintf(stderr, "Falha ao criar janela de memória: %s\n", SDL_GetError());
        exit(1);
    }

    memory_renderer = SDL_CreateRenderer(memory_window, -1, SDL_RENDERER_ACCELERATED);
    if (!memory_renderer) {
        fprintf(stderr, "Falha ao criar renderizador para memória: %s\n", SDL_GetError());
        exit(1);
    }
    init_font();
    debug_enabled = true;
}

void debugMemory(CPU *cpu) {
    printf("A: 0x%02X\n", cpu->a);
    printf("X: 0x%02X\n", cpu->x);
    printf("Y: 0x%02X\n", cpu->y);
    printf("SP: 0x%02X\n", cpu->sp);
    printf("PC: 0x%04X\n", cpu->pc);    
    printf("Status: 0x%02X\n", cpu->ps);
}

void print_text(const char *text, int x, int y, SDL_Color color, TTF_Font *font) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(memory_renderer, surface);

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(memory_renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
   
}

// Função para registrar informações no log
void update_debug(CPU *cpu,uint8_t *memory) {
    if (debug_enabled) {
       SDL_SetRenderDrawColor(memory_renderer, 0, 0, 0, 255); // Fundo preto
    SDL_RenderClear(memory_renderer);

    SDL_Color white = {255, 255, 255, 255}; // Cor branca para texto
    SDL_Color gray = {150, 150, 150, 150}; // Cor branca para texto
    int x = 20;  // Posição horizontal inicial
    int y = 20;  // Posição vertical inicial
    int col_width = 70; // Largura da coluna
    int row_height = 18; // Altura da linha

    for (int col = 0; col < 16; col++) { // De 0x0 a 0xF
        y = 20; // Reinicia a linha para cada coluna

        for (int row = 0; row < 16; row++) { // 16 linhas por coluna
            int addr = (col * 16) + row; // Calcula o endereço atual (0x00 até 0xFF)

            // Prepara o texto a ser exibido (Ex: "00: FF")
            char text_addr[16];
            snprintf(text_addr, sizeof(text_addr), "%02X: ", addr);
            print_text(text_addr, x, y, gray, font);
            char text_value[16];
            snprintf(text_value, sizeof(text_value), "%02X", memory[addr]);
            print_text(text_value, x + 30, y, white, font);
            // Renderiza o texto na posição atual
            // SDL_Surface *surface = TTF_RenderText_Solid(font, buffer, white);
            // SDL_Texture *texture = SDL_CreateTextureFromSurface(memory_renderer, surface);

            // SDL_Rect rect = {x, y, surface->w, surface->h};
            // SDL_RenderCopy(memory_renderer, texture, NULL, &rect);

            // SDL_FreeSurface(surface);  // Libera a superfície
            // SDL_DestroyTexture(texture); // Libera a textura

            y += row_height; // Próxima linha na coluna atual
        }

        x += col_width; // Move para a próxima coluna
    }

            char memPosition[16];
            snprintf(memPosition, sizeof(memPosition), "running:%04X", cpu->pc);
            print_text(memPosition, 20, 320, white, font);

            char registers[128];
            snprintf(registers, sizeof(registers), "REGISTERS: A%02X  X:%02X  Y:%02X SP:%02X", cpu->a, cpu->x, cpu->y, cpu->sp);
            print_text(registers, 20, 340, white, font);
            char status[128];
            snprintf(status, sizeof(status), "STATUS: %02X  ", cpu->ps);
            print_text(status, 20, 360, white, font);

            // Monta a string de status com as cores apropriadas
            snprintf(status, sizeof(status), "STATUS:");
            print_text(status, 20, 360, white, font);

            // Flags individuais
            print_text((cpu->ps & 0x80) ? "N" : "n", 140, 360, (cpu->ps & 0x80) ? white : gray, font); // Negative
            print_text((cpu->ps & 0x40) ? "V" : "v", 160, 360, (cpu->ps & 0x40) ? white : gray, font); // Overflow
            print_text("-", 180, 360, gray, font); // Placeholder sempre inativo
            print_text((cpu->ps & 0x10) ? "B" : "b", 200, 360, (cpu->ps & 0x10) ? white : gray, font); // Break
            print_text((cpu->ps & 0x08) ? "D" : "d", 220, 360, (cpu->ps & 0x08) ? white : gray, font); // Decimal
            print_text((cpu->ps & 0x04) ? "I" : "i", 240, 360, (cpu->ps & 0x04) ? white : gray, font); // Interrupt
            print_text((cpu->ps & 0x02) ? "Z" : "z", 260, 360, (cpu->ps & 0x02) ? white : gray, font); // Zero
            print_text((cpu->ps & 0x01) ? "C" : "c", 280, 360, (cpu->ps & 0x01) ? white : gray, font); // Carry


    SDL_RenderPresent(memory_renderer); // Atualiza a tela
    }
}


