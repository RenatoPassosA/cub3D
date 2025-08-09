#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "../src/cub3d.h"

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