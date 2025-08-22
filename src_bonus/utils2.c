/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:19:18 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 14:03:35 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int get_map_height(char **map)
{
    int height;

    height = 0;
    while (map[height])
        height++;
    return (height);
}

static int *fill_position(int *position, int x, int y)
{
    position[0] = y;
    position[1] = x;
    return (position);
}

int *get_player_position(char **map)
{
    int *position;
    int x;
    int y;

    x = 0;
    y = 0;
    position = (int *)malloc(sizeof(int) * 2);
    if (!position)
        return(NULL);
    while (y < get_map_height(map))
    {
        while (x < get_line_width(map[y]))
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W' || 
                map[y][x] == 'E')
                   return(fill_position(position, x, y));
            x++;
        }
        x = 0;
        y++;
    }
    free(position);
    return(NULL);
}




