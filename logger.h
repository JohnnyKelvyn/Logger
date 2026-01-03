#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define COLOR_RESET "\e[0m"

#define TIME_BUFFER_SIZE 100



// Definindo typedef para facilitar a chamada de funções por ponteiros
typedef void (*Level)(char*);

// Variavel para configuração de cores 

typedef struct {
    FILE *file;              // ??? - Ponteiro para arquivo aberto
    bool log_to_file;        // ??? - Se true, escreve no arquivo
    bool log_to_console;     // ??? - Se true, imprime no terminal
    bool use_colors;         // ??? - Cores (só funciona no console)
} LogConfig;

// Enum para os tipos de LOG: DEBUG = 0;...
enum Level_Type{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
    NUM_LEVELS
};

// Struct que contem informações dos niveis de LOG.
typedef struct {
    enum Level_Type type;
    const char* name;
    const char* color;
} LogLevel;

// Status de quantas vezes foi requisitado cada LOG.
typedef struct {
    int counts[NUM_LEVELS];
} LogStats;


// Funções de configurações do logger.
void logger_init(const char *filename);
void logger_close(void);
void logger_set_console(bool enable);
void logger_set_file(bool enable);


// Função Helper para formatar o log.
void _log_format(LogLevel *log_l, char* message);

// Declação das funções de LOG.
void debug(char* message);
void info(char* message);
void warning(char* message);
void error(char* message);
void critical(char* message);

// Definindo "externs para reutilizar e acessar de fora do escopo"
extern LogConfig config;
extern LogLevel levels[NUM_LEVELS];
extern LogStats stats;
extern Level log_levels[5];

// Função que é chamada para fazer a loggagem.
void logger(enum Level_Type type, char* message);

// Função para desativar cores
void logger_disable_colors();

// Função para exibir o contador por tipo de LOG.
void logger_print_stats();


#endif