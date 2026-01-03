#include "logger.h"

// FUNÇÃO AUXILIAR PARA RETORNAR TEMPO ATUAL!
char* current_time(void){
    time_t now;
    struct tm *timeinfo;
    static char timeStr[TIME_BUFFER_SIZE];

    time(&now);

    timeinfo = localtime(&now);

    strftime(timeStr, TIME_BUFFER_SIZE, "%H:%M:%S", timeinfo);

    return timeStr;
}

// INICIALIZANDO CONFIG DO LOGGER
LogConfig config = {
    NULL,
    true, 
    true, 
    true
};


// INICIALIZANDO OS NIVEIS DE LOG;
LogLevel levels[NUM_LEVELS] = {
    {DEBUG,     "DEBUG",    "\e[0;32m"},
    {INFO,      "INFO",     "\e[0;34m"},
    {WARNING,   "WARNING",  "\e[0;33m"},
    {ERROR,     "ERROR",    "\e[0;31m"},
    {CRITICAL,  "CRITICAL", "\e[0;91m"}
};

// Função Helper para formatar o log.
void _log_format(LogLevel *log_l, char* message) {
    if(config.log_to_console){
        if(config.use_colors){
            printf("%s[%s] %s" COLOR_RESET " - %s\n",log_l->color, log_l->name, current_time(), message);
        }else{
            printf("[%s] %s - %s\n", log_l->name, current_time(), message);
        }
    }
    if(config.log_to_file && config.file != NULL){
        fprintf( config.file ,"[%s] %s - %s\n", log_l->name, current_time(), message);
        fflush(config.file);
    }
        
}

LogStats stats = {0};

void debug(char* message){
    _log_format(&levels[0], message);
}
void info(char* message){
    _log_format(&levels[1], message);
}
void warning(char* message){
    _log_format(&levels[2], message);
}
void error(char* message){
    _log_format(&levels[3], message);
}
void critical(char* message){
    _log_format(&levels[4], message);
}



Level log_levels[5] = {
    debug,
    info,
    warning,
    error,
    critical
};

void logger_init(const char *filename){
    config.file = fopen(filename, "a");
    if (config.file == NULL) {
        fprintf(stderr, "ERRO: não foi possível abrir %s\n\n", filename);
        config.log_to_file = false;  // Desabilita file logging
    }
}
void logger_close(void){
    if (config.file != NULL) {
        fclose(config.file);
        config.file = NULL;  // Evita uso após fechamento
    }
}
void logger_set_console(bool enable){
    config.log_to_console = enable;
}
void logger_set_file(bool enable){
    config.log_to_file = enable;
}



void logger(enum Level_Type type, char* message){
    if (message == NULL) {
        fprintf(stderr, "Erro: message é NULL\n");
        return;
    }
    if (type < 0 || type >= NUM_LEVELS) {
        fprintf(stderr, "Erro: tipo de log inválido\n");
        return;
    }
    // log_levels[type](message);
    log_levels[type](message);
    stats.counts[type]++;
}

void logger_print_stats() {
    printf("\n=== LOG STATS ===\n");
    for (int i = 0; i < NUM_LEVELS; i++) {
        printf("%s: %d\n", levels[i].name, stats.counts[i]);
    }
}

void logger_disable_colors() {
    config.use_colors = false;
}

