/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/26 09:26:29 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_top_and_bottom_edge(char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (false);
		line++;
	}
	return(true);		
}

static bool	check_middle_edges(char *line)
{
	int	len;
	
	len = ft_strlen(line);
	if (line[0] != '1' || line[len - 1] != '1')
		return (false);
	return(true);		
}

void	validate_edges(char **map, int fd)
{
	int	counter;
	int	size;

	counter = 1;
	size = 0;
	while(map[size] != NULL)
		size++;
	if (!check_top_and_bottom_edge(map[0]) || !check_top_and_bottom_edge(map[size - 1]))
		clean_all_and_message_error("Error.\nWrong edges configuration", NULL, map, fd);
	while(counter < size - 1)
	{
		if (!check_middle_edges(map[counter]))
			clean_all_and_message_error("Error.\nWrong edges configuration", NULL, map, fd);
		counter++;
	}
}
