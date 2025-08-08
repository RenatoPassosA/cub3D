/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 10:17:12 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_width(char *line)
{
	int	width;

	width = 0;
	while (*line)
	{
		width++;
		line++;
	}
	return (width);
}

bool	check_map_size(char **map)
{
	int	heigth;
	int	width;
	
	heigth = 0;
	while (map[heigth] != NULL)
	{
		width = count_width(map[heigth]);
		if (width < 5)
			return(false);
		heigth++;
	}
	if (heigth < 5)
			return(false);
	return(true);
}

void validate_map(char ***content)
{
	int index;
	int	map_height;
	
	index = 0;
	map_height = 0;
	while (content[index] && (is_type_identifier(content[index][0]) ||
       ft_strcmp(content[index][0], "\n") == 0))
		index++;
	while (content[index] && *content[index][0] == '1')
	{
		index++;
		map_height++;
	}
	while (content[index])
		clean_all_and_message_error("Error.\nFile contains data after map.", content, NULL);
	if (map_height == 0)
		clean_all_and_message_error("Error.\nMissing map.", content, NULL);
}
