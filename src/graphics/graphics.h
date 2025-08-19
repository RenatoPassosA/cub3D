/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:05 by renato            #+#    #+#             */
/*   Updated: 2025/08/19 14:05:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

#include "../cub3d.h"
#include "../../mlx/mlx.h"

void    render();
void	init_textures();
void    set_wall_height(t_map *map);
void    draw_floor(t_map *map, int x);
void    draw_ceiling(t_map *map, int x);
uint32_t texel_at(const t_tex *t, int tx, int ty);
void    draw_walls(t_map *map, t_tex *texture, int x);
void    set_texture_and_coordinates(t_map *map, t_tex **texture);

#endif