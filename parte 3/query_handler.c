#include "query_handler.h"
#include "search_engine.h"
#include <stdio.h>
#include <string.h>

/* Estas funciones son simples wrappers que hacen validaciones
   de formato extra (si es necesario) y llaman a search_engine. */

void handle_bio_search_command(const char *arg)
{
    char *gene_upper;
    size_t i;
    size_t len;
    
    if (arg == NULL) {
        printf("Error: no gene provided\n");
        return;
    }
    
    /* Crear una copia del argumento para convertir a mayúsculas */
    len = strlen(arg);
    gene_upper = (char *)malloc((len + 1) * sizeof(char));
    if (gene_upper == NULL) {
        printf("Error: memory allocation failed\n");
        return;
    }
    
    /* Copiar y convertir a mayúsculas */
    for (i = 0; i < len; i++) {
        char c = arg[i];
        if (c >= 'a' && c <= 'z') {
            gene_upper[i] = (char)(c - ('a' - 'A'));
        } else {
            gene_upper[i] = c;
        }
    }
    gene_upper[len] = '\0';
    
    /* Validar formato */
    if (!validate_gene(gene_upper)) {
        printf("Error: invalid gene format. Only A,C,G,T and correct length allowed\n");
        free(gene_upper);
        return;
    }
    
    /* Realizar búsqueda */
    bio_search(gene_upper);
    
    free(gene_upper);
}

void handle_bio_max_command(void)
{
    bio_max();
}

void handle_bio_min_command(void)
{
    bio_min();
}

void handle_bio_all_command(void)
{
    bio_all();
}