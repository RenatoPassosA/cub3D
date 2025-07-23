/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:19:18 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 13:26:40 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	clean_map_error(int fd, char *line, char **splitted)
{
	close(fd);
	printf("Error.\nMap must be on end of the file.");
	free(line);
	free_arr_with_null(splitted, get_arr_size(splitted));
	return(false);
}

bool	is_valid_map_char(char *line)
{
	while(*line)
	{
		if (*line != '1' && *line != '0' && *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return (false);
		line++;
	}
	return (true);
}

bool	validate_map(int fd)
{
	bool	is_map;
	char	*line;
	char	**splitted;
	t_map	*map;
	size_t	len;

	map = get_map_instance();
	is_map = false;
	while ((line = get_next_line(fd)))
	{
		if (line && ft_strcmp(line, "\n") != 0)
		{
			len = ft_strlen(line);
			if (len > 1)
				line[len - 1] = '\0';
		}
		splitted = ft_split(line, ' ');
		if (splitted[0] && !is_map && (is_type_identifier(splitted[0]) || ft_strcmp(splitted[0], "\n") == 0))
		{
			free(line);
			free_arr_with_null(splitted, get_arr_size(splitted));
			continue;
		}
		else if (!is_map && splitted[0] && is_valid_map_char(line))
			is_map = true;
		else if (splitted[0] && is_map && !is_valid_map_char(line)) //nao entra aqui pq o is_map é false
			return(clean_map_error(fd, line, splitted));
		if (is_valid_map_char(line))
			map->map_lines++;
		free(line);
		free_arr_with_null(splitted, get_arr_size(splitted));
	}
	return(true);
}


// bool	check_if_map_is_at_end(int fd)
// {
// 	bool	is_map;
// 	char	*line;
// 	char	**splitted;
// 	t_map	*map;

// 	map = get_map_instance();
// 	is_map = false;
// 	while ((line = get_next_line(fd)))
// 	{
// 		splitted = ft_split(line, ' ');
// 		if (splitted[0] && is_type_identifier(splitted[0]) && !is_map)
// 		{
// 			free(line);
// 			free_arr_with_null(splitted, get_arr_size(splitted));
// 			continue;
// 		}
// 		else if (!is_map && splitted[0] && !is_type_identifier(splitted[0]) && ft_strcmp(splitted[0], "\n") != 0)
// 			is_map = true;
// 		else if (splitted[0] && is_map && (is_type_identifier(splitted[0]) || !is_valid_map_char(line)))
// 			return(clean_map_error(fd, line, splitted));
// 		if (ft_strcmp(line, "\n") != 0)
// 			map->map_lines++;
// 		free(line);
// 		free_arr_with_null(splitted, get_arr_size(splitted));
// 	}
// 	return(true);
// }
