/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:59:03 by renato            #+#    #+#             */
/*   Updated: 2025/08/29 12:42:20 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

static void    input_w(t_map *map)
{
    double next_x;
    double next_y;

    next_x = map->player.posX + map->player.dirX * map->player.move_speed;
    next_y = map->player.posY + map->player.dirY * map->player.move_speed;
    move_axis(map, next_x, map->player.posY, 'X');
    move_axis(map, map->player.posX, next_y, 'Y');
}

static void    input_s(t_map *map)
{
    double next_x;
    double next_y;

    next_x = map->player.posX - map->player.dirX * map->player.move_speed;
    next_y = map->player.posY - map->player.dirY * map->player.move_speed;
    move_axis(map, next_x, map->player.posY, 'X');
    move_axis(map, map->player.posX, next_y, 'Y');
}

static void    input_a(t_map *map)
{
    double next_x;
    double next_y;
    
    next_x = map->player.posX - map->player.planeX * map->player.move_speed;
    next_y = map->player.posY - map->player.planeY * map->player.move_speed;
    move_axis(map, next_x, map->player.posY, 'X');
    move_axis(map, map->player.posX, next_y, 'Y');
}

static void    input_d(t_map *map)
{
    double next_x;
    double next_y;
    
    next_x = map->player.posX + map->player.planeX * map->player.move_speed;
    next_y = map->player.posY + map->player.planeY * map->player.move_speed;
    move_axis(map, next_x, map->player.posY, 'X');
    move_axis(map, map->player.posX, next_y, 'Y');
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
    else if (map->input.use)
        input_use(map);
    return (0);
}
