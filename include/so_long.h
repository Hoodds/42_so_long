#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "libft.h"

// la estructura tiene que ser un string de strings => **map
// debe saber la altura y la anchura del rectangulo

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;
}	t_game;

char	*read_file(const char *filename);
int	load_map(t_game *game, const char *filename);
int	is_valid_map(t_game *game);

#endif