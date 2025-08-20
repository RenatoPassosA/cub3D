#ifndef TESTS_H
#define TESTS_H

#include "../src/cub3d.h"
#include "../src/parser/parser.h"

t_validation_status	get_content_splitted_mock(char *path, char ****content);
t_validation_status	get_map_matrix_mock(char *path, char ***map, char ***content);
const char *get_status_name(t_validation_status status);

#endif