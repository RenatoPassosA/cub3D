/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/11 15:35:46 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	putstr(char *msg)
{
	while(*msg)
		write(2, msg++, 1);
	write(2, "\n", 1);
}
void print_error_message2(t_validation_status status, char *msg)
{
	if (status == ERR_MISSING_MAP)
		msg = "Error.\nMissing map.";
	else if (status == ERR_INVALID_MAP_CONTENT)
		msg = "Error.\nForbidden chars on map content";
	else if (status == ERR_INVALID_MAP_SIZE)
		msg = "Error.\nMap should be at least 5x5.";
	else if (status == ERR_INVALID_MAP_CONTENT)
		msg = "Error.\nForbidden chars on map content";
	else if (status == ERR_INVALID_EDGES)
		msg = "Error.\nWrong edges configuration";
	else if (status == ERR_COPY_MAP)
		msg = "Error.\nFailed to copy map";
	else if (status == ERR_NO_PLAYER)
		msg = "Error.\nNo player start position found.";
	else if (status == ERR_INTER_SPACE)
		msg = "Error.\nMap contains isolated intern space";
	else if (status == ERR_MAP_OPEN)
		msg = "Error.\nMap is not closed or holes on the floor";
	else if (status == ERR_MULTIPLAYERS)
		msg = "Error.\nMultiplayers not allowed.";
	else if (status == ERR_MALLOC_CONTENT || status == ERR_MALLOC_MAP ||
			status == ERR_MALLOC_MAP_AND_CONTENT)
		msg = "Error.\nAllocation Failed";
	putstr(msg);
}

void print_error_message1(t_validation_status status, char *msg)
{
	if (status == ERR_MISSING_IDENTIFIER)
		msg = "Error.\nMissing type identifier element.";
	else if (status == ERR_DOUBLE_IDENTIFIER)
		msg = "Error.\nDuplicated identifiers.";
	else if (status == ERR_MISSING_TEXTURE_PATH)
		msg = "Error.\nInsert a texture path.";
	else if (status == ERR_INVALID_TEXTURE_PATH)
		msg = "Error.\nInsert a valid texture path.";
	else if (status == ERR_INVALID_MAP_POSITION)
		msg = "Error.\nInvalid map position on content.";
	else if (status == ERR_MISSING_COLOR)
		msg = "Error.\n Insert a color";
	else if (status == ERR_INVALID_RGB)
		msg = "Error.\n Insert a valid color configuration";
	else if (status == ERR_INVALID_MAP_POSITION)
		msg = "Error.\nInvalid map position on content.";
	else if (status == ERR_INVALID_MAP_ELEMENT)
		msg = "Error.\nInvalid map element.";
	else if (status == ERR_DATA_AFTER_MAP)
		msg = "Error.\nFile contains data after map.";
	if (!msg)
		print_error_message2(status, msg);
	else
		putstr(msg);
}
	
void handle_error(t_validation_status status, char ***content, char **map)
{
	t_map *map_data;
	char *msg;

	msg = NULL;
	map_data = get_map_instance();
	
	if (content)
		free_tridimensional_array(content);
	if (map)
		free_bidimensional_array(map);
	if (map_data->fd >= 0)
		close(map_data->fd);
	print_error_message1(status, msg);
	exit(1);

}

t_validation_status do_matrix_validations(char **map)
{
	t_validation_status status;
	
	status = validate_map_size(map);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_map_lines(map);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_edges(map);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_player(map);
	if (status != VALIDATION_OK)
		return (status);
	status = flood_fill(map);
	if (status != VALIDATION_OK)
		return (status);
	return (status);
}

t_validation_status do_content_validations(char ***content)
{
	t_validation_status status;

	status = check_missing_identifier(content);
	if (status != VALIDATION_OK)
		return (status);
	status = check_double_identifier(content);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_textures(content);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_colors(content);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_map_position(content);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_map_elements(content);
	if (status != VALIDATION_OK)
		return (status);
	status = validate_map_existence(content);
	if (status != VALIDATION_OK)
		return (status);
	return (status);
}

void	map_validations(char **av)
{
	char	***content;
	char	**map;
	t_validation_status status;

	status = get_content_splitted(av[1], &content);
	if (status != VALIDATION_OK)
		handle_error(status, NULL, NULL);
	status = do_content_validations(content);
	if (status != VALIDATION_OK)
		handle_error(status, content, NULL);
	status = get_map_matrix(av, &map, content);
	if (status != VALIDATION_OK)
		handle_error(status, content, map);
	status = do_matrix_validations(map);
	if (status != VALIDATION_OK)
		handle_error(status, content, map);
	status = set_map_data(content, map);
	if (status != VALIDATION_OK)
		handle_error(status, content, NULL);
}
