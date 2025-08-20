#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "tests.h"

t_validation_status	get_content_splitted_mock(char *path, char ****content)
{
	int		counter;
    int     fd;
	char	*line;
	
	counter = 0;
	fd = open(path, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		counter++;
		free(line);
	}
	*content = (char ***)malloc(sizeof(char **) * (counter + 1));
	if (!(*content))
		return(ERR_MALLOC_CONTENT);
	(*content)[counter] = NULL;
    close(fd);
    fd = open(path, O_RDONLY);
	counter = 0;
	while ((line = get_next_line(fd)))
	{
		(*content)[counter] = ft_split(line, ' ');
		remove_backslash_n((*content)[counter]);
		free(line);
		counter++;
	}
	close(fd);
	return(VALIDATION_OK);
}

t_validation_status	get_map_matrix_mock(char *path, char ***map, char ***content)
{
	int	index;
	int	index2;
	int	map_height;
	char *line;
    int fd;
	
	index = 0;
	index2 = 0;
	map_height = get_map_content_height(content);
	*map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (!(*map))
		return(ERR_MALLOC_MAP);
    fd = open(path, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (find_map(line))
		{
			free(line);
			index++;
			continue;
		}
		remove_backslash_n2(line);
		(*map)[index2] = ft_strdup(line);
		index++;
		index2++;
		free(line);
	}
	(*map)[index2] = NULL; //aqui tenho o mapa certinho
	if (set_matrix(map) == 	ERR_MALLOC_MAP_AND_CONTENT) //aqui o meu mapa está com as linhas ao final preenchido com espaço até todas as linhas ficarem iguais
		return (ERR_MALLOC_MAP_AND_CONTENT);
	return (VALIDATION_OK);
}


const char *get_status_name(t_validation_status status)
{
    switch (status)
    {
        case VALIDATION_OK: return "VALIDATION_OK";
        case ERR_MISSING_IDENTIFIER: return "ERR_MISSING_IDENTIFIER";
        case ERR_DOUBLE_IDENTIFIER: return "ERR_DOUBLE_IDENTIFIER";
        case ERR_MISSING_TEXTURE_PATH: return "ERR_MISSING_TEXTURE_PATH";
        case ERR_INVALID_TEXTURE_PATH: return "ERR_INVALID_TEXTURE_PATH";
        case ERR_MISSING_COLOR: return "ERR_MISSING_COLOR";
        case ERR_INVALID_RGB: return "ERR_INVALID_RGB";
        case ERR_INVALID_MAP_POSITION: return "ERR_INVALID_MAP_POSITION";
        case ERR_INVALID_MAP_ELEMENT: return "ERR_INVALID_MAP_ELEMENT";
        case ERR_DATA_AFTER_MAP: return "ERR_DATA_AFTER_MAP";
        case ERR_MISSING_MAP: return "ERR_MISSING_MAP";
        case ERR_INVALID_MAP_SIZE: return "ERR_INVALID_MAP_SIZE";
        case ERR_INVALID_MAP_CONTENT: return "ERR_INVALID_MAP_CONTENT";
        case ERR_INVALID_EDGES: return "ERR_INVALID_EDGES";
        case ERR_MULTIPLAYERS: return "ERR_MULTIPLAYERS";
        case ERR_NO_PLAYER: return "ERR_NO_PLAYER";
        case ERR_COPY_MAP: return "ERR_COPY_MAP";
        case ERR_INTER_SPACE: return "ERR_INTER_SPACE";
        case ERR_MAP_OPEN: return "ERR_MAP_OPEN";
        case ERR_MALLOC_CONTENT: return "ERR_MALLOC_CONTENT";
        case ERR_MALLOC_MAP: return "ERR_MALLOC_MAP";
        case ERR_MALLOC_MAP_AND_CONTENT: return "ERR_MALLOC_MAP_AND_CONTENT";
        default: return "UNKNOWN_STATUS";
    }
}