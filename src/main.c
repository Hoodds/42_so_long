#include "so_long.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
    t_game	game;
    int		i;

    if (argc != 2)
    {
        printf("Uso: %s <mapa.ber>\n", argv[0]);
        return (1);
    }

    if (load_map(&game, argv[1]) != 0)
    {
        printf("Error al cargar el mapa\n");
        return (1);
    }

    if (!is_valid_map(&game))
    {
        printf("Mapa inválido\n");
        for (int j = 0; j < game.height; j++)
            free(game.map[j]);
        free(game.map);
        return (1);
    }

    printf("Mapa cargado ok. Tamaño: %dx%d\n", game.width, game.height);

    i = 0;
    while (game.map[i])
    {
        printf("%s\n", game.map[i]);
        i++;
    }

    for (int j = 0; j < game.height; j++)
    {
        free(game.map[j]);
    }
    free(game.map);

    return (0);
}
