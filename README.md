# Tarea-3---Estructura-de-datos---Umag

Grupo: 
Cristobal Vidal -
Rodolfo Aguilar -
Sebastian Riveros -
Damaris Ahumada

################################################

Nos dividimos el codigo en 4 partes:

Integrante 1 "Rodolfo Aguilar": Estructuras de Datos y Núcleo del Árbol Trie
Responsabilidades:

    Diseñar e implementar las estructuras de datos del árbol trie 4-ario

    Crear las definiciones de Nodo y Hoja según la especificación

    Implementar las funciones básicas de creación y destrucción del árbol

    Gestionar la memoria para las estructuras del árbol

    Implementar la función de limpieza (bio exit)

Archivos principales:

    trie.h, trie.c - Estructuras y funciones del árbol

    memory_manager.c - Gestión de memoria
Integrante 2 "Damaris Ahumada": Carga de Datos y Procesamiento de Secuencias
Responsabilidades:

    Implementar la lectura del archivo de ADN (bio read)

    Desarrollar el algoritmo para extraer todos los genes de tamaño m de la secuencia S

    Implementar la inserción de genes en el árbol trie con sus posiciones

    Validar el formato del archivo de entrada

    Manejar errores de entrada/salida

Archivos principales:

    file_reader.h, file_reader.c

    sequence_processor.h, sequence_processor.c
Integrante 3 "Cristobal Vidal" : Funciones de Búsqueda y Consultas
Responsabilidades:

    Implementar la búsqueda individual de genes (bio search)

    Desarrollar el algoritmo para encontrar el gen más frecuente (bio max)

    Implementar la búsqueda del gen menos frecuente (bio min)

    Crear la función para listar todos los genes (bio all)

    Validar que los genes buscados tengan el formato correcto (solo A,C,G,T)

Archivos principales:

    search_engine.h, search_engine.c

    query_handler.h, query_handler.c
Integrante 4 "Sebastian Riveros": Interfaz y Integración del Sistema
Responsabilidades:

    Implementar el sistema de línea de comandos y parser de instrucciones

    Crear el Makefile para compilación multiplataforma

    Integrar todos los módulos y asegurar su correcto funcionamiento conjunto

    Desarrollar pruebas unitarias y de integración

    Documentación del código y preparación del informe final

Archivos principales:

    main.c - Programa principal

    command_parser.h, command_parser.c

    Makefile


################################################






