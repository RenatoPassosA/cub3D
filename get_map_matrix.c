/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:10:29 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/30 10:27:29 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void set_matrix(char ***map, int fd)
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
			clean_all_and_message_error("Error on malloc", NULL, *map, fd);
		free((*map)[index]);
		(*map)[index] = temp;
		index++;
	}
	(*map)[index] = NULL;
}

void	get_map_matrix(char **av, char ***map, char ***content, int fd)
{
	int	index;
	int	index2;
	int	map_height;
	char *line;
	
	index = 0;
	index2 = 0;
	map_height = get_map_content_height(content);
	*map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (!(*map))
		clean_all_and_message_error("Error on malloc.\n", content, NULL, fd);
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
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
	if (!check_map_size(*map))
	 	clean_all_and_message_error("Error.\nMap should be at least 5x5.", content, *map, fd);
	set_matrix(map, fd); //aqui o meu mapa está com as linhas ao final preenchido com espaço até todas as linhas ficarem iguais
}
