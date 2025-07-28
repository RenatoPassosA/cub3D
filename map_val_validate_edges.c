/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/28 19:02:20 by rpassos-         ###   ########.fr       */
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

char *remove_spaces(char *line)
{
	char **splitted;
	char *temp;
	char *new_line;
	int	index;

	splitted = ft_split(line, ' ');
	index = 0;
	new_line = ft_strdup(splitted[0]);
	while (splitted[++index])
	{
		temp = new_line;
		new_line = ft_strjoin(new_line, splitted[index]);
		free(temp);
	}
	free_bidimensional_array(splitted);
	return(new_line);
}

void	validate_edges(char **map, int fd)
{
	int	counter;
	int	size;

	counter = 1;
	size = 0;
	while(map[size] != NULL)
		size++;
	
	if (!check_top_and_bottom_edge(remove_spaces(map[0])) || 
		!check_top_and_bottom_edge(remove_spaces(map[size - 1])))
		clean_all_and_message_error("Error.\nWrong edges configuration", NULL, map, fd);
	while(counter < size - 1)
	{
		if (!check_middle_edges(remove_spaces(map[counter])))
			clean_all_and_message_error("Error.\nWrong edges configuration", NULL, map, fd);
		counter++;
	}
}



