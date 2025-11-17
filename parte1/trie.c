#include "trie.h"
#include "memory_manager.h"
#include <stdio.h>

static NodoTrie* crear_nodo() {
    // Usamos el gestor de memoria
    NodoTrie* nodo = (NodoTrie*)gestionar_malloc(sizeof(NodoTrie));
    
    nodo->hijoA = NULL;
    nodo->hijoC = NULL;
    nodo->hijoG = NULL;
    nodo->hijoT = NULL;
    nodo->pos = NULL; // Lista vacía
    
    return nodo;
}

static NodoTrie* crear_nodos_recursivo(int profundidad_actual, int m_maxima) {
    
    NodoTrie* nuevo_nodo = crear_nodo();
    if (profundidad_actual < m_maxima) 
    {
        nuevo_nodo->hijoA = crear_nodos_recursivo(profundidad_actual + 1, m_maxima);
        nuevo_nodo->hijoC = crear_nodos_recursivo(profundidad_actual + 1, m_maxima);
        nuevo_nodo->hijoG = crear_nodos_recursivo(profundidad_actual + 1, m_maxima);
        nuevo_nodo->hijoT = crear_nodos_recursivo(profundidad_actual + 1, m_maxima);
    }
    return nuevo_nodo;
}

static void eliminar_lista(ListaInt lista) {
    while (lista != NULL) {
        NodoLista* temp = lista;
        lista = lista->siguiente;
        gestionar_free(temp); // Usa tu gestor
    }
}

static void eliminar_arbol_recursivo(NodoTrie* nodo) {
    if (nodo == NULL) {
        return;
    }
    eliminar_arbol_recursivo(nodo->hijoA);
    eliminar_arbol_recursivo(nodo->hijoC);
    eliminar_arbol_recursivo(nodo->hijoG);
    eliminar_arbol_recursivo(nodo->hijoT);
    
    eliminar_lista(nodo->pos);

    //Destruir nodo actual
    gestionar_free(nodo);
}

NodoTrie* bio_start(int m) {
    // La raíz es un nodo interno en profundidad 0.
    NodoTrie* raiz = crear_nodo();

    if (m > 0) 
    {
        // Crear los 4 subárboles principales (nivel 1)
        raiz->hijoA = crear_nodos_recursivo(1, m);
        raiz->hijoC = crear_nodos_recursivo(1, m);
        raiz->hijoG = crear_nodos_recursivo(1, m);
        raiz->hijoT = crear_nodos_recursivo(1, m);
    }
    
    printf("Arbol creado con altura: %d\n", m);
    return raiz;
}

void bio_exit(NodoTrie* raiz) {
    printf("Limpiando cache y saliendo..\n");
    eliminar_arbol_recursivo(raiz);
}
