/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_matrix_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:10:29 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 13:54:07 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

bool	check_find_map(char *line, int *index)
{
	if (find_map(line))
	{
		free(line);
		(*index)++;
		return (true);
	}
	return (false);
}
