/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:19:18 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/30 11:21:24 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_argument(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		printf("Error.\n Check the arguments");
		return (0);
	}
	len = ft_strlen(av[1]);
	if (ft_strnstr(&av[1][len - 4], ".cub", 4) == NULL)
	{
		printf("Error.\n Invalid map file");
		return (0);
	}
	return (1);
}

int	get_arr_size(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
		index++;
	return (index);
}


void	free_arr_with_null(char **arr, int splitted_arr_size)
{
	int	index;

	index = 0;
	while (index < splitted_arr_size)
	{
		if (!arr[index])
			index++;
		else
		{
			free(arr[index]);
			index++;
		}
	}
	free(arr);
}

void	free_bidimensional_array(char **arr)
{
	int i;

	if (!arr)
		return;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


void	free_tridimensional_array(char ***content)
{
	int	i;
	int j;

	if (!content)
		return;
	i = 0;
	while (content[i])
	{
		j = 0;
		while (content[i][j])
		{
			free(content[i][j]);
			j++;
		}
		free(content[i]);
		i++;
	}
	free(content);
}


void clean_all_and_message_error(char *msg, char ***content, char **map)
{
	t_map *map_data;

	map_data = get_map_instance();
	if (msg)
	{
		while(*msg)
			write(2, msg++, 1);
		write(2, "\n", 1);
	}
	if (content)
		free_tridimensional_array(content);
	if (map)
		free_bidimensional_array(map);
	if (map_data->fd >= 0)
		close(map_data->fd);
	exit(1);
}



