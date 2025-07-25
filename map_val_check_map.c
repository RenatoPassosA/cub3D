/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/24 21:01:10 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map(int content_index, char ***content, char **map)
{
	int	index;

	index = 0;
	while (content[content_index] && ft_strcmp(content[content_index][0], "1") == 0)
	{
		map[index] = ft_strdup(content[content_index][0]);
		content_index++;
		index++;
	}	
	map[index] = NULL;
}

void check_map(char ***content, char ***map)
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
	while (content[index] && ft_strcmp(content[index][0], "1") == 0)
	{
		index++;
		counter++;
	}
	while (content[index])
	{
		show_error_msg("Error.\nFile contains data after map."); //-------------------------criar função para imprimir a msg, dar free no ***map e exit e free no ***map;
		exit(1);
	}
	if (counter == 0)
	{
		show_error_msg("Error.\nMissing map."); //-------------------------criar função para imprimir a msg, dar free no ***map e exit e free no ***map;
		exit(1);
	}
	*map = (char **)malloc(sizeof(char *) * (counter + 1));
	if (!*map)
		;//-------------------------criar função para imprimir a msg, dar free no ***map e exit e free no ***map;
	fill_map(save_index, content, *map);
}