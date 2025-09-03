/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:59:10 by rpassos-          #+#    #+#             */
/*   Updated: 2025/09/02 16:43:02 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

t_map *get_map_instance(void)
{
	static t_map map;
	
	return (&map);
}

void init_data(char *path)
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
	map->z_buffer = malloc(sizeof(double) * SCREEN_WIDTH);
	if (!map->z_buffer)
		clean_all_and_message_error("Error on malloc.", NULL, NULL);
	map->fd = open(path, O_RDONLY);
	if (map->fd < 0)
		clean_all_and_message_error("Error on opening fd.", NULL, NULL);
}

void	fd_manage(char *path, int fd, char ***content, char **map)
{
	t_map *map_data;

	if (fd >= 0)
		close(fd);
	map_data = get_map_instance();
	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_all_and_message_error("Error on opening fd.", content, map);
	map_data->fd = fd;
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
		free_bidimensional_array(map->map);
}
