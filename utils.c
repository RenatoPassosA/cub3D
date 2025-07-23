/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:19:18 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 16:14:04 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void show_error_msg(char *msg)
{
	while(*msg)
		write(2, msg++, 1);
}

int	check_argument(int ac, char **av, int fd)
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
	if (fd == -1)
	{
		printf("Error.\n Cannot read the map");
		close(fd);
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



