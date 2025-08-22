/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:36:13 by renato            #+#    #+#             */
/*   Updated: 2025/08/19 13:55:32 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_type_identifier(char *splitted)
{
	return (ft_strcmp(splitted, "NO") == 0 || 
		ft_strcmp(splitted, "SO") == 0 || 
		ft_strcmp(splitted, "WE") == 0 || 
		ft_strcmp(splitted, "EA") == 0 || 
		ft_strcmp(splitted, "F") == 0 || 
		ft_strcmp(splitted, "C") == 0);
}

void	remove_backslash_n(char **content)
{
	int	index;
	int	len;
	
	index = 0;
	while (content[index] != NULL)
	{
		if (ft_strcmp(content[index], "\n") == 0)
		{
			index++;
			continue;
		}
		else if (ft_strstr(content[index],"\n"))
		{
			len = ft_strlen(content[index]);
			content[index][len - 1] = '\0';
		}
		index++;
	}
}

t_validation_status	get_content_splitted(char *path, char ****content)
{
	int		counter;
	char	*line;
	t_map	*map_data;

	counter = 0;
	map_data = get_map_instance();
	while ((line = get_next_line(map_data->fd)))
	{
		counter++;
		free(line);
	}
	*content = (char ***)malloc(sizeof(char **) * (counter + 1));
	if (!(*content))
		return(ERR_MALLOC_CONTENT);
	(*content)[counter] = NULL;
	fd_manage(path, map_data->fd, *content, NULL);
	counter = 0;
	while ((line = get_next_line(map_data->fd)))
	{
		(*content)[counter] = ft_split(line, ' ');
		remove_backslash_n((*content)[counter]);
		free(line);
		counter++;
	}
	return(VALIDATION_OK);
}
