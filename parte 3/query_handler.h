#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

/* Funciones para integrar con main.c / parser de comandos.
   query_handler interpreta las instrucciones tipo:
     >bio search <GEN>
     >bio max
     >bio min
     >bio all
   y llama al search_engine.
*/

void handle_bio_search_command(const char *arg); /* arg es el gen (sin espacios) */
void handle_bio_max_command(void);
void handle_bio_min_command(void);
void handle_bio_all_command(void);

#endif /* QUERY_HANDLER_H */
