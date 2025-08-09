#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "./tests.h"

void	redirect_all_stdout_echo(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}


//--Validações

Test(check_missing_identifier, missing_identifier_should_return_ERR_MISSING_IDENTIFIER, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_missing.cub", &content);
	t_validation_status status = check_missing_identifier(content);
	
	cr_assert_eq(status, ERR_MISSING_IDENTIFIER, "Esperava ERR_MISSING_IDENTIFIER, mas recebeu %d", status);

}
