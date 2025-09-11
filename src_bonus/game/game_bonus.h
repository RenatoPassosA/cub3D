/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:50:52 by renato            #+#    #+#             */
/*   Updated: 2025/09/11 13:04:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

#include "../cub3d_bonus.h"
#include "../../mlx/mlx.h"
#include "../graphics/graphics_bonus.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void    init_mlx();
void    init_player();
void    game_loop(void);
int     quit_game(void);
int     keyboard_inputs(t_map *map);
int     on_key_press(int key, t_map *map);
int     on_key_release(int key, t_map *map);
int     is_walkable(t_map *map, int x, int y);
void    rotate_player(t_map *map, double ang);
void    move_axis(t_map *map, double nextX, double nextY, char axis);

int    mouse_movement(int x, int y, void *param);
void    recenter_mouse();
void    init_cam();
void	check_rotate_on_edge(t_map *map);
bool is_door(t_map *map, int y, int x);
int get_door_id(t_map *map, int y, int x);
void    input_use(t_map *map);

void    set_cooldown();
void    relax_recoil();
int on_mouse_press(int button, int x, int y, t_map *map);
void    init_gun();
void    shoot();
void hide_cursor(t_map *map);

#endif