# 42_so_long
This repository contains my aproach to so_long project at 42 School


ESTRUCTURA

so_long/
├── MLX42/              # Librería MLX42 que me la ha recomendado narrospi en lugar de miniLibX
├── mapa.ber            # Archivo de mapa
├── src/
│   ├── main.c
│   ├── map.c           # Leer y cargar el mapa
│   └── utils.c
├── include/
│   ├── so_long.h
│   └── (otros).h
├── libft/
├── .gitmodules
├── README.md
├── Makefile


COMO DEBE SER EL MAPA

El mapa debe tener una salida, al menos un objeto y una posición inicial.
El mapa debe ser rectangular.
El mapa deberá estar cerrado/rodeado de muros, en caso contrario el programa deberá devolver un error.
Tienes que comprobar si hay un camino válido en el mapa.
Debes poder procesar cualquier tipo de mapa, siempre y cuando respete las anteriores normas.
En caso de fallos de configuración de cualquier tipo encontrados en el archivo, el programa debe terminar correctamente y devolver Error\n” seguido de un mensaje explícito de tu elección.