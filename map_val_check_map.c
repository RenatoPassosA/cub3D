/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/28 17:41:15 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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

bool	check_map_size(char ***content, int init_map)
{
	int	heigth;
	int	width;
	int	index;

	index = 0;
	heigth = 0;
	while (content[init_map] != NULL)
	{
		while (content[init_map][index])
		{
			width = count_width(content[init_map][index]);
			if (width < 5)
				return(false);
		index++;
		}
		index = 0;
		init_map++;
		heigth++;
	}
	if (heigth < 5)
			return(false);
	return(true);
}

void validate_map(char ***content, int fd)
{
	int index;
	int	map_height;
	int	save_index;
	
	index = 0;
	map_height = 0;
	while (content[index] && (is_type_identifier(content[index][0]) ||
       ft_strcmp(content[index][0], "\n") == 0))
		index++;
	save_index = index;
	while (content[index] && *content[index][0] == '1')
	{
		index++;
		map_height++;
	}
	while (content[index])
		clean_all_and_message_error("Error.\nFile contains data after map.", content, NULL, fd);
	if (map_height == 0)
		clean_all_and_message_error("Error.\nMissing map.", content, NULL, fd);
	if (!check_map_size(content, save_index))
	 	clean_all_and_message_error("Error.\nMap should be at least 5x5.", content, NULL, fd);
}
