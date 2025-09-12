/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_high.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:58:54 by renato            #+#    #+#             */
/*   Updated: 2025/09/12 10:11:10 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void check_mush(t_map *map)
{
    int width;
    int y;
    int x;
    int counter;
    
    y = (int)map->player.posY;
    x = (int)map->player.posX;
    counter = 0;
    if (y < 0 || y >= get_map_height(map->map))
        return ;
    width = (int)ft_strlen(map->map[y]);
    if (x < 0 || x >= width)
        return ;
    while (counter < map->num_sprites)
    {
        if (x == (int)map->sprites[counter].x && y == (int)map->sprites[counter].y)
            if (map->sprites[counter].is_mush)
            {
                map->player.is_high = true;
                map->sprites[counter].is_visible = false;
            }
        counter++;
        
    }
}

void    check_high()
{
    t_map *map;

    map = get_map_instance();
    if (map->player.is_high)
    {
        map->time_accumulator += map->player.frame_time;
        if (map->frame_index >= 17)
            map->frame_index = 14;
        if (map->time_accumulator >= map->frame_duration)
        {
            map->frame_index++;
            map->time_accumulator = 0;
        }
        map->player.trippy_duration -= map->player.frame_time;
        map->player.trippy_phase += map->player.frame_time;
        if (map->player.trippy_duration <= 0)
        {
            map->player.is_high = 0;
            map->player.trippy_phase = 0;
        }
    }
}