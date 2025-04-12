#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char	*read_file(const char *filename)
{
	int		fd;
	int		bytes;
	char	*content;
	char	tmp[BUFFER_SIZE + 1];

    // abre el archivo en modo lectura.devuelve null si falla
    fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);

	content = NULL;

    // lee el archivo en bloques de BUFFER_SIZE
    // y almacena el contenido en content
    // si content es null, se asigna el primer bloque
	while ((bytes = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[bytes] = '\0'; // al funal del string leido en tmp se añade del '\0'		if (!content)
			content = ft_strdup(tmp);ç

        /* ELSE
        Guardamos el puntero original en old.
        Reservamos espacio para el nuevo string (tamaño actual + nuevo + \0).
        Copiamos el contenido anterior.
        Concatenamos lo nuevo.
        Liberamos el contenido antiguo.
        */
		else
		{
			char	*old = content;
			content = malloc(ft_strlen(old) + ft_strlen(tmp) + 1);
			if (!content)
				return (NULL);
			ft_strcpy(content, old);
			ft_strcat(content, tmp);
			free(old);
		}
	}
	close(fd);
	return (content);
}