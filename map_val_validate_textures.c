/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:46:53 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/26 09:23:00 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_texture(char *identifier)
{
	return (ft_strcmp(identifier, "NO") == 0) ||
	(ft_strcmp(identifier, "SO") == 0) ||
	(ft_strcmp(identifier, "WE") == 0) ||
	(ft_strcmp(identifier, "EA") == 0);
}

static bool is_valid_texture_path(char *path)
{
	int		fd;
	size_t	len;
	
	len= ft_strlen(path);
	if (len < 4 || ft_strcmp(path + len - 4, ".xpm") != 0)
		return false;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

void	validate_textures(char ***content, int fd)
{
	int		index;

	index = 0;
	while(content[index] != NULL)
	{
		if (content[index][0] && is_texture(content[index][0]))
		{
			if (!content[index][1])
				clean_all_and_message_error("Error.\n Insert a texture path.", content, NULL, fd);
			if (!is_valid_texture_path(content[index][1]))
				clean_all_and_message_error("Error.\n Insert a valid texture path.", content, NULL, fd);
		}
		index++;
	}
}
