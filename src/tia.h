// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.


#ifndef TIA_H
#define TIA_H

#include <stdint.h>
#include <SDL2/SDL.h>

// Definições para a tela
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 192
#define SCALE 3



// Funções do TIA
void tia_init();
void tia_update(uint8_t *rom);

void tia_cleanup();

void render_elements(uint8_t *rom);

void tia_set_pixel(int x, int y, uint32_t color);

#endif // TIA_H
