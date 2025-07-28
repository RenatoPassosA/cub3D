/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_player.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:23:58 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/28 18:17:51 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	validate_player(char **map, int fd)
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
			clean_all_and_message_error("Error.\nMultiplayers not allowed.", NULL, map, fd);
		index++;
	}
	if (!has_player)
		clean_all_and_message_error("Error.\nNo player start position found.", NULL, map, fd);
		
}