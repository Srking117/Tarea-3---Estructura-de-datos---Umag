#include <stdio.h>
#include <stdlib.h>
#include "command_parser.h"

int main() {
    char input[MAX_INPUT_LENGTH];
    
    printf("Bioinformatics Gene Search System\n");
    printf("Available commands:\n");
    printf("  bio start m      - Create tree with height m\n");
    printf("  bio read file    - Read sequence from file\n");
    printf("  bio search GEN   - Search for specific gene\n");
    printf("  bio max          - Find most frequent genes\n");
    printf("  bio min          - Find least frequent genes\n");
    printf("  bio all          - List all genes with positions\n");
    printf("  bio exit         - Exit program\n\n");
    
    while(1) {
        display_prompt();
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Eliminar salto de línea
        input[strcspn(input, "\n")] = 0;
        
        // Procesar comando
        parse_and_execute(input);
    }
    
    return 0;
}