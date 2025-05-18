#include "so_long.h"
#include <stdio.h>
#include "MLX42/MLX42.h"
#include <stdint.h> // para uint32_t

// Tamanyo de cada tile en pix
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

// Encuentra las coordenadas iniciales del jugador
void	find_player(t_game *game)
{
    int i, j;

    for (i = 0; i < game->height; i++)
    {
        for (j = 0; j < game->width; j++)
        {
            if (game->map[i][j] == 'P')
            {
                game->player_x = j;
                game->player_y = i;
                return;
            }
        }
    }
}

// Comprueba si el movimiento es valido
int	is_valid_move(t_game *game, int new_y, int new_x)
{
    // Si es una pared, no podemos movernos
    if (game->map[new_y][new_x] == '1')
        return (0);
    return (1);
}

// Mueve al jugador en la direccio especificada
void	move_player(t_game *game, int dir_y, int dir_x)
{
    int new_y = game->player_y + dir_y;
    int new_x = game->player_x + dir_x;

    // Comprueba si el movimiento es valido
    if (!is_valid_move(game, new_y, new_x))
        return;

    // Si el destino es un coleccionable, recogerlo
    if (game->map[new_y][new_x] == 'C')
        game->map[new_y][new_x] = '0';

    // Si el destino es la salida, comprobar si hemos recogido todos los coleccionables
    if (game->map[new_y][new_x] == 'E')
    {
        // Comprobar si hay ma coleccionables
        for (int i = 0; i < game->height; i++)
            for (int j = 0; j < game->width; j++)
                if (game->map[i][j] == 'C')
                    return; // Hay coleccionables, no podemos salir aun

        printf("¡Has ganado! Movimientos: %d\n", game->moves + 1);
        mlx_close_window(game->mlx);
        return;
    }

    // Actualizar el mapa: borrar la posicion antigua
    game->map[game->player_y][game->player_x] = '0';

    // Actualizar la posicion del jugador
    game->player_x = new_x;
    game->player_y = new_y;

    // Poner al jugador en la nueva posicion
    game->map[game->player_y][game->player_x] = 'P';

    // Incrementar contador de movimientos
    game->moves++;
    printf("Movimientos: %d\n", game->moves);

    // Volver a dibujar el mapa
    mlx_delete_image(game->mlx, game->img);
    draw_map(game);
}

// Callback de teclado
void	key_handler(mlx_key_data_t keydata, void *param)
{
    t_game	*game;

    game = param;
    // Solo procesar teclas cuando se presionan
    if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
        return;

    // Mover segun la tecla
    if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
        move_player(game, -1, 0); // Arriba
    else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
        move_player(game, 1, 0);  // Abajo
    else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
        move_player(game, 0, -1); // Izquierda
    else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
        move_player(game, 0, 1);  // Derecha
    else if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(game->mlx); // Salir con ESC
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

    // Inicializar contador de movimientos
    game.moves = 0;

    // Encontrar posicion inicial del jugador
    find_player(&game);

    printf("Mapa cargado ok. Tamaño: %dx%d\n", game.width, game.height);

    i = 0;
    while (game.map[i])
    {
        printf("%s\n", game.map[i]);
        i++;
    }

    // Registrar el callback de teclado
    mlx_key_hook(game.mlx, &key_handler, &game);

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
