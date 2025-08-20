/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:00:36 by renato            #+#    #+#             */
/*   Updated: 2025/08/19 13:53:46 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void    init_mlx()
{
     t_map   *map;

    map = get_map_instance();
    map->mlx.mlx_ptr = mlx_init();
    if (map->mlx.mlx_ptr == NULL)
        exit(1);
    map->mlx.win_ptr = mlx_new_window(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
    if (map->mlx.win_ptr == NULL)
        exit(1);
    map->mlx.img_ptr = mlx_new_image(map->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
    map->mlx.img_data = mlx_get_data_addr(map->mlx.img_ptr, &map->mlx.bits_per_pixel, &map->mlx.size_line, &map->mlx.endian);
}