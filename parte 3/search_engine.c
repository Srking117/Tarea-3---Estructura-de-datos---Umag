#include "search_engine.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Se declaran aquí las firmas que esperamos del trie / lista.
   Si las funciones reales tienen otros nombres, solo cambia las declaraciones
   y las llamadas correspondientes. */
extern ListInt* trie_get_positions(Trie *t, const char *gene);
extern size_t list_int_size(const ListInt *lst);
extern int list_int_get(const ListInt *lst, size_t idx);
extern void trie_iterate_all(Trie *t, void (*cb)(const char *gene, const ListInt *pos, void *ctx), void *ctx);

/* Variables estáticas internas */
static Trie *g_trie = NULL;
static int g_gene_size = 0;

void search_engine_init(Trie *trie_ptr, int gene_size)
{
    g_trie = trie_ptr;
    g_gene_size = gene_size;
}

void search_engine_cleanup(void)
{
    /* No liberamos g_trie aquí (lo maneja quien creó el trie).
       Solo limpiamos estado interno. */
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
        /* aceptamos solo mayusculas A C G T */
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            return 0;
        }
    }
    return 1;
}

/* Helper: imprime lista de posiciones en el formato "p0 p1 p2..." */
static void print_positions(const ListInt *lst)
{
    size_t n;
    size_t i;

    if (lst == NULL) {
        /* no hay posiciones */
        printf("-1\n");
        return;
    }

    n = list_int_size(lst);
    if (n == 0) {
        printf("-1\n");
        return;
    }

    for (i = 0; i < n; i++) {
        int val = list_int_get(lst, i);
        if (i > 0) {
            printf(" ");
        }
        printf("%d", val);
    }
    printf("\n");
}

int bio_search(const char *gene)
{
    ListInt *positions;

    if (!validate_gene(gene)) {
        /* indicador de error de formato */
        return -1;
    }

    if (g_trie == NULL) {
        printf("Error: trie not initialized\n");
        return -1;
    }

    positions = trie_get_positions(g_trie, gene);
    if (positions == NULL) {
        /* imprimir -1 (segun enunciado) */
        printf("-1\n");
        return 0;
    }
    print_positions(positions);
    return 0;
}

/* Estructura de contexto para iterar y recolectar info */
typedef struct {
    size_t current_max;
    size_t current_min;
    int first; /* flag para min inicial */
} MaxMinCtx;

/* Callback que usa bio_max para encontrar max */
static void cb_max(const char *gene, const ListInt *pos, void *vctx)
{
    MaxMinCtx *ctx = (MaxMinCtx *)vctx;
    size_t count = list_int_size(pos);

    if (ctx->first) {
        ctx->current_max = count;
        ctx->first = 0;
    } else {
        if (count > ctx->current_max) {
            ctx->current_max = count;
        }
    }
}

/* Callback que imprime genes cuya frecuencia == target */
typedef struct {
    size_t target;
} PrintCtx;

static void cb_print_if_target(const char *gene, const ListInt *pos, void *vctx)
{
    PrintCtx *pctx = (PrintCtx *)vctx;
    size_t count = list_int_size(pos);
    size_t i;
    if (count == pctx->target && count > 0) {
        /* imprimir gene seguido de posiciones */
        printf("%s", gene);
        for (i = 0; i < count; i++) {
            int val = list_int_get(pos, i);
            printf(" %d", val);
        }
        printf("\n");
    }
}

/* Implementacion de bio_max:
   1) iterar sobre todos los genes para determinar el max
   2) iterar otra vez para imprimir todos con frecuencia == max
*/
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

    /* primera pasada: hallar max */
    trie_iterate_all(g_trie, cb_max, &ctx);

    if (ctx.first) {
        /* no hay genes (arbol vacio) */
        return;
    }

    pctx.target = ctx.current_max;

    /* segunda pasada: imprimir todos con count == max */
    trie_iterate_all(g_trie, cb_print_if_target, &pctx);
}

/* --- bio_min --- 
   parecido a bio_max pero buscando el minimo entre genes con apariciones >= 1
   Si hay genes con frecuencia 0 no se consideran (las hojas con lista vacia no cuentan).
*/
static void cb_min(const char *gene, const ListInt *pos, void *vctx)
{
    MaxMinCtx *ctx = (MaxMinCtx *)vctx;
    size_t count = list_int_size(pos);

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

    trie_iterate_all(g_trie, cb_min, &ctx);

    if (ctx.first) {
        /* no hay genes con apariciones (arbol vacio) */
        return;
    }

    pctx.target = ctx.current_min;
    trie_iterate_all(g_trie, cb_print_if_target, &pctx);
}

/* bio_all: iterar e imprimir todos los genes con sus posiciones */
static void cb_print_all(const char *gene, const ListInt *pos, void *vctx)
{
    size_t count = list_int_size(pos);
    size_t i;

    if (count == 0) {
        /* si la lista esta vacia, no imprimimos (segun ejemplo) */
        return;
    }

    printf("%s", gene);
    for (i = 0; i < count; i++) {
        int val = list_int_get(pos, i);
        printf(" %d", val);
    }
    printf("\n");
}

void bio_all(void)
{
    if (g_trie == NULL) {
        printf("Error: trie not initialized\n");
        return;
    }
    trie_iterate_all(g_trie, cb_print_all, NULL);
}
