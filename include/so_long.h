#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "libft.h"
# include "MLX42/MLX42.h"

// la estructura tiene que ser un string de strings => **map
// debe saber la altura y la anchura del rectangulo

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;
	mlx_t	*mlx;		// puntero a la ventana
	mlx_image_t *img;	// puntero a la imagen
	int		player_x;   // pos X del jugador
	int		player_y;   // pos Y del jugador
	int		moves;      // contador de movimientos
}	t_game;

char	*read_file(const char *filename);
int	load_map(t_game *game, const char *filename);
int	is_valid_map(t_game *game);

#endif