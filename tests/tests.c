#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "../src/cub3d.h"

void	redirect_all_stdout_echo(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

char ***get_content(const char *path)
{
	int     fd;
	int     counter = 0;
	char    *line;
	char    ***content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return NULL;

	while ((line = get_next_line(fd)))
	{
		counter++;
		free(line);
	}
	close(fd);
	content = malloc(sizeof(char **) * (counter + 1));
	if (!content)
		return NULL;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return NULL;

	counter = 0;
	while ((line = get_next_line(fd)))
	{
		content[counter] = ft_split(line, ' ');
		remove_backslash_n(content[counter]);
		free(line);
		counter++;
	}
	content[counter] = NULL;
	close(fd);
	return content;
}


//--Validações

Test(check_missing_identifier, missing_identifier_should_print_error_msg, .init=redirect_all_stdout_echo)
{
	char ***content = get_content("resources/invalid_maps/textures_missing.cub");
	char *error_msg;

	check_missing_identifier(content);
	fflush(stdout);


	cr_assert_not(result, "Deveria retornar false");

	
}
