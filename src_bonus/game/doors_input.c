/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:28:01 by renato            #+#    #+#             */
/*   Updated: 2025/11/02 18:04:04 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

bool is_door(t_map *map, int y, int x)
{
    int width;
    
    if (y < 0 || y >= get_map_height(map->map))
        return 0;
    width = (int)ft_strlen(map->map[y]);
    if (x < 0 || x >= width)
        return 0;
    return (map->map[y][x] == 'D');
}

int get_door_id(t_map *map, int y, int x)
{
    int counter;

    counter = 0;
    while (counter < map->num_doors)
    {
        if (map->doors[counter].x == x && map->doors[counter]. y == y)
            return (counter);
        counter++;
    }
    return (-1);
}

void    input_use(t_map *map)
{
    int next_x;
    int next_y;
    int id;
    
    if (map->input.use == 1)
    {
        next_x = (int)floor(map->player.pos_x + map->player.dirX * 0.6);
        next_y = (int)floor(map->player.pos_y + map->player.dirY * 0.6);
        if (is_door(map, next_y, next_x))
        {
            id = get_door_id(map, next_y,  next_x);
            if (map->doors[id].opening_dir == -1)
                map->doors[id].opening_dir = 1;
            else if (map->doors[id].opening_dir == 1)
                map->doors[id].opening_dir = 0;
            else if (map->doors[id].opening_dir == 0)
                map->doors[id].opening_dir = 1;
            map->input.use = 0;
        }
    }
}
