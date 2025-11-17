#include "search_engine.h"
#include "memory_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Variables estáticas internas */
static NodoTrie *g_trie = NULL;
static int g_gene_size = 0;

void search_engine_init(NodoTrie *trie_ptr, int gene_size)
{
    g_trie = trie_ptr;
    g_gene_size = gene_size;
}

void search_engine_cleanup(void)
{
    g_trie = NULL;
    g_gene_size = 0;
}

int validate_gene(const char *gene)
{
    size_t len;
    size_t i;
    if (gene == NULL) {
        return 0;
    }
    len = strlen(gene);
    if ((int)len != g_gene_size) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = gene[i];
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            return 0;
        }
    }
    return 1;
}

/* Helper: obtiene la hoja correspondiente al gen en el trie */
static NodoTrie* get_leaf_for_gene(NodoTrie *raiz, const char *gene)
{
    NodoTrie *actual = raiz;
    int i;
    
    if (raiz == NULL || gene == NULL) {
        return NULL;
    }
    
    for (i = 0; i < g_gene_size; i++) {
        char c = gene[i];
        
        if (actual == NULL) {
            return NULL;
        }
        
        switch(c) {
            case 'A':
                actual = actual->hijoA;
                break;
            case 'C':
                actual = actual->hijoC;
                break;
            case 'G':
                actual = actual->hijoG;
                break;
            case 'T':
                actual = actual->hijoT;
                break;
            default:
                return NULL;
        }
    }
    
    return actual;
}

/* Helper: cuenta elementos en una lista */
static int count_list(ListaInt lista)
{
    int count = 0;
    NodoLista *actual = lista;
    
    while (actual != NULL) {
        count++;
        actual = actual->siguiente;
    }
    
    return count;
}

/* Helper: imprime lista de posiciones en el formato "p0 p1 p2..." */
static void print_positions(ListaInt lista)
{
    NodoLista *actual = lista;
    int first = 1;
    
    if (lista == NULL) {
        printf("-1\n");
        return;
    }
    
    while (actual != NULL) {
        if (!first) {
            printf(" ");
        }
        printf("%d", actual->posicion);
        first = 0;
        actual = actual->siguiente;
    }
    printf("\n");
}

int bio_search(const char *gene)
{
    NodoTrie *hoja;
    
    if (!validate_gene(gene)) {
        return -1;
    }
    
    if (g_trie == NULL) {
        printf("Error: trie not initialized\n");
        return -1;
    }
    
    hoja = get_leaf_for_gene(g_trie, gene);
    
    if (hoja == NULL || hoja->pos == NULL) {
        printf("-1\n");
        return 0;
    }
    
    print_positions(hoja->pos);
    return 0;
}

/* Estructura para construir el gene string durante la iteración */
typedef struct {
    char *gene_buffer;
    int current_depth;
    int max_depth;
    void (*user_callback)(const char *gene, ListaInt pos, void *user_ctx);
    void *user_ctx;
} IterateContext;

/* Función recursiva para iterar sobre todo el árbol */
static void iterate_recursive(NodoTrie *nodo, IterateContext *ctx)
{
    if (nodo == NULL) {
        return;
    }
    
    /* Si llegamos a una hoja (profundidad máxima) */
    if (ctx->current_depth == ctx->max_depth) {
        /* Llamar al callback del usuario con el gen actual */
        ctx->gene_buffer[ctx->current_depth] = '\0';
        ctx->user_callback(ctx->gene_buffer, nodo->pos, ctx->user_ctx);
        return;
    }
    
    /* Explorar hijo A */
    if (nodo->hijoA != NULL) {
        ctx->gene_buffer[ctx->current_depth] = 'A';
        ctx->current_depth++;
        iterate_recursive(nodo->hijoA, ctx);
        ctx->current_depth--;
    }
    
    /* Explorar hijo C */
    if (nodo->hijoC != NULL) {
        ctx->gene_buffer[ctx->current_depth] = 'C';
        ctx->current_depth++;
        iterate_recursive(nodo->hijoC, ctx);
        ctx->current_depth--;
    }
    
    /* Explorar hijo G */
    if (nodo->hijoG != NULL) {
        ctx->gene_buffer[ctx->current_depth] = 'G';
        ctx->current_depth++;
        iterate_recursive(nodo->hijoG, ctx);
        ctx->current_depth--;
    }
    
    /* Explorar hijo T */
    if (nodo->hijoT != NULL) {
        ctx->gene_buffer[ctx->current_depth] = 'T';
        ctx->current_depth++;
        iterate_recursive(nodo->hijoT, ctx);
        ctx->current_depth--;
    }
}

