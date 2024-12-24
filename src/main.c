// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.



#include "cpu.h"
#include "tia.h"
#include "riot.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define KEY_UP_CODE    0x52
#define KEY_DOWN_CODE  0x51
#define KEY_LEFT_CODE  0x50
#define KEY_RIGHT_CODE 0x4F
#define KEY_FIRE_CODE  0x2C


bool is_running = true;
bool key_up = false;
bool key_down = false;
bool key_left = false;
bool key_right = false;
bool key_fire = false;

// Função para lidar com eventos
void handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    switch (event.type) {
        case SDL_QUIT:
            printf("EVENT: QUIT\n");
            is_running = false; // Sai do loop principal
            break;

        case SDL_KEYDOWN:
            printf("EVENT: KEYDOWN (Keycode: 0x%X, Scancode: 0x%X)\n",
                   event.key.keysym.sym, event.key.keysym.scancode);
                   key_up = event.key.keysym.scancode == KEY_UP_CODE;
                   key_down = event.key.keysym.scancode == KEY_DOWN_CODE;
                   key_left = event.key.keysym.scancode == KEY_LEFT_CODE;
                   key_right = event.key.keysym.scancode == KEY_RIGHT_CODE;
                   key_fire = event.key.keysym.scancode == KEY_FIRE_CODE;
            break;

        case SDL_KEYUP:
            printf("EVENT: KEYUP (Keycode: 0x%X, Scancode: 0x%X)\n",
                   event.key.keysym.sym, event.key.keysym.scancode);
            break;

        case SDL_MOUSEBUTTONDOWN:
            printf("EVENT: MOUSEBUTTONDOWN (Button: %d, x: %d, y: %d)\n",
                   event.button.button, event.button.x, event.button.y);
            break;

        case SDL_MOUSEBUTTONUP:
            printf("EVENT: MOUSEBUTTONUP (Button: %d, x: %d, y: %d)\n",
                   event.button.button, event.button.x, event.button.y);
            break;

        case SDL_MOUSEMOTION:
            printf("EVENT: MOUSEMOTION (x: %d, y: %d, xrel: %d, yrel: %d)\n",
                   event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            break;

        case SDL_JOYAXISMOTION:
            printf("EVENT: JOYAXISMOTION (Axis: %d, Value: %d)\n",
                   event.jaxis.axis, event.jaxis.value);
            break;

        case SDL_JOYBUTTONDOWN:
            printf("EVENT: JOYBUTTONDOWN (Button: %d)\n", event.jbutton.button);
            break;

        case SDL_JOYBUTTONUP:
            printf("EVENT: JOYBUTTONUP (Button: %d)\n", event.jbutton.button);
            break;

        default:
            printf("EVENT: UNKNOWN (Type: 0x%02X)\n", event.type);
            break;
    }
    }
}

void debugMemory(CPU *cpu) {
    printf("A: 0x%02X\n", cpu->a);
    printf("X: 0x%02X\n", cpu->x);
    printf("Y: 0x%02X\n", cpu->y);
    printf("SP: 0x%02X\n", cpu->sp);
    printf("PC: 0x%04X\n", cpu->pc);
    printf("UP: 0x%02X\n", key_up);

    printf("Status: 0x%02X\n", cpu->status);
}

void mainLoop(CPU *cpu, RIOT *riot) {
    riot_init(riot);
    tia_init();

    // Loop principal
    while (is_running) {
        handle_events();
        cpu_step(cpu); // Executa instrução por instrução
        riot_tick(riot);  // Atualiza o temporizador

        tia_update(memory);      // Atualiza os gráficos

        debugMemory(cpu);
        SDL_Delay(0);  // Aproximadamente 60 FPS
    }

    // Finaliza o TIA
    tia_cleanup();
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    
    CPU cpu;
    RIOT riot;

    cpu_load_rom(&cpu, "sample.a26"); // Substitua por uma ROM válida
    mainLoop(&cpu, &riot);

    return 0;
}
