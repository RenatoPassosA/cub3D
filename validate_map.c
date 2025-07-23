/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:11:59 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 16:36:52 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_map(int fd) //REFATORAR
{
	bool	is_map;
	char	*line;
	char	**splitted;
	size_t	len;
	t_map	*map;

	map = get_map_instance();
	is_map = false;
	while ((line = get_next_line(fd)))
	{
		splitted = ft_split(line, ' ');
		if (!check_valid_content(splitted[0]))
		{
			free(line);
			close(fd);
			show_error_msg("Error.\nWrong identifiers or map elements");
			exit(1);
		}
		if (splitted[0] && ft_strcmp(splitted[0], "\n") != 0)
		{
			if (!splitted[1] && ft_strstr(splitted[0],"\n"))
			{
				len = ft_strlen(splitted[0]);
				splitted[0][len - 1] = '\0';
			}
		}
		if (splitted[0] && !is_map && (is_type_identifier(splitted[0]) || ft_strcmp(splitted[0], "\n") == 0))
		{
			free(line);
			free_arr_with_null(splitted, get_arr_size(splitted));
			is_map = false;
			continue;
		}
		is_map = true;
		if (is_map && !is_valid_map_char(splitted[0]))
		{
			show_error_msg("Error.\nWrong elements on map content");
			clean_map_error(fd, line, splitted);
			exit(1);
		}
		if (is_map && is_valid_map_char(splitted[0]))
			map->map_lines++;
		free(line);
		free_arr_with_null(splitted, get_arr_size(splitted));
	}
	map->map = (char **)malloc(sizeof(char *) * map->map_lines);
	if(!map->map)
	{
		show_error_msg("Error on malloc");
		close(fd);
		exit(1);
	}
	return(true);
}
