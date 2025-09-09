/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:59:03 by renato            #+#    #+#             */
/*   Updated: 2025/09/09 10:37:17 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "../graphics/graphics_bonus.h"

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
    else if (key == KEY_ESC)
        map->input.esc = 1;
    else if (key == KEY_E)
        map->input.use = 1;
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
    else if (key == KEY_ESC)
        map->input.esc = 0;
    else if (key == KEY_E)
        map->input.use = 0;
    return (0);
}

int is_walkable(t_map *map, int y, int x)
{
    int width;
    int     counter;
    
    counter = 0;
    if (y < 0 || y >= get_map_height(map->map))
        return 0;
    width = (int)ft_strlen(map->map[y]);
    if (x < 0 || x >= width)
        return 0;
    while (counter < map->num_sprites)
    {
        if ((int)map->sprites[counter].x == x && (int)map->sprites[counter].y == y && map->sprites[counter].collision)
            return 0;
        counter++;
    }
    return (map->map[y][x] == '0');
}

void move_axis(t_map *map, double next_x, double next_y, char axis)
{
    int target_cell_x;
    int target_cell_y;
    int door_id;
    if (axis == 'X')
    {
        target_cell_x = (int)floor(next_x);
        target_cell_y = (int)floor(map->player.posY);
        if (is_walkable(map, target_cell_y, target_cell_x))
            map->player.posX = next_x;
        else if (is_door(map, target_cell_y, target_cell_x))
        {
            door_id = get_door_id(map, target_cell_y, target_cell_x);
            if (map->doors[door_id].open_amount >= DOOR_THRESHOLD)
                map->player.posX = next_x;
        }
    }
    else
    {
        target_cell_x = (int)floor(map->player.posX);
        target_cell_y = (int)floor(next_y);
        if (is_walkable(map, target_cell_y, target_cell_x))
            map->player.posY = next_y;
        else if (is_door(map, target_cell_y, target_cell_x))
        {
            door_id = get_door_id(map, target_cell_y, target_cell_x);
            if (map->doors[door_id].open_amount >= DOOR_THRESHOLD)
                map->player.posY = next_y;
        }
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
