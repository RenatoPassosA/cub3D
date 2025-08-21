/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:50:52 by renato            #+#    #+#             */
/*   Updated: 2025/08/21 11:27:37 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include "../cub3d.h"
#include "../../../mlx/mlx.h"
#include "../graphics/graphics.h"

#include <X11/X.h>

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

#endif