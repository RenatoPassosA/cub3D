/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:10:29 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/18 17:48:22 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char *fill_line(char *line, int	width)
{
	char *new_line;
	int	index;

	index = 0;
	new_line = (char *)malloc(sizeof(char) * (width + 1));
	if (!new_line)
		return (NULL);
	while (line[index])
	{
		new_line[index] = line[index];
		index++;
	}
	while (index < width)
	{
		new_line[index] = '1';
		index++;
	}
	new_line[index] = '\0';
	return (new_line);
}

t_validation_status set_matrix(char ***map)
{
	int index = 0;
	int max_width = 0;
	char *temp;
	int width;

	while ((*map)[index] != NULL)
	{
		width = get_line_width((*map)[index]);
		if (width > max_width)
			max_width = width;
		index++;
	}
	index = 0;
	while ((*map)[index] != NULL)
	{
		temp = fill_line((*map)[index], max_width);
		if (!temp)
			return (ERR_MALLOC_MAP_AND_CONTENT);
		free((*map)[index]);
		(*map)[index] = temp;
		index++;
	}
	(*map)[index] = NULL;
	return(VALIDATION_OK);
}

t_validation_status	get_map_matrix(char **av, char ***map, char ***content)
{
	int	index;
	int	index2;
	char *line;
	t_map	*map_data;
	
	index = 0;
	index2 = 0;
	*map = (char **)malloc(sizeof(char *) * (get_map_content_height(content) + 1));
	if (!(*map))
		return(ERR_MALLOC_MAP);
	map_data = get_map_instance();
	fd_manage(av[1], map_data->fd, content, *map);
	while ((line = get_next_line(map_data->fd)))
	{
		if (check_find_map(line, &index))
			continue;
		remove_backslash_n2(line);
		(*map)[index2++] = ft_strdup(line);
		index++;
		free(line);
	}
	(*map)[index2] = NULL;
	if (set_matrix(map) == ERR_MALLOC_MAP_AND_CONTENT)
		return (ERR_MALLOC_MAP_AND_CONTENT);
	return (VALIDATION_OK);
}
