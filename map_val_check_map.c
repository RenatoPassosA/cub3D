/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/26 09:29:16 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map(int content_index, char ***content, char **map)
{
	int	index;

	index = 0;
	while (content[content_index] && *content[content_index][0] == '1')
	{
		map[index] = ft_strdup(content[content_index][0]);
		content_index++;
		index++;
	}	
	map[index] = NULL;
}

int	count_width(char *line)
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

bool	check_map_size(char ***content, char **map)
{
	int	heigth;
	int	width;
	int	index;

	index = 0;
	while(content[index])
	{
		if (*content[index][0] == '1' && get_arr_size(content[index]) >= 2)
			return(true);
		index++;
	}
	heigth = 0;
	width = 0;
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

void check_map(char ***content, char ***map, int fd)
{
	int index;
	int	counter;
	int	save_index;
	
	index = 0;
	counter = 0;
	while (content[index] && (is_type_identifier(content[index][0]) ||
       ft_strcmp(content[index][0], "\n") == 0))
		index++;
	save_index = index;
	while (content[index] && *content[index][0] == '1')
	{
		index++;
		counter++;
	}
	while (content[index])
		clean_all_and_message_error("Error.\nFile contains data after map.", content, NULL, fd);
	if (counter == 0)
		clean_all_and_message_error("Error.\nMissing map.", content, NULL, fd);
	*map = (char **)malloc(sizeof(char *) * (counter + 1));
	fill_map(save_index, content, *map);
	if (!check_map_size(content, *map))
		clean_all_and_message_error("Error.\nMap should be at least 5x5.", content, *map, fd);
}