/* Helper: itera sobre todos los genes del trie */
static void iterate_all_genes(NodoTrie *raiz, int gene_size, 
                              void (*callback)(const char *gene, ListaInt pos, void *ctx), 
                              void *user_ctx)
{
    IterateContext ctx;
    
    if (raiz == NULL || gene_size <= 0) {
        return;
    }
    
    ctx.gene_buffer = (char *)gestionar_malloc((gene_size + 1) * sizeof(char));
    if (ctx.gene_buffer == NULL) {
        return;
    }
    
    ctx.current_depth = 0;
    ctx.max_depth = gene_size;
    ctx.user_callback = callback;
    ctx.user_ctx = user_ctx;
    
    iterate_recursive(raiz, &ctx);
    
    gestionar_free(ctx.gene_buffer);
}

/* Estructura de contexto para max/min */
typedef struct {
    int current_max;
    int current_min;
    int first;
} MaxMinCtx;

/* Callback para encontrar max */
static void cb_max(const char *gene, ListaInt pos, void *vctx)
{
    (void)gene;  // Marcar parámetro como usado para eliminar warning
    MaxMinCtx *ctx = (MaxMinCtx *)vctx;
    int count = count_list(pos);
    
    if (ctx->first) {
        ctx->current_max = count;
        ctx->first = 0;
    } else {
        if (count > ctx->current_max) {
            ctx->current_max = count;
        }
    }
}

/* Estructura para imprimir genes con frecuencia específica */
typedef struct {
    int target;
} PrintCtx;

/* Callback para imprimir si coincide con target */
static void cb_print_if_target(const char *gene, ListaInt pos, void *vctx)
{
    PrintCtx *pctx = (PrintCtx *)vctx;
    int count = count_list(pos);
    NodoLista *actual;
    int first;
    
    if (count == pctx->target && count > 0) {
        printf("%s", gene);
        actual = pos;
        first = 1;
        while (actual != NULL) {
            if (!first) {
                printf(" %d", actual->posicion);
            } else {
                printf(" %d", actual->posicion);
                first = 0;
            }
            actual = actual->siguiente;
        }
        printf("\n");
    }
}

void bio_max(void)
{
    MaxMinCtx ctx;
    PrintCtx pctx;
    
    if (g_trie == NULL) {
        printf("Error: trie not initialized\n");
        return;
    }
    
    ctx.current_max = 0;
    ctx.first = 1;
    
    /* Primera pasada: hallar max */
    iterate_all_genes(g_trie, g_gene_size, cb_max, &ctx);
    
    if (ctx.first) {
        /* No hay genes */
        return;
    }
    
    pctx.target = ctx.current_max;
    
    /* Segunda pasada: imprimir todos con count == max */
    iterate_all_genes(g_trie, g_gene_size, cb_print_if_target, &pctx);
}

/* Callback para encontrar min */
static void cb_min(const char *gene, ListaInt pos, void *vctx)
{
    (void)gene;  // Marcar parámetro como usado para eliminar warning
    MaxMinCtx *ctx = (MaxMinCtx *)vctx;
    int count = count_list(pos);
    
    if (count == 0) {
        return;
    }
    
    if (ctx->first) {
        ctx->current_min = count;
        ctx->first = 0;
    } else {
        if (count < ctx->current_min) {
            ctx->current_min = count;
        }
    }
}

void bio_min(void)
{
    MaxMinCtx ctx;
    PrintCtx pctx;
    
    if (g_trie == NULL) {
        printf("Error: trie not initialized\n");
        return;
    }
    
    ctx.current_min = 0;
    ctx.first = 1;
    
    /* Primera pasada: hallar min */
    iterate_all_genes(g_trie, g_gene_size, cb_min, &ctx);
    
    if (ctx.first) {
        /* No hay genes con apariciones */
        return;
    }
    
    pctx.target = ctx.current_min;
    
    /* Segunda pasada: imprimir todos con count == min */
    iterate_all_genes(g_trie, g_gene_size, cb_print_if_target, &pctx);
}

/* Callback para imprimir todos los genes */
static void cb_print_all(const char *gene, ListaInt pos, void *vctx)
{
    (void)vctx;  // Marcar parámetro como usado para eliminar warning
    int count = count_list(pos);
    NodoLista *actual;
    int first;
    
    if (count == 0) {
        return;
    }
    
    printf("%s", gene);
    actual = pos;
    first = 1;
    while (actual != NULL) {
        if (!first) {
            printf(" %d", actual->posicion);
        } else {
            printf(" %d", actual->posicion);
            first = 0;
        }
        actual = actual->siguiente;
    }
    printf("\n");
}

void bio_all(void)
{
    if (g_trie == NULL) {
        printf("Error: trie not initialized\n");
        return;
    }
    
    iterate_all_genes(g_trie, g_gene_size, cb_print_all, NULL);
}
