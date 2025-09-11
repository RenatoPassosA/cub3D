/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:45:05 by renato            #+#    #+#             */
/*   Updated: 2025/09/11 12:05:17 by renato           ###   ########.fr       */
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
void init_sprites();
void	door_animation(double delta_time);
void    draw_doors(t_map *map, int x);
void    set_door_height(t_map *map);
void    render_decorative_sprites(void *sprite);
void    init_monster_type();
void    render_monsters(void *monster);
void    init_monsters();

void    render_sprites();
void    set_monsters_projection();
void    monster_animation();
void    set_monsters_projection();
void    sort_monsters(t_map *map);
void    set_sprites_projection();
void    sort_sprites(t_map *map);
void    set_render_list();
void    set_priority_order();
void    check_damaged_monster();
#endif