#include "query_handler.h"
#include "search_engine.h"
#include <stdio.h>
#include <string.h>

/* Estas funciones son simples wrappers que hacen validaciones
   de formato extra (si es necesario) y llaman a search_engine. */

void handle_bio_search_command(const char *arg)
{
    if (arg == NULL) {
        printf("Error: no gene provided\n");
        return;
    }
    /* arg debe ya venir en mayusculas; si el parser permite minusculas,
       hay que convertir a mayusculas aquí. */
    /* convertimos in-place a mayusculas */
    {
        size_t i;
        size_t len = strlen(arg);
        for (i = 0; i < len; i++) {
            /* forzar mayuscula */
            char c = arg[i];
            if (c >= 'a' && c <= 'z') {
                ((char *)arg)[i] = (char)(c - ('a' - 'A'));
            }
        }
    }

    if (!validate_gene(arg)) {
        /* Invalid format -> segun enunciado: devolver error de validacion.
           Aquí devolvemos un mensaje y no hacemos la busqueda. */
        printf("Error: invalid gene format. Only A,C,G,T and correct length allowed\n");
        return;
    }
    bio_search(arg);
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
