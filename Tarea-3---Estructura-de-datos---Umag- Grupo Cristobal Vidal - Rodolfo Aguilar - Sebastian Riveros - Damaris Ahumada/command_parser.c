#include "command_parser.h"
#include "memory_manager.h"
#include "trie.h"           
#include "file_reader.h"   
#include "search_engine.h"  
#include "sequence_processor.h"
#include "query_handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Variable global para almacenar la altura del árbol (m)
static int tree_height = 0;
static NodoTrie* g_trie = NULL;

void display_prompt(void) {
    printf(">");
}

int parse_and_execute(char* input) {
    char command[20];
    char arg1[50];
    char arg2[50];
    int args_read;
    
    // Limpiar buffers
    memset(command, 0, sizeof(command));
    memset(arg1, 0, sizeof(arg1));
    memset(arg2, 0, sizeof(arg2));
    
    // Parsear el input
    args_read = sscanf(input, "%19s %49s %49s", command, arg1, arg2);
    
    // Verificar que empiece con "bio"
    if (strcmp(command, "bio") != 0) {
        printf("Error: Todos los comandos deben comenzar con 'bio'\n");
        return -1;
    }
    
    // Procesar subcomando
    if (args_read < 2) {
        printf("Error: Comando incompleto. Use: bio [start|read|search|max|min|all|exit]\n");
        return -1;
    }
    
    if (strcmp(arg1, "start") == 0) {
        if (args_read < 3) {
            printf("Error: Uso: bio start m\n");
            return -1;
        }
        if (!is_positive_integer(arg2)) {
            printf("Error: 'm' debe ser un número entero positivo\n");
            return -1;
        }
        return execute_bio_start(atoi(arg2));
    }
    else if (strcmp(arg1, "read") == 0) {
        if (args_read < 3) {
            printf("Error: Uso: bio read archivo.txt\n");
            return -1;
        }
        return execute_bio_read(arg2);
    }
    else if (strcmp(arg1, "search") == 0) {
        if (args_read < 3) {
            printf("Error: Uso: bio search GEN\n");
            return -1;
        }
        return execute_bio_search(arg2);
    }
    else if (strcmp(arg1, "max") == 0) {
        return execute_bio_max();
    }
    else if (strcmp(arg1, "min") == 0) {
        return execute_bio_min();
    }
    else if (strcmp(arg1, "all") == 0) {
        return execute_bio_all();
    }
    else if (strcmp(arg1, "exit") == 0) {
        return execute_bio_exit();
    }
    else {
        printf("Error: Comando desconocido: %s\n", arg1);
        return -1;
    }
}

int execute_bio_start(int m) {
    if (m <= 0) {
        printf("Error: La altura del árbol debe ser mayor a 0\n");
        return -1;
    }
    
    tree_height = m;
    int result = create_trie(m);  
    
    if (result == 0) {
        printf("Tree created with height %d\n", m);
    } else {
        printf("Error creating tree\n");
    }
    
    return result;
}

int execute_bio_read(char* filename) {
    if (tree_height == 0) {
        printf("Error: Primero debe ejecutar 'bio start m'\n");
        return -1;
    }
    
    int result = read_sequence_file(filename, tree_height);  
    
    if (result == 0) {
        printf("Sequence S read from file\n");
    } else {
        printf("Error reading sequence from file\n");
    }
    
    return result;
}

int execute_bio_search(char* gen) {
    if (tree_height == 0) {
        printf("Error: Primero debe ejecutar 'bio start m' y 'bio read archivo'\n");
        return -1;
    }
    
    if (!validate_gene_format(gen, tree_height)) {
        printf("Error: El gen debe tener longitud %d y contener solo A,C,G,T\n", tree_height);
        return -1;
    }
    
    return search_gene(gen);  
}

int execute_bio_max(void) {
    if (tree_height == 0) {
        printf("Error: Primero debe ejecutar 'bio start m' y 'bio read archivo'\n");
        return -1;
    }
    
    return find_most_frequent_genes();  
}

int execute_bio_min(void) {
    if (tree_height == 0) {
        printf("Error: Primero debe ejecutar 'bio start m' y 'bio read archivo'\n");
        return -1;
    }
    
    return find_least_frequent_genes();  
}

int execute_bio_all(void) {
    if (tree_height == 0) {
        printf("Error: Primero debe ejecutar 'bio start m' y 'bio read archivo'\n");
        return -1;
    }
    
    return list_all_genes();  
}

int execute_bio_exit(void) {
    printf("Clearing cache and exiting...\n");
    free_trie();  
    exit(0);
    return 0;
}

// Funciones de integración con otros módulos
int create_trie(int m) {
    g_trie = bio_start(m);
    if (g_trie == NULL) {
        return -1;
    }
    
    // Inicializar search_engine
    search_engine_init(g_trie, m);
    return 0;
}

int read_sequence_file(const char* filename, int gene_size) {
    char* sequence = leer_secuencia(filename);
    if (sequence == NULL) {
        return -1;
    }
    
    procesar_y_cargar_trie(g_trie, sequence, gene_size);
    gestionar_free(sequence);
    return 0;
}

int search_gene(const char* gene) {
    handle_bio_search_command(gene);
    return 0;
}

int find_most_frequent_genes(void) {
    handle_bio_max_command();
    return 0;
}

int find_least_frequent_genes(void) {
    handle_bio_min_command();
    return 0;
}

int list_all_genes(void) {
    handle_bio_all_command();
    return 0;
}

void free_trie(void) {
    if (g_trie != NULL) {
        bio_exit(g_trie);
        g_trie = NULL;
    }
    search_engine_cleanup();
}

// Funciones de validación
int validate_gene_format(char* gen, int expected_length) {
    if ((int)strlen(gen) != expected_length) {
        return 0;
    }
    return is_valid_dna_sequence(gen);
}

int is_valid_dna_sequence(char* sequence) {
    for (int i = 0; sequence[i] != '\0'; i++) {
        char c = toupper(sequence[i]);
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            return 0;
        }
    }
    return 1;
}

int is_positive_integer(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return atoi(str) > 0;
}
