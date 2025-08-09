/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_colors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:05:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 16:34:20 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

t_validation_status	validate_colors(char ***content)
{
	int		index;

	index = 0;
	while(content[index] != NULL)
	{
		if (content[index][0] && is_color(content[index][0]))
		{
			if (!content[index][1])
				return(ERR_MISSING_COLOR);
			if (!is_valid_color(content[index][1]))
				return(ERR_INVALID_RGB);
		}
		index++;
	}
	return(VALIDATION_OK);
}

