/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:59:10 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/25 13:34:50 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map *get_map_instance(void)
{
	static t_map map;
	
	return (&map);
}

t_map *init_data(void)
{
	t_map	*map;

	map = get_map_instance();
	map->NO_texture = NULL;
	map->SO_texture = NULL;
	map->WE_texture = NULL;
	map->EA_texture = NULL;
	map->floor_rgb = -1;
	map->ceiling_rgb = -1;
	map->map_lines = 0;
	map->map = NULL;

	return (map);
}

void	free_map_info(void)
{
	t_map	*map;

	map = get_map_instance();
	if (map->NO_texture)
		free(map->NO_texture);
	if (map->SO_texture)
		free(map->SO_texture);
	if (map->WE_texture)
		free(map->WE_texture);
	if (map->EA_texture)
		free(map->EA_texture);
	if (map->map)
		free_arr_with_null(map->map, map->map_lines + 1);
}
