#include "input.h"

#include <SDL2/SDL.h>

// Variáveis para armazenar o estado dos inputs
uint8_t swchb = 0xFF; // Estado padrão dos switches
uint8_t swcha = 0xFF; // Estado padrão dos controles

void input_init() {
    swchb = 0xFF; // Reseta os switches
    swcha = 0xFF; // Reseta os controles
}

void input_update(bool *is_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:           
                {
                    *is_running = false; // Sai do loop principal
                    exit(0);                       
                }
            break;
            

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_1: swchb &= ~0x01; break; // Select
                    case SDLK_2: swchb &= ~0x02; break; // Reset
                    case SDLK_UP: swcha &= ~0x10; break; // Cima
                    case SDLK_DOWN: swcha &= ~0x20; break; // Baixo
                    case SDLK_LEFT: swcha &= ~0x40; break; // Esquerda
                    case SDLK_RIGHT: swcha &= ~0x80; break; // Direita
                    case SDLK_SPACE: swcha &= ~0x01; break; // Fogo
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_1: swchb |= 0x01; break;
                    case SDLK_2: swchb |= 0x02; break;
                    case SDLK_UP: swcha |= 0x10; break;
                    case SDLK_DOWN: swcha |= 0x20; break;
                    case SDLK_LEFT: swcha |= 0x40; break;
                    case SDLK_RIGHT: swcha |= 0x80; break;
                    case SDLK_SPACE: swcha |= 0x01; break;
                }
                break;
            // case SDL_MOUSEBUTTONDOWN:
            //     printf("EVENT: MOUSEBUTTONDOWN (Button: %d, x: %d, y: %d)\n",
            //         event.button.button, event.button.x, event.button.y);
            //     break;

            // case SDL_MOUSEBUTTONUP:
            //     printf("EVENT: MOUSEBUTTONUP (Button: %d, x: %d, y: %d)\n",
            //         event.button.button, event.button.x, event.button.y);
            //     break;

            // case SDL_MOUSEMOTION:
            //     printf("EVENT: MOUSEMOTION (x: %d, y: %d, xrel: %d, yrel: %d)\n",
            //         event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            //     break;

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
        }
    }

    // Atualiza os valores na memória mapeada
    memory[0x3C] = swchb; // Atualiza switches
    memory[0x282] = swcha; // Atualiza controles
}

// Leitura direta de inputs
uint8_t input_read(uint16_t addr) {
    switch (addr) {
        case 0x3C: return swchb; // Switches
        case 0x282: return swcha; // Controles
        default: return 0xFF; // Retorna padrão
    }
}

// Escrita (caso necessário para portas de saída)
void input_write(uint16_t addr, uint8_t value) {
    switch (addr) {
        case 0x3C: swchb = value; break;
        case 0x282: swcha = value; break;
    }
}
