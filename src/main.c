// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.


#include <SDL2/SDL.h>
#include "cpu.h"
#include <stdio.h>
#include <stdbool.h>

// Definições básicas
#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 192
#define SCALE 3

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = true;

// Função para lidar com eventos
void handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        }
    }
}

// Função principal de renderização
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Exemplo: desenhar um pixel branco no centro
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    SDL_RenderPresent(renderer);
}

void debugMemory(CPU *cpu) {
    printf("A: 0x%02X\n", cpu->a);
    printf("X: 0x%02X\n", cpu->x);
    printf("Y: 0x%02X\n", cpu->y);
    printf("SP: 0x%02X\n", cpu->sp);
    printf("PC: 0x%04X\n", cpu->pc);
    printf("Status: 0x%02X\n", cpu->status);
}
int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Falha ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Cria janela e renderizador
    window = SDL_CreateWindow("Exuz Atari 2600 Emulator",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH * SCALE,
                              WINDOW_HEIGHT * SCALE,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Falha ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Falha ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    CPU cpu;
    cpu_load_rom(&cpu, "sample.a26"); // Substitua por uma ROM válida


    // Loop principal
    while (is_running) {
        // Executa instrução por instrução
        cpu_step(&cpu); 
        debugMemory(&cpu);

        handle_events();
        render();
       
        SDL_Delay(100); // 16 é Aproximadamente 60 FPS
    }

    // Liberação de recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
