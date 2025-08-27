/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:59:03 by renato            #+#    #+#             */
/*   Updated: 2025/08/26 15:12:05 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

int on_key_press(int key, t_map *map)
{ 
    if (key == KEY_W)
        map->input.w = 1;
    else if (key == KEY_S)
        map->input.s = 1;
    else if (key == KEY_A)
        map->input.a = 1;
    else if (key == KEY_D)
        map->input.d = 1;
    // else if (key == KEY_LEFT)   
    //     map->input.left  = 1;
    // else if (key == KEY_RIGHT)
    //     map->input.right = 1;
    else if (key == KEY_ESC)
        map->input.esc = 1;
    return (0);
}

int on_key_release(int key, t_map *map)
{
    if (key == KEY_W)
        map->input.w = 0;
    else if (key == KEY_S)
        map->input.s = 0;
    else if (key == KEY_A)
        map->input.a = 0;
    else if (key == KEY_D)
        map->input.d = 0;
    // else if (key == KEY_LEFT)   
    //     map->input.left  = 0;
    // else if (key == KEY_RIGHT)
    //     map->input.right = 0;
    else if (key == KEY_ESC)
        map->input.esc = 0;
    return (0);
}

int is_walkable(t_map *map, int x, int y)
{
    int width;
    
    if (y < 0 || y >= get_map_height(map->map))
        return 0;
    width = (int)ft_strlen(map->map[y]);
    if (x < 0 || x >= width)
        return 0;
    return (map->map[y][x] == '0');
}

void move_axis(t_map *map, double nextX, double nextY, char axis)
{
    int targetCellX;
    int targetCellY;
    if (axis == 'X')
    {
        targetCellX = (int)floor(nextX);
        targetCellY = (int)floor(map->player.posY);
        if (is_walkable(map, targetCellX, targetCellY))
            map->player.posX = nextX;
    }
    else
    {
        targetCellX = (int)floor(map->player.posX);
        targetCellY = (int)floor(nextY);
        if (is_walkable(map, targetCellX, targetCellY))
            map->player.posY = nextY;
    }
}

void rotate_player(t_map *map, double ang)
{
    double oldDirX;
    double oldPlaneX;
    double c;
    double s;
    
    oldDirX = map->player.dirX;
    oldPlaneX = map->player.planeX;
    c = cos(ang);
    s = sin(ang);

    map->player.dirX = map->player.dirX * c - map->player.dirY * s;
    map->player.dirY = oldDirX * s + map->player.dirY * c;
    map->player.planeX = map->player.planeX * c - map->player.planeY * s;
    map->player.planeY = oldPlaneX * s + map->player.planeY * c;
}
