#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "trie.h"
#include <stddef.h>

/*
  Interfaz del módulo search_engine (Integrante 3).
  
  Este módulo trabaja con las estructuras NodoTrie y ListaInt
  definidas por el Integrante 1.
*/

/* Inicializa el search engine con el trie ya creado y el tamaño de los genes (m) */
void search_engine_init(NodoTrie *trie_ptr, int gene_size);

/* Libera recursos internos del módulo */
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