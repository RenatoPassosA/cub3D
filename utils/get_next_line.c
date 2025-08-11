/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:00:11 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/11 14:28:38 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*set_line(char **store)
{
	int		i;
	char	*line;
	char	*temp;

	line = NULL;
	i = 0;
	if (ft_strchr(*store, '\n'))
	{
		while (store[0][i] != '\n')
			i++;
		i++;
		line = ft_substr(*store, 0, i);
		temp = *store;
		*store = ft_substr(*store, i, ft_strlen(*store) - i);
		free(temp);
	}
	else
	{
		line = *store;
		*store = NULL;
	}
	return (line);
}

static int	check_empty(char **store, char *buffer, int r_return)
{
	if (r_return < 0 || !store[0] || (!r_return && store[0][0] == '\0'))
	{
		free(buffer);
		free(*store);
		*store = NULL;
		return (1);
	}
	return (0);
}

static char	*read_line(int fd, char **store)
{
	char	*buffer;
	int		read_return;
	char	*temp;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return == -1)
		return (free(*store), free(buffer), NULL);
	buffer[read_return] = '\0';
	while (read_return > 0)
	{
		temp = *store;
		*store = ft_strjoin(*store, buffer);
		free(temp);
		if (ft_strchr(*store, '\n'))
			break ;
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = '\0';
	}
	if (check_empty(store, buffer, read_return) == 1)
		return (NULL);
	free(buffer);
	return (set_line(store));
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, &store);
	if (!line)
		return (NULL);
	return (line);
}
