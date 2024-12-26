#ifndef LOG_H
#define LOG_H

#include <stdint.h>
#include <stdio.h>


void init_logs();
void log_message(int logType, const char *message);

#endif // LOG_H