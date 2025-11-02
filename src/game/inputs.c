/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:59:03 by renato            #+#    #+#             */
/*   Updated: 2025/11/02 18:04:04 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void    input_w(t_map *map)
{
    double nextX;
    double nextY;

    nextX = map->player.pos_x + map->player.dirX * map->player.move_speed;
    nextY = map->player.pos_y + map->player.dirY * map->player.move_speed;
    move_axis(map, nextX, map->player.pos_y, 'X');
    move_axis(map, map->player.pos_x, nextY, 'Y');
}

static void    input_s(t_map *map)
{
    double nextX;
    double nextY;

    nextX = map->player.pos_x - map->player.dirX * map->player.move_speed;
    nextY = map->player.pos_y - map->player.dirY * map->player.move_speed;
    move_axis(map, nextX, map->player.pos_y, 'X');
    move_axis(map, map->player.pos_x, nextY, 'Y');
}

static void    input_a(t_map *map)
{
    double nextX;
    double nextY;
    
    nextX = map->player.pos_x - map->player.planeX * map->player.move_speed;
    nextY = map->player.pos_y - map->player.planeY * map->player.move_speed;
    move_axis(map, nextX, map->player.pos_y, 'X');
    move_axis(map, map->player.pos_x, nextY, 'Y');
}

static void    input_d(t_map *map)
{
    double nextX;
    double nextY;
    
    nextX = map->player.pos_x + map->player.planeX * map->player.move_speed;
    nextY = map->player.pos_y + map->player.planeY * map->player.move_speed;
    move_axis(map, nextX, map->player.pos_y, 'X');
    move_axis(map, map->player.pos_x, nextY, 'Y');
}

int    keyboard_inputs(t_map *map)
{
 
    if (map->input.esc)
		quit_game();
	else if (map->input.w)
        input_w(map);
	else if (map->input.s)
	    input_s(map);
	else if (map->input.a)
	    input_a(map);
	else if (map->input.d)
        input_d(map);
    else if (map->input.left)
        rotate_player(map, -map->player.rotate_speed);
    else if (map->input.right)
        rotate_player(map, map->player.rotate_speed);
    return (0);
}

