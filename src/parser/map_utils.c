/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:59:10 by rpassos-          #+#    #+#             */
/*   Updated: 2025/11/02 18:18:00 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_map *get_map_instance(void)
{
	static t_map map;
	
	return (&map);
}

void init_data(char *path)
{
	t_map	*map;

	map = get_map_instance();
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_rgb = -1;
	map->ceiling_rgb = -1;
	map->map_lines = 0;
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
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->map)
		free_bidimensional_array(map->map);
}
