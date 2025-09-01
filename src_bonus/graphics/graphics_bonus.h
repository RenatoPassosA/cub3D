/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:05 by renato            #+#    #+#             */
/*   Updated: 2025/08/29 13:07:55 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_BONUS_H
# define GRAPHICS_BONUS_H

#include "../cub3d_bonus.h"
#include "../../mlx/mlx.h"

void    render();
void	init_textures();
void    set_wall_height(t_map *map);
void    draw_floor(t_map *map, int x);
void    draw_ceiling(t_map *map, int x);
uint32_t texel_at(const t_tex *t, int tx, int ty);
void    draw_walls(t_map *map, t_tex *texture, int x);
void    set_texture_and_coordinates(t_map *map, t_tex **texture);

void    render_floor_and_ceiling();




void    render_minimap();
void    init_minimap_data();
void init_door();
void	door_animation(double delta_time);
void    draw_doors(t_map *map, int x);
void    set_door_height(t_map *map);

#endif