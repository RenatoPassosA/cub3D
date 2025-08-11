/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_map_size.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/11 14:53:22 by renato           ###   ########.fr       */
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

static bool	check_map_size(char **map)
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

t_validation_status validate_map_size(char **map)
{
	if (!check_map_size(map))
		return (ERR_INVALID_MAP_SIZE);
	return(VALIDATION_OK);
}
