#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "../cub3d.h"

void	redirect_all_stdout_echo(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

//--Validações

Test(map_validation, invalid_identifier_should_return_false, .init=redirect_all_stdout_echo)
{
	int fd = open("maps/2.cub", O_RDONLY);
	cr_assert_neq(fd, -1, "Falha ao abrir arquivo de teste");

	bool result = validate_map(fd);

	cr_assert_not(result, "Deveria retornar false");

	close(fd);
}
