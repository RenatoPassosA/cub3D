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

// ------------------- MISSING IDENTIFIER -------------------

Test(check_missing_identifier, missing_identifier_should_return_ERR_MISSING_IDENTIFIER, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_missing.cub", &content);
	t_validation_status status = check_missing_identifier(content);
	
	cr_assert_eq(status, ERR_MISSING_IDENTIFIER, "Esperava ERR_MISSING_IDENTIFIER, mas recebeu %d", status);
}

Test(check_missing_identifier, empty_file_should_return_ERR_MISSING_IDENTIFIER, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/empty.cub", &content);
	t_validation_status status = check_missing_identifier(content);
	
	cr_assert_eq(status, ERR_MISSING_IDENTIFIER, "Esperava ERR_MISSING_IDENTIFIER, mas recebeu %d", status);
}

Test(check_missing_identifier, no_missing_identifier_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	t_validation_status status = check_missing_identifier(content);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- DOUBLE IDENTIFIER -------------------

Test(check_double_identifier, double_identifier_should_return_ERR_DOUBLE_IDENTIFIER, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/double_identifier.cub", &content);
	t_validation_status status = check_double_identifier(content);
	
	cr_assert_eq(status, ERR_DOUBLE_IDENTIFIER, "Esperava ERR_DOUBLE_IDENTIFIER, mas recebeu %d", status);
}

Test(check_double_identifier, double_identifier2_should_return_ERR_DOUBLE_IDENTIFIER, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/double_identifier2.cub", &content);
	t_validation_status status = check_double_identifier(content);
	
	cr_assert_eq(status, ERR_DOUBLE_IDENTIFIER, "Esperava ERR_DOUBLE_IDENTIFIER, mas recebeu %d", status);
}

Test(check_double_identifier, no_double_identifier_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	t_validation_status status = check_double_identifier(content);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- TEXTURES -------------------

Test(validate_textures, not_xpm_should_return_ERR_INVALID_TEXTURE_PATH, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_not_xpm.cub", &content);
	t_validation_status status = validate_textures(content);
	
	cr_assert_eq(status, ERR_INVALID_TEXTURE_PATH, "Esperava ERR_INVALID_TEXTURE_PATH, mas recebeu %d", status);
}

Test(validate_textures, filetype_missing_should_return_ERR_INVALID_TEXTURE_PATH, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_filetype_missing.cub", &content);
	t_validation_status status = validate_textures(content);

	cr_assert_eq(status, ERR_INVALID_TEXTURE_PATH, "Esperava ERR_INVALID_TEXTURE_PATH, mas recebeu %d", status);
}

Test(validate_textures, texture_no_path_should_return_ERR_MISSING_TEXTURE_PATH, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_no_path.cub", &content);
	t_validation_status status = validate_textures(content);
	
	cr_assert_eq(status, ERR_MISSING_TEXTURE_PATH, "Esperava ERR_MISSING_TEXTURE_PATH, mas recebeu %s", get_status_name(status));
}

Test(validate_textures, texture_no_complete_path_should_return_ERR_INVALID_TEXTURE_PATH, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_invalid.cub", &content);
	t_validation_status status = validate_textures(content);
	
	cr_assert_eq(status, ERR_INVALID_TEXTURE_PATH, "Esperava ERR_MISSING_TEXTURE_PATH, mas recebeu %s", get_status_name(status));
}

Test(validate_textures, texture_no_complete_path2_should_return_ERR_INVALID_TEXTURE_PATH, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/textures_dir.cub", &content);
	t_validation_status status = validate_textures(content);
	
	cr_assert_eq(status, ERR_INVALID_TEXTURE_PATH, "Esperava ERR_MISSING_TEXTURE_PATH, mas recebeu %s", get_status_name(status));
}

Test(validate_textures, valid_path_and_filetype_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	t_validation_status status = validate_textures(content);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- COLORS -------------------

Test(validate_colors, invalid_rgb_should_return_ERR_INVALID_RGB, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/color_invalid_rgb.cub", &content);
	t_validation_status status = validate_colors(content);
	
	cr_assert_eq(status, ERR_INVALID_RGB, "Esperava ERR_INVALID_RGB, mas recebeu %s", get_status_name(status));
}

Test(validate_colors, missing_rgb_C_return_ERR_ERR_INVALID_RGB, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/color_missing_ceiling_rgb.cub", &content);
	t_validation_status status = validate_colors(content);
	
	cr_assert_eq(status, ERR_INVALID_RGB, "Esperava ERR_INVALID_RGB, mas recebeu %s", get_status_name(status));
}

Test(validate_colors, missing_rgb_F_return_ERR_ERR_INVALID_RGB, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/color_missing_floor_rgb.cub", &content);
	t_validation_status status = validate_colors(content);
	
	cr_assert_eq(status, ERR_INVALID_RGB, "Esperava ERR_INVALID_RGB, mas recebeu %s", get_status_name(status));
}

Test(validate_colors, missing_color_should_return_ERR_MISSING_COLOR, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/color_missing.cub", &content);
	t_validation_status status = validate_colors(content);
	
	cr_assert_eq(status, ERR_MISSING_COLOR, "Esperava ERR_MISSING_COLOR, mas recebeu %s", get_status_name(status));
}

Test(validate_colors, valid_color_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	t_validation_status status = validate_colors(content);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- MAP POSITON -------------------

Test(validate_map_position, map_first_should_return_ERR_INVALID_MAP_POSITION, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/map_first.cub", &content);
	t_validation_status status = validate_map_position(content);
	
	cr_assert_eq(status, ERR_INVALID_MAP_POSITION, "Esperava ERR_INVALID_MAP_POSITION, mas recebeu %s", get_status_name(status));
}

Test(validate_map_position, map_middle_should_return_ERR_INVALID_MAP_POSITION, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/map_middle.cub", &content);
	t_validation_status status = validate_map_position(content);
	
	cr_assert_eq(status, ERR_INVALID_MAP_POSITION, "Esperava ERR_INVALID_MAP_POSITION, mas recebeu %s", get_status_name(status));
}

Test(validate_map_position, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	t_validation_status status = validate_map_position(content);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- MAP EXISTENCE -------------------

Test(validate_map_existence, map_missing_should_return_ERR_MISSING_MAP, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/map_missing.cub", &content);
	t_validation_status status = validate_map_existence(content);
	
	cr_assert_eq(status, ERR_MISSING_MAP, "Esperava ERR_MISSING_MAP, mas recebeu %s", get_status_name(status));
}

Test(validate_map_existence, data_adter_map_should_return_ERR_DATA_AFTER_MAP, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	get_content_splitted_mock("./tests/resources/invalid_maps/data_after_map.cub", &content);
	t_validation_status status = validate_map_existence(content);
	
	cr_assert_eq(status, ERR_DATA_AFTER_MAP, "Esperava ERR_DATA_AFTER_MAP, mas recebeu %s", get_status_name(status));
}

Test(validate_map_existence, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	t_validation_status status = validate_map_existence(content);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- MAP SIZE -------------------

Test(validate_map_size, small_map_should_return_ERR_INVALID_MAP_SIZE, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/map_too_small.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/map_too_small.cub", &map, content);
	t_validation_status status = validate_map_size(map);
	
	cr_assert_eq(status, ERR_INVALID_MAP_SIZE, "Esperava ERR_INVALID_MAP_SIZE, mas recebeu %s", get_status_name(status));
}

Test(validate_map_size, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	get_map_matrix_mock("./tests/resources/valid_maps/1.cub", &map, content);
	t_validation_status status = validate_map_size(map);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- FORBIDDEN CONTENT (EXCETO ESPAÇO) -------------------

Test(validate_map_lines, small_map_should_return_ERR_INVALID_MAP_SIZE, .init=redirect_all_stdout_echo)//VERIFICAR
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/forbidden_map_content.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/forbidden_map_content.cub", &map, content);
	t_validation_status status = validate_map_lines(map);
	
	cr_assert_eq(status, ERR_INVALID_MAP_CONTENT, "Esperava ERR_INVALID_MAP_SIZE, mas recebeu %s", get_status_name(status));
}

Test(validate_map_lines, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	get_map_matrix_mock("./tests/resources/valid_maps/1.cub", &map, content);
	t_validation_status status = validate_map_lines(map);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- EDGES VALIDATION -------------------

Test(validate_edges, hole_on_north_edge_should_return_ERR_INVALID_EDGES, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/wall_hole_north.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/wall_hole_north.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, ERR_INVALID_EDGES, "Esperava ERR_INVALID_EDGES, mas recebeu %s", get_status_name(status));
}

Test(validate_edges, hole_on_south_edge_should_return_ERR_INVALID_EDGES, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/wall_hole_south.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/wall_hole_south.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, ERR_INVALID_EDGES, "Esperava ERR_INVALID_EDGES, mas recebeu %s", get_status_name(status));
}

Test(validate_edges, hole_on_east_edge_should_return_ERR_INVALID_EDGES, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/wall_hole_east.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/wall_hole_east.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, ERR_INVALID_EDGES, "Esperava ERR_INVALID_EDGES, mas recebeu %s", get_status_name(status));
}

Test(validate_edges, hole_on_west_edge_should_return_ERR_INVALID_EDGES, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/wall_hole_west.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/wall_hole_west.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, ERR_INVALID_EDGES, "Esperava ERR_INVALID_EDGES, mas recebeu %s", get_status_name(status));
}

Test(validate_edges, player_on_edge_should_return_ERR_INVALID_EDGES, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/player_on_edge.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/player_on_edge.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, ERR_INVALID_EDGES, "Esperava ERR_INVALID_EDGES, mas recebeu %s", get_status_name(status));
}

Test(validate_edges, no_walls_should_return_ERR_INVALID_EDGES, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/wall_none.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/wall_none.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, ERR_INVALID_EDGES, "Esperava ERR_INVALID_EDGES, mas recebeu %s", get_status_name(status));
}

Test(validate_edges, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	get_map_matrix_mock("./tests/resources/valid_maps/1.cub", &map, content);
	t_validation_status status = validate_edges(map);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- PLAYER VALIDATION -------------------

Test(validate_player, multiplayer_should_return_ERR_MULTIPLAYERS, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/player_multiple.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/player_multiple.cub", &map, content);
	t_validation_status status = validate_player(map);
	
	cr_assert_eq(status, ERR_MULTIPLAYERS, "Esperava ERR_MULTIPLAYERS, mas recebeu %s", get_status_name(status));
}

Test(validate_player, no_player_should_return_ERR_NO_PLAYER, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/player_none.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/player_none.cub", &map, content);
	t_validation_status status = validate_player(map);
	
	cr_assert_eq(status, ERR_NO_PLAYER, "Esperava ERR_NO_PLAYER, mas recebeu %s", get_status_name(status));
}

Test(validate_player, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	get_map_matrix_mock("./tests/resources/valid_maps/1.cub", &map, content);
	t_validation_status status = validate_player(map);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}

// ------------------- FLOOD FILL -------------------

Test(flood_fill, map_open_should_return_ERR_MAP_OPEN, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/map_open.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/map_open.cub", &map, content);
	t_validation_status status = flood_fill(map);
	
	cr_assert_eq(status, ERR_MAP_OPEN, "Esperava ERR_MAP_OPEN, mas recebeu %s", get_status_name(status));
}

Test(flood_fill, inter_space_should_return_ERR_INTER_SPACE, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/invalid_maps/forbidden.cub", &content);
	get_map_matrix_mock("./tests/resources/invalid_maps/forbidden.cub", &map, content);
	t_validation_status status = flood_fill(map);
	
	cr_assert_eq(status, ERR_INTER_SPACE, "Esperava ERR_INTER_SPACE, mas recebeu %s", get_status_name(status));
}


Test(flood_fill, valid_map_should_return_VALIDATION_OK, .init=redirect_all_stdout_echo)
{
	char ***content;
	char **map;
	get_content_splitted_mock("./tests/resources/valid_maps/1.cub", &content);
	get_map_matrix_mock("./tests/resources/valid_maps/1.cub", &map, content);
	t_validation_status status = flood_fill(map);
	
	cr_assert_eq(status, VALIDATION_OK, "Esperava VALIDATION_OK, mas recebeu %s", get_status_name(status));
}
