#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

// funcion para leer el mapa
#define BUFFER_SIZE 1024

char	*read_file(const char *filename)
{
	int		fd; // file descriptor que devuelve open
	int		bytes;  // bytes leidos
	char	*content;   // string final con todo el archivo
	char	tmp[BUFFER_SIZE + 1];   // string buffer temporal. como read no pone '\0' ponemos un byte mas

    // abre el archivo en modo lectura, devuelve NULL si falla
    fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);

	content = NULL;

    // lee el archivo en bloques de BUFFER_SIZE
    // y almacena el contenido en content
    // si content es NULL, se asigna el primer bloque
	while ((bytes = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[bytes] = '\0'; // al final del string leido en tmp se añade '\0'

		if (!content)
			content = ft_strdup(tmp);
		else
		{
			// guardamos el puntero original en old.
			// reservamos espacio para el nuevo string (tamaño actual + nuevo + '\0').
			char *old = content;
			content = malloc(ft_strlen(old) + ft_strlen(tmp) + 1); // +1 para el '\0'
			if (!content)
				return (NULL);

			ft_strlcpy(content, old, ft_strlen(old) + 1);  // Usamos ft_strlcpy para copiar old
			ft_strlcat(content, tmp, ft_strlen(content) + ft_strlen(tmp) + 1);  // Usamos ft_strlcat para concatenar tmp

			free(old);
		}
	}
	close(fd);
	return (content);
}


// funcion para cargar el mapa en la struct
int	load_map(t_game *game, const char *filename)
{
	char	*content;

    // llama a read_file y lee el contenoido completo, retorna null si falla
	content = read_file(filename);
	if (!content)
		return (1);

    // divide el contenido en líneas usando '\n' como separador
	game->map = ft_split(content, '\n');

    // ya no se necesita el string completo, se libera
	free(content);

	// si falla el split (memoria), error
	if (!game->map)
		return (1);

	// calcula la altura
	game->height = 0;
	while (game->map[game->height])
		game->height++;

    // calcula el ancho
	game->width = ft_strlen(game->map[0]);

	return (0);
}

int	is_valid_map(t_game *game)
{
    int	player = 0, exit = 0, collect = 0;
    int	i, j;

    // Comprobar rectangulo
    for (i = 0; i < game->height; i++)
        if ((int)ft_strlen(game->map[i]) != game->width)
            return (0);

    // Comprobar paredes arriba y abajo
    for (j = 0; j < game->width; j++)
        if (game->map[0][j] != '1' || game->map[game->height - 1][j] != '1')
            return (0);

    // Comprobar laterales y caracteres validos
    for (i = 0; i < game->height; i++)
    {
        if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
            return (0);
        for (j = 0; j < game->width; j++)
        {
            if (game->map[i][j] == 'P')
                player++;
            else if (game->map[i][j] == 'E')
                exit++;
            else if (game->map[i][j] == 'C')
                collect++;
            else if (game->map[i][j] != '0' && game->map[i][j] != '1')
                return (0);
        }
    }
    // Comprobar cantidad de elementos obligatorios
    if (player != 1 || exit < 1 || collect < 1)
        return (0);
    return (1);
}
