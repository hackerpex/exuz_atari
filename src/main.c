// Este projeto é licenciado sob a licença propria.
// Este código é parte do emulador exuz e não pode ser usado sem que se respeite as restrições de uso.
// Aqui está a licença:
// Copyright (c) 2023 Rodrigo Camargo
// O uso do programa ou partes dele apenas são liberados para uso academico não comercial.
// Qualquer contribuição ao software deve ser feita de forma a garantir a continuidade desta licença.



#include "cpu.h"
#include "tia.h"
#include "riot.h"
#include "input.h"
#include "state.h"
#include "memory.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>



void debugMemory(CPU *cpu) {
    printf("A: 0x%02X\n", cpu->a);
    printf("X: 0x%02X\n", cpu->x);
    printf("Y: 0x%02X\n", cpu->y);
    printf("SP: 0x%02X\n", cpu->sp);
    printf("PC: 0x%04X\n", cpu->pc);    
    printf("Status: 0x%02X\n", cpu->status);
}

void mainLoop(CPU *cpu, RIOT *riot) {
    

    riot_init(riot);
    tia_init();
   

    // Loop principal
    while (is_running) {
        input_update(&is_running); // Atualiza o estado dos inputs
        // handle_events();
        cpu_step(cpu); // Executa instrução por instrução
        riot_tick(riot);  // Atualiza o temporizador

        tia_update(memory);      // Atualiza os gráficos

        // debugMemory(cpu);
        SDL_Delay(1);  // Aproximadamente 60 FPS
    }

    // Finaliza o TIA
    tia_cleanup();
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    
    CPU cpu;
    RIOT riot;
    
    init_cpu_log();

    cpu_load_rom(&cpu, "sample.a26"); // Substitua por uma ROM válida
    mainLoop(&cpu, &riot);

    return 0;
}
