/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 11:41:07 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	free_tridimensional_array(content);
	free_bidimensional_array(map);
}
