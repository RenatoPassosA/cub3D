/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:10:29 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 15:18:19 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	remove_backslash_n2(char *line)
{
	int	len;
	
	if (!line)
		return;
	if (ft_strstr(line,"\n"))
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
	}
}

bool	find_map(char *line)
{
	while (*line == ' ')
			line++;
	return (ft_strncmp(line, "NO", 2) == 0 || 
		ft_strncmp(line, "SO", 2) == 0 || 
		ft_strncmp(line, "WE", 2) == 0 || 
		ft_strncmp(line, "EA", 2) == 0 || 
		ft_strncmp(line, "F", 1) == 0 || 
		ft_strncmp(line, "C", 1) == 0 ||
		ft_strncmp(line, "\n", 1) == 0);
	
}

int	get_map_content_height(char ***content)
{
	int index;
	int	map_height;
	
	index = 0;
	map_height = 0;
	while (content[index] && (is_type_identifier(content[index][0]) ||
       ft_strcmp(content[index][0], "\n") == 0))
		index++;
	while (content[index] && *content[index][0] == '1')
	{
		index++;
		map_height++;
	}
	return (map_height);
}

int	get_line_width(char *line)
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
		new_line[index] = ' ';
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
	int	map_height;
	char *line;
	t_map	*map_data;
	
	index = 0;
	index2 = 0;
	map_height = get_map_content_height(content);
	*map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (!(*map))
		return(ERR_MALLOC_MAP);
	map_data = get_map_instance();
	fd_manage(av[1], map_data->fd, content, *map);
	while ((line = get_next_line(map_data->fd)))
	{
		if (find_map(line))
		{
			free(line);
			index++;
			continue;
		}
		remove_backslash_n2(line);
		(*map)[index2] = ft_strdup(line);
		index++;
		index2++;
		free(line);
	}
	(*map)[index2] = NULL; //aqui tenho o mapa certinho
	if (set_matrix(map) == 	ERR_MALLOC_MAP_AND_CONTENT) //aqui o meu mapa está com as linhas ao final preenchido com espaço até todas as linhas ficarem iguais
		return (ERR_MALLOC_MAP_AND_CONTENT);
	return (VALIDATION_OK);
}
