/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_colors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:05:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/26 09:23:36 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*static int get_rgb(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}*/

static bool check_rgb_range(int val)
{
	return (val >= 0 && val <= 255);
}


static bool	is_color(char *identifier)
{
	return (ft_strcmp(identifier, "F") == 0) ||
	(ft_strcmp(identifier, "C") == 0);
}

static bool is_valid_color(const char *colors)
{
	char	**rgb;
	int		size;

	rgb = ft_split(colors, ',');
	if (!rgb)
		return (false);
	size = get_arr_size(rgb);
	if (get_arr_size(rgb) < 3 || !check_rgb_range(ft_atoi(rgb[0])) ||
		!check_rgb_range(ft_atoi(rgb[1])) || !check_rgb_range(ft_atoi(rgb[2])))
	{
		free_arr_with_null(rgb, size);
		return(false);
	}
	free_arr_with_null(rgb, size);
	return (true);
}

void	validate_colors(char ***content, int fd)
{
	int		index;

	index = 0;
	while(content[index] != NULL)
	{
		if (content[index][0] && is_color(content[index][0]))
		{
			if (!content[index][1])
				clean_all_and_message_error("Error.\n Insert a color", content, NULL, fd);
			if (!is_valid_color(content[index][1]))
				clean_all_and_message_error("Error.\n Insert a valid color configuration", content, NULL, fd);
		}
		index++;
	}
}

