/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:46:53 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/24 20:08:17 by rpassos-         ###   ########.fr       */
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

static bool is_valid_texture_path(const char *path)
{
	int		fd;
	size_t	len;
	
	len= strlen(path);
	if (len < 4 || strcmp(path + len - 4, ".xpm") != 0)
		return false;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

void	validate_textures(char ***content)
{
	int		index;

	index = 0;
	while(content[index] != NULL)
	{
		if (content[index][0] && is_texture(content[index][0]))
		{
			if (!content[index][1])
				show_error_msg("Error.\n Insert a texture path"); //-------------------------criar função para imprimir a msg, dar free no ***map e exit
			if (!is_valid_texture_path(content[index][1]))
				show_error_msg("Error.\n Insert a valid texture path"); //-------------------------criar função para imprimir a msg, dar free no ***map e exit
		}
		index++;
	}
}