#ifndef SEQUENCE_PROCESSOR_H
#define SEQUENCE_PROCESSOR_H

#include "trie.h" 

/*
    Esta funcion se encarga de procesar la secuencia S completa,
    extraer todos los genes de tamaño 'm' y guardar sus posiciones
    en el árbol trie.
 */
void agregar_posicion_a_lista(ListaInt* lista_cabeza, int posicion_a_guardar);
void procesar_y_cargar_trie(NodoTrie* raiz, const char* secuencia_S, int tamano_gen);

#endif