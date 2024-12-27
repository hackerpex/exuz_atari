
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

FILE *cpu_log_file;
FILE *memory_log_file;
// Função para inicializar o log
bool logs_enabled = false;

void init_logs() {
    cpu_log_file = fopen("cpu.log", "w");
    if (!cpu_log_file) {
        fprintf(stderr, "Erro ao gerar logs: %s\n", "cpu.log");
        exit(1);
    }
    memory_log_file = fopen("memory.log", "w");
    if (!memory_log_file) {
        fprintf(stderr, "Erro ao gerar logs: %s\n", "cpu.log");
        exit(1);
    }

    logs_enabled = true;
   

}


// Função para registrar informações no log
void log_message_to_file(FILE *file, const char *message) {

    fprintf(file, "Message: %s\n",message);            
    fflush(file); // Garante que os dados sejam gravados imediatamente
    
}

void log_message(int logType, const char *message) {
        if (logs_enabled)
        {
            switch (logType) {
            case 1: // CPU  
            {
                log_message_to_file(cpu_log_file, message);
            }
            break;
            case 2: // CPU  
            {
                log_message_to_file(memory_log_file, message);
            }
            break;
            }
        }
        

}

