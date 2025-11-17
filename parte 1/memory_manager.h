#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdlib.h>

void* gestionar_malloc(size_t size);
void gestionar_free(void* ptr);

#endif
