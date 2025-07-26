/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_valid_lines.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:08:26 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/26 09:24:27 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_line(char *line)
{
	if (!line)
		return (false);
	return (
		ft_strncmp(line, "NO", 2) == 0 ||
		ft_strncmp(line, "SO", 2) == 0 ||
		ft_strncmp(line, "WE", 2) == 0 ||
		ft_strncmp(line, "EA", 2) == 0 ||
		ft_strncmp(line, "F", 1) == 0 ||
		ft_strncmp(line, "C", 1) == 0 ||
		line[0] == '1' ||
		line[0] == '\n');
}

void	check_valid_lines(char ***content, int fd)
{
	int		index;
	
	index = 0;
	while(content[index] != NULL)
	{
		if (!check_line(content[index][0]))
			clean_all_and_message_error("Error.\nInvalid map element.", content, NULL, fd);
		index++;
	}
}