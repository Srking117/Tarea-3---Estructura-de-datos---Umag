#include "file_reader.h"
#include "memory_manager.h" 
#include <stdio.h>
#include <stdlib.h> 
char* leer_secuencia(const char* nombre_archivo)
{
    int caracter_leido;
    char* secuencia = NULL;
    size_t longitud_secuencia = 0; 
    size_t i = 0;
    FILE *p = fopen(nombre_archivo, "r");
    if (!p)
    {
        printf("El archivo no se pudo abrir\n");
        return NULL;
    }
    //contar caracteres leidos 
    while ((caracter_leido = fgetc(p)) != EOF)
    {
        if (caracter_leido == '\n') 
        {
            break; 
        } 
        longitud_secuencia++;
    }
    // ya no necesitamos a p
    fclose(p); 
    secuencia = (char*)gestionar_malloc(longitud_secuencia + 1); // +1 para el \0
    FILE *p_ = fopen(nombre_archivo, "r");
    if (!p_) 
    {
        printf("Error: No se pudo re-abrir el archivo.\n");
        gestionar_free(secuencia);
        return NULL;
    }
    while (i < longitud_secuencia && (caracter_leido = fgetc(p_)) != EOF) 
    { 
        secuencia[i] = (char)caracter_leido;
        i++;
    }
    secuencia[i] = '\0';
    fclose(p_);
    
    return secuencia;
}