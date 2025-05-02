#include "so_long.h"
#include <stdio.h>
#include "MLX42/MLX42.h"
#include <stdint.h> // para uint32_t

// Tamaño de cada tile en píxeles
#define TILE_SIZE 64

void	draw_map(t_game *game)
{
    int			x, y, i, j;
    mlx_image_t	*img;

    img = mlx_new_image(game->mlx, game->width * TILE_SIZE, game->height * TILE_SIZE);
    if (!img)
        return;
    for (i = 0; i < game->height; i++)
    {
        for (j = 0; j < game->width; j++)
        {
            uint32_t color = 0x000000FF; // negro por defecto
            if (game->map[i][j] == '1')
                color = 0x808080FF; // gris
            else if (game->map[i][j] == 'P')
                color = 0x0000FFFF; // azul
            else if (game->map[i][j] == 'C')
                color = 0xFFFF00FF; // amarillo
            else if (game->map[i][j] == 'E')
                color = 0x00FF00FF; // verde

            for (y = 0; y < TILE_SIZE; y++)
                for (x = 0; x < TILE_SIZE; x++)
                    mlx_put_pixel(img, j * TILE_SIZE + x, i * TILE_SIZE + y, color);
        }
    }
    mlx_image_to_window(game->mlx, img, 0, 0);
    game->img = img;
}

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

    game.mlx = mlx_init(game.width * TILE_SIZE, game.height * TILE_SIZE, "so_long", false);
    if (!game.mlx)
    {
        printf("Error al iniciar MLX42\n");
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

    draw_map(&game);

    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);

    for (int j = 0; j < game.height; j++)
    {
        free(game.map[j]);
    }
    free(game.map);

    return (0);
}
