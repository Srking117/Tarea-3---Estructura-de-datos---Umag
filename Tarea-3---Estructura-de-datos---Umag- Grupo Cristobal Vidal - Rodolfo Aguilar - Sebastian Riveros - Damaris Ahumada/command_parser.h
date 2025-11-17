#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#define MAX_INPUT_LENGTH 100
#define MAX_FILENAME_LENGTH 50
#define MAX_GENE_LENGTH 10

// Funciones principales de parsing y ejecución
int parse_and_execute(char* input);
void display_prompt(void);

// Funciones de ejecución de comandos específicos
int execute_bio_start(int m);
int execute_bio_read(char* filename);
int execute_bio_search(char* gen);
int execute_bio_max(void);
int execute_bio_min(void);
int execute_bio_all(void);
int execute_bio_exit(void);

// Funciones de validación
int validate_gene_format(char* gen, int expected_length);
int is_valid_dna_sequence(char* sequence);
int is_positive_integer(char* str);

// Funciones de integración con otros módulos
int create_trie(int m);
int read_sequence_file(const char* filename, int gene_size);
int search_gene(const char* gene);
int find_most_frequent_genes(void);
int find_least_frequent_genes(void);
int list_all_genes(void);
void free_trie(void);

#endif