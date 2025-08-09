/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_player.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:23:58 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 16:34:13 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_player_one_line(char *line)
{
	while(*line)
	{
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			return (true);
		line++;
	}
	return(false);
}

t_validation_status	validate_player(char **map)
{
	int	index;
	bool	has_player;

	index = 1;
	has_player = false;
	while (map[index] != NULL)
	{
		if (check_player_one_line(map[index]) && !has_player)
			has_player = true;
		else if (check_player_one_line(map[index]) && has_player)
			return(ERR_MULTIPLAYERS);
		index++;
	}
	if (!has_player)
		return(ERR_NO_PLAYER);	
	return(VALIDATION_OK);
}