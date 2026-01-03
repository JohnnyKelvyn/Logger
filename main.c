#include "logger.h"

#include "logger.h"

int main(void) {
    // Inicializa logger com arquivo
    logger_init("pentest.log");
    
    // Configura: console + arquivo simultâneos
    logger_set_console(true);
    logger_set_file(true);
    
    // Simula sessão de pentest
    logger(INFO, "=== PENTEST SESSION START ===");
    logger(DEBUG, "Target: https://example.com");
    logger(INFO, "Running subdomain enumeration...");
    logger(WARNING, "Found deprecated API endpoint");
    logger(ERROR, "Auth bypass attempt failed (WAF)");
    logger(CRITICAL, "XSS vulnerability confirmed!");
    logger(INFO, "=== PENTEST SESSION END ===");
    
    // Exibe estatísticas
    logger_print_stats();
    
    // Cleanup
    logger_close();
    
    return 0;
}