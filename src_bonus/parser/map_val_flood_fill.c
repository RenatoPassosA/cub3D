/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 09:55:41 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 13:55:06 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char **copy_map(char **map)
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

static t_validation_status run_flood_fill(char **map, char **flood_fill_map, int x, int y)
{
    t_validation_status status;
    
    if (x < 0 || y < 0)
        return (VALIDATION_OK);
    if (x >= get_map_height(flood_fill_map) || y >= get_line_width(flood_fill_map[x]))
         return (VALIDATION_OK);
    if (flood_fill_map[x][y] == ' ' || flood_fill_map[x][y] == '\0')
        return (ERR_MAP_OPEN);
    if (flood_fill_map[x][y] != '0' && flood_fill_map[x][y] != 'N' &&
        flood_fill_map[x][y] != 'S' && flood_fill_map[x][y] != 'W' && flood_fill_map[x][y] != 'E')
         return (VALIDATION_OK);
    flood_fill_map[x][y] = 'F';
    status = run_flood_fill(map, flood_fill_map, x + 1, y);
    if (status != VALIDATION_OK)
        return (status);
    status = run_flood_fill(map, flood_fill_map, x - 1, y);
    if (status != VALIDATION_OK)
        return (status);
    status = run_flood_fill(map, flood_fill_map, x, y + 1);
    if (status != VALIDATION_OK)
        return (status);
    status = run_flood_fill(map, flood_fill_map, x, y - 1);
    if (status != VALIDATION_OK)
        return (status);
    return (VALIDATION_OK);
}

t_validation_status clean_and_return_status(t_validation_status status, int *player_position, char **flood_fill_map)
{
    if (player_position)
        free(player_position);
    free_bidimensional_array(flood_fill_map);
    return (status);
}

t_validation_status    flood_fill(char **map)
{
    int *player_position;
    char **flood_fill_map;
    t_validation_status status;

    flood_fill_map = copy_map(map);
    if (!flood_fill_map)
        return(ERR_COPY_MAP);
    player_position = get_player_position(flood_fill_map);
    if (!player_position)
        return (clean_and_return_status(ERR_NO_PLAYER, NULL, flood_fill_map));
    status = outside_flood_fill(map, flood_fill_map);
    if (status != VALIDATION_OK)
        return (clean_and_return_status(status, player_position, flood_fill_map));
    status = run_flood_fill(map, flood_fill_map, player_position[0], player_position[1]);
    if (status != VALIDATION_OK)
        return (clean_and_return_status(status, player_position, flood_fill_map));
    if (!find_isolated_spaces(flood_fill_map))
       return (clean_and_return_status(ERR_INTER_SPACE, player_position, flood_fill_map));
    free(player_position);
    free_bidimensional_array(flood_fill_map);
    return(VALIDATION_OK);
}
