#include "sequence_processor.h" 
#include "trie.h"               
#include "memory_manager.h"     
#include <string.h>
#include <stdio.h>
void agregar_posicion_a_lista(ListaInt* lista_cabeza, int posicion_a_guardar) 
{
    NodoLista* nuevo_eslabon = (NodoLista*)gestionar_malloc(sizeof(NodoLista));
    // Rellenamos el eslabon.
    nuevo_eslabon->posición = posicion_a_guardar; 
    // Añadimos el eslabón al inicioo de la lista
    nuevo_eslabon->siguiente = *lista_cabeza; 
    *lista_cabeza = nuevo_eslabon;
}
void procesar_y_cargar_trie(NodoTrie* raiz, const char* secuencia_S, int tamano_gen) 
{
    int longitud_total = strlen(secuencia_S);
    if (longitud_total < tamano_gen) 
    {
        return; 
    }
    printf("Procesando secuencia de %d letras para genes de tamaño %d\n", longitud_total, tamano_gen);
    for (int i = 0; i <= longitud_total - tamano_gen; i++) 
    {
        NodoTrie* nodo_actual = raiz; 
        for (int j = 0; j < tamano_gen; j++) 
        {
            char letra_actual = secuencia_S[i + j]; 
            switch (letra_actual) 
            {
                case 'A': nodo_actual = nodo_actual->hijoA; break;
                case 'C': nodo_actual = nodo_actual->hijoC; break;
                case 'G': nodo_actual = nodo_actual->hijoG; break;
                case 'T': nodo_actual = nodo_actual->hijoT; break;
                default:
                    printf("Error: Carácter inválido '%c' en la secuencia.\n", letra_actual);
                    return;
            }
            if (nodo_actual == NULL) 
            {
                printf("Error: El árbol no fue creado correctamente.\n");
                return;
            }
        } 
        agregar_posicion_a_lista( &(nodo_actual->pos), i ); 
        printf("DEBUG: Gen en pos %d guardado en la hoja.\n", i); 
    } 
    printf("Carga de genes completada.\n");
}