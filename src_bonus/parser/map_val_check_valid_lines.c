/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_valid_lines.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:18:49 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 13:55:39 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	check_forbidden_char_in_line(char *line)
{
	int	index;

	index = 0;
	while (*line)
	{
		if (line[index] != '0' &&
			line[index] != '1' &&
			line[index] != 'N' &&
			line[index] != 'S' &&
			line[index] != 'E' &&
			line[index] != 'W' &&
			line[index] != ' ')
			return (true);
		line++;
	}
	return (false);
}

t_validation_status	validate_map_lines(char **map)
{
	int	height;
	
	height = 0;
	while (map[height] != NULL)
	{
		if (check_forbidden_char_in_line(map[height]))
			return(ERR_INVALID_MAP_CONTENT);
		height++;
	}
	return(VALIDATION_OK);
}
