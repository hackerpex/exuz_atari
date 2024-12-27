// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.

#include "tia.h"
#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>

// Framebuffer para os pixels
uint32_t framebuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture *texture = NULL;

// Inicializa o TIA e o SDL
void tia_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erro ao inicializar SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Exuz atari 2600 Emulator",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH * SCALE,
                              SCREEN_HEIGHT * SCALE,
                              SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "Erro ao criar janela: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Erro ao criar renderizador: %s\n", SDL_GetError());
        exit(1);
    }

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!texture) {
        fprintf(stderr, "Erro ao criar textura: %s\n", SDL_GetError());
        exit(1);
    }

    memset(framebuffer, 0, sizeof(framebuffer)); // Limpa o framebuffer
}

void render_random_pixel() {
    // Gera coordenadas aleatórias dentro dos limites da janela
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;

    // Define uma cor aleatória para o pixel
    uint8_t r = rand() % 256; // Vermelho
    uint8_t g = rand() % 256; // Verde
    uint8_t b = rand() % 256; // Azul

    SDL_SetRenderDrawColor(renderer, r, g, b, 255); // Define a cor
    SDL_RenderDrawPoint(renderer, x, y);           // Desenha o pixel
}

// Atualiza o TIA (renderiza o framebuffer na tela)
void tia_update(uint8_t *rom) {
     SDL_UpdateTexture(texture, NULL, framebuffer, SCREEN_WIDTH * sizeof(uint32_t));
    //  SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    render_elements(rom);
    render_random_pixel();

    SDL_RenderPresent(renderer);
}



// Define a cor de um pixel no framebuffer
void tia_set_pixel(int x, int y, uint32_t color) {
     printf("draw pixel with color: 0x%08X\n", color);
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        framebuffer[y * SCREEN_WIDTH + x] = color;
    }
}

// Finaliza o TIA e libera os recursos do SDL
void tia_cleanup() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void render_playfield(uint8_t *rom, int y) {
    uint8_t pf0 = rom[0x07]; // Primeiro bloco do Playfield
    uint8_t pf1 = rom[0x08]; // Segundo bloco
    uint8_t pf2 = rom[0x09]; // Terceiro bloco

    // Renderiza o PF0 (4 bits visíveis)
    for (int i = 0; i < 4; i++) {
        uint8_t pixel = (pf0 >> (7 - i)) & 1;
        if (pixel) tia_set_pixel(i, y, 0xFFFFFFFF);
    }

    // Renderiza o PF1 e PF2 (8 bits cada)
    for (int i = 0; i < 8; i++) {
        uint8_t pixel1 = (pf1 >> (7 - i)) & 1;
        uint8_t pixel2 = (pf2 >> (7 - i)) & 1;
        if (pixel1) tia_set_pixel(i + 4, y, 0xFFFFFFFF);  // PF1 começa após PF0
        if (pixel2) tia_set_pixel(i + 12, y, 0xFFFFFFFF); // PF2 começa após PF1
    }
}


void render_player(uint8_t *rom, int x, int y, int player) {
    uint8_t sprite = rom[player == 0 ? 0x1B : 0x1C]; // Posição do jogador
    uint32_t color = (player == 0) ? 0xFF0000FF : 0xFFFF0000; // Azul ou vermelho

    for (int i = 0; i < 8; i++) {
        uint8_t pixel = (sprite >> (7 - i)) & 1;
        if (pixel) {
            tia_set_pixel(x + i, y, color);
        }
    }
}

void render_elements(uint8_t *rom) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
            render_playfield(rom, y);              
            render_player(rom, 50, y, 0);          
            render_player(rom, 100, y, 1);         
        }
}

