#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>

typedef struct NodoLista {
    int posicion;
    struct NodoLista* siguiente;
} NodoLista;

typedef NodoLista* ListaInt;

typedef struct NodoTrie {
    // Punteros a hijos para nodos internos 
    struct NodoTrie* hijoA;
    struct NodoTrie* hijoC;
    struct NodoTrie* hijoG;
    struct NodoTrie* hijoT;

    // Lista de posiciones para nodos hoja 
    ListaInt pos; 
} NodoTrie;

NodoTrie* bio_start(int m);
void bio_exit(NodoTrie* raiz);

#endif
