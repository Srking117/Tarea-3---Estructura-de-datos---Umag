# Detección automática de sistema operativo
ifeq ($(OS),Windows_NT)
    CC = gcc
    EXEC = bio.exe
    RM = del
else
    CC = gcc
    EXEC = bio
    RM = rm -f
endif

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99 -g
SOURCES = main.c command_parser.c trie.c file_reader.c search_engine.c memory_manager.c sequence_processor.c query_handler.c
OBJECTS = $(SOURCES:.c=.o)

# Target principal
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

# Reglas de compilación para cada archivo
main.o: main.c command_parser.h
	$(CC) $(CFLAGS) -c main.c

command_parser.o: command_parser.c command_parser.h trie.h file_reader.h search_engine.h
	$(CC) $(CFLAGS) -c command_parser.c


trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

file_reader.o: file_reader.c file_reader.h
	$(CC) $(CFLAGS) -c file_reader.c

search_engine.o: search_engine.c search_engine.h
	$(CC) $(CFLAGS) -c search_engine.c

memory_manager.o: memory_manager.c memory_manager.h
	$(CC) $(CFLAGS) -c memory_manager.c

sequence_processor.o: sequence_processor.c sequence_processor.h
	$(CC) $(CFLAGS) -c sequence_processor.c

query_handler.o: query_handler.c query_handler.h
	$(CC) $(CFLAGS) -c query_handler.c

# Limpieza
clean:
	$(RM) $(OBJECTS) $(EXEC)

# Instalación 
install: $(EXEC)
	@echo "Program compiled successfully: $(EXEC)"

# Ayuda
help:
	@echo "Available targets:"
	@echo "  make           - Compile the program"
	@echo "  make clean     - Remove object files and executable"
	@echo "  make install   - Compile and show success message"
	@echo "  make help      - Show this help message"

.PHONY: clean install help