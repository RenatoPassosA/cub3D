/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:55:41 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/30 12:29:44 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_map_height(char **map)
{
    int height;

    height = 0;
    while (map[height])
        height++;
    return (height);
}

int *fill_position(int *position, int x, int y)
{
    position[0] = x;
    position[1] = y;
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
        clean_all_and_message_error("Error on malloc.", NULL, map);
    while (x < get_map_height(map))
    {
        while (y < get_line_width(map[x]))
        {
            if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'W' || 
                map[x][y] == 'E')
                    return(fill_position(position, x, y));
                y++;
        }
        y = 0;
        x++;
    }
    free(position);
    return(NULL);
}

char **copy_map(char **map)
{
    int height = 0;
    char **map_copy;
    int i;

    height = get_map_height(map);
    map_copy = (char **)malloc(sizeof(char *) * (height + 1));
    if (!map_copy)
        return (NULL);
    i = 0;
    while (i < height)
    {
        map_copy[i] = ft_strdup(map[i]);
        if (!map_copy[i])
        {
            while (--i >= 0)
                free(map_copy[i]);
            free(map_copy);
            return (NULL);
        }
        i++;
    }
    map_copy[i] = NULL;
    return (map_copy);
}

void run_flood_fill(char **map, char **flood_fill_map, int x, int y)
{
    if (x < 0 || y < 0)
        return ;
    if (x >= get_map_height(flood_fill_map) || y >= get_line_width(flood_fill_map[x]))
        return ;
    if (flood_fill_map[x][y] == ' ' || flood_fill_map[x][y] == '\0')
    {   
        free_bidimensional_array(flood_fill_map);
        clean_all_and_message_error("Error.\nMap is not closed or holes on the floor", NULL, map);
    }
    if (flood_fill_map[x][y] != '0' && flood_fill_map[x][y] != 'N' &&
        flood_fill_map[x][y] != 'S' && flood_fill_map[x][y] != 'W' && flood_fill_map[x][y] != 'E')
        return;
    flood_fill_map[x][y] = 'F';
    run_flood_fill(map, flood_fill_map, x + 1, y);
    run_flood_fill(map, flood_fill_map, x - 1, y);
    run_flood_fill(map, flood_fill_map, x, y + 1);
    run_flood_fill(map, flood_fill_map, x, y - 1);
}

void    flood_fill(char **map)
{
    int *player_position;
    char **flood_fill_map;

    flood_fill_map = copy_map(map);
    if (!flood_fill_map)
        clean_all_and_message_error("Failed to copy map", NULL, map);
    player_position = get_player_position(flood_fill_map);
    if (!player_position)
    {
        free_bidimensional_array(flood_fill_map);
        clean_all_and_message_error("Player position not found", NULL, map);
    }
    outside_flood_fill(map, flood_fill_map);
    run_flood_fill(map, flood_fill_map, player_position[0], player_position[1]);
    if (!find_isolated_spaces(flood_fill_map))
    {
        free_bidimensional_array(flood_fill_map);
        clean_all_and_message_error("Error. Map contains isolated intern space", NULL, map);
    }
    free(player_position);
    free_bidimensional_array(flood_fill_map); //aqui o mapa está com F em toda a area acessível ao player
}
