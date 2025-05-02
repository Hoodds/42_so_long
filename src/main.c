#include "so_long.h"
#include <stdio.h>

int	main(void)
{
	t_game	game;
	int		i;

	// cargar el mapa desde el archivo .ber. hay que hacer marpeta maps
	if (load_map(&game, "./mapa.ber") != 0)
	{
		printf("Error al cargar el mapa\n");
		return (1);
	}

    if (!is_valid_map(&game))
    {
        printf("Mapa inválido\n");
        // liberar memoria antes de salir
        for (int j = 0; j < game.height; j++)
            free(game.map[j]);
        free(game.map);
        return (1);
    }

	printf("Mapa cargado ok. Tamaño: %dx%d\n", game.width, game.height);

	// imprimir el mapa
	i = 0;
	while (game.map[i])
	{
		printf("%s\n", game.map[i]);
		i++;
	}

	// liberar la memoria
	for (int j = 0; j < game.height; j++)
	{
		free(game.map[j]);
	}
	free(game.map);

	return (0);
}
