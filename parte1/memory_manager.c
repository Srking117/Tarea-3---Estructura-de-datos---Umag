#include "memory_manager.h"
#include <stdio.h> 
#include <stdlib.h> 

void* gestionar_malloc(size_t size) 
{
    void* ptr = malloc(size);
    if (ptr == NULL) 
    {
        perror("Error: Falla al asignar memoria");
        exit(EXIT_FAILURE); 
    }
    return ptr;
}

void gestionar_free(void* ptr) 
{
    if (ptr != NULL) 
    {
        free(ptr);
    }
}
