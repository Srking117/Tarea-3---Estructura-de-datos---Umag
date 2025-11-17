#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <stddef.h>

/*
  Interfaz del módulo search_engine (Integrante 3).

  Este módulo mantiene un puntero al trie (creado por Integrante 1)
  y proporciona las funciones:
    - search_engine_init(trie_ptr, gene_size)
    - search_engine_cleanup()
    - bio_search(gene) -> imprime posiciones o -1
    - bio_max() -> imprime genes con max apariciones y sus posiciones
    - bio_min() -> imprime genes con min apariciones y sus posiciones
    - bio_all() -> imprime todos los genes presentes con sus posiciones
    - validate_gene(gene) -> 1 si OK, 0 si no

  NOTA: Este módulo asume que existen en el proyecto las siguientes
  funciones / tipos (definidas por Integrante 1):
    - typedef struct Trie Trie;
    - typedef struct ListInt ListInt;    // lista de enteros (posiciones)
    - ListInt* trie_get_positions(Trie *t, const char *gene);
         // devuelve NULL si el gen no existe, o puntero a lista (posiciones)
    - size_t list_int_size(const ListInt *lst);
    - int list_int_get(const ListInt *lst, size_t idx); // devuelve el elemento idx
    - void list_int_free(ListInt *lst); // si corresponde
    - void trie_iterate_all(Trie *t, void (*cb)(const char *gene, const ListInt *pos, void *ctx), void *ctx);
         // itera sobre todos los genes presentes; cb recibe gene (c-string) y lista de posiciones (const)
  Si las funciones tienen nombres distintos, ajusta las llamadas en search_engine.c.
*/

typedef struct Trie Trie;
typedef struct ListInt ListInt;

/* Inicializa el search engine con el trie ya creado y el tamaño de los genes (m) */
void search_engine_init(Trie *trie_ptr, int gene_size);

/* Libera recursos internos del módulo (no libera el trie en sí; bio exit debe hacerlo quien corresponda) */
void search_engine_cleanup(void);

/* Valida que el gen tenga longitud m y solo contenga A,C,G,T (mayusculas) */
int validate_gene(const char *gene);

/* Imprime las posiciones del gen o "-1" si no existe.
   Retorna 0 si gene válido (aunque -1 impreso), -1 si gene inválido */
int bio_search(const char *gene);

/* Imprime los genes con mayor numero de apariciones y sus posiciones */
void bio_max(void);

/* Imprime los genes con menor numero de apariciones (>=1) y sus posiciones */
void bio_min(void);

/* Imprime todos los genes presentes con sus posiciones */
void bio_all(void);

#endif /* SEARCH_ENGINE_H */
