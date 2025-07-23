/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:12:58 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 16:13:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	clean_map_error(int fd, char *line, char **splitted)
{
	close(fd);
	free(line);
	free_arr_with_null(splitted, get_arr_size(splitted));
	return(false);
}

bool	is_valid_map_char(char *line)
{
	while(*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return (false);
		line++;
	}
	return (true);
}

bool	check_valid_content(char *line)
{
	return (
		ft_strncmp(line, "NO", 2) == 0 ||
		ft_strncmp(line, "SO", 2) == 0 ||
		ft_strncmp(line, "WE", 2) == 0 ||
		ft_strncmp(line, "EA", 2) == 0 ||
		ft_strncmp(line, "F", 1) == 0 ||
		ft_strncmp(line, "C", 1) == 0 ||
		line[0] == '1' ||
		line[0] == '\n'
	);
}