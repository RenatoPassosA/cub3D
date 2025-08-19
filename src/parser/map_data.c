/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:19:51 by renato            #+#    #+#             */
/*   Updated: 2025/08/19 13:55:25 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int get_rgb(int r, int g, int b)
{
	return (r << 16) | (g << 8) | b;
}

static int get_color(char *rgb)
{
    char	**colors;
    int color;

    colors = ft_split(rgb, ',');
    color = get_rgb(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
    free_bidimensional_array(colors);
    return (color);
}

static void get_identifier_content(t_map *map_data, char ***content)
{
    int index;

    index = -1;
    while (content[++index])
    {
        if (ft_strcmp(content[index][0], "\n") == 0)
        {
            index++;
			continue;
        }
        if (ft_strcmp(content[index][0], "1") == 0)
			break;
        if (ft_strcmp(content[index][0], "NO") == 0)
		    map_data->NO_texture = ft_strdup(content[index][1]);
        else if (ft_strcmp(content[index][0], "SO") == 0)
            map_data->SO_texture = ft_strdup(content[index][1]);
        else if (ft_strcmp(content[index][0], "WE") == 0)
            map_data->WE_texture = ft_strdup(content[index][1]);
        else if (ft_strcmp(content[index][0], "EA") == 0)
            map_data->EA_texture = ft_strdup(content[index][1]);
        else if (ft_strcmp(content[index][0], "F") == 0)
            map_data->floor_rgb = get_color(content[index][1]);
        else if (ft_strcmp(content[index][0], "C") == 0)
            map_data->ceiling_rgb = get_color(content[index][1]);
    } 
}

static t_validation_status get_map(t_map *map_data, char **map)
{
    int size;
    int index;

    size = get_arr_size(map);
    index = 0;

    map_data->map = (char **)malloc(sizeof(char *) * (size + 1));
    if (!map_data->map)
        return(ERR_MALLOC_CONTENT);
    while (map[index])
    {
        map_data->map[index] = ft_strdup(map[index]);
        index++;
    }
    map_data->map[index] = NULL;
    return(VALIDATION_OK);
}

t_validation_status    set_map_data(char ***content, char **map)
{
    t_map   *map_data;

    map_data = get_map_instance();
    get_identifier_content(map_data, content);
    if (get_map(map_data, map) != VALIDATION_OK)
        return(ERR_MALLOC_CONTENT);
    return(VALIDATION_OK);
}
 