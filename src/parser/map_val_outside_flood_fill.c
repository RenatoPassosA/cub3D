/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_outside_flood_fill.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:52:45 by renato            #+#    #+#             */
/*   Updated: 2025/08/11 10:31:04 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


t_validation_status run_outside_flood_fill(char **map, char **flood_fill_map, int x, int y)
{
	t_validation_status status;

	if (x < 0 || y < 0)
		return (VALIDATION_OK);
	if (x >= get_map_height(flood_fill_map) || y >= get_line_width(flood_fill_map[x]))
		return (VALIDATION_OK);
	if (flood_fill_map[x][y] == '1' || flood_fill_map[x][y] == '|')
		return (VALIDATION_OK);
	if (flood_fill_map[x][y] == ' ')
		flood_fill_map[x][y] = '|';
	else if (flood_fill_map[x][y] == '0' || flood_fill_map[x][y] == 'N' ||
			 flood_fill_map[x][y] == 'S' || flood_fill_map[x][y] == 'E' ||
			 flood_fill_map[x][y] == 'W')
		return (ERR_MAP_OPEN);
	status = run_outside_flood_fill(map, flood_fill_map, x + 1, y);
	if (status != VALIDATION_OK)
		return status;
	status = run_outside_flood_fill(map, flood_fill_map, x - 1, y);
	if (status != VALIDATION_OK)
		return status;
	status = run_outside_flood_fill(map, flood_fill_map, x, y + 1);
	if (status != VALIDATION_OK)
		return status;
	status = run_outside_flood_fill(map, flood_fill_map, x, y - 1);
	if (status != VALIDATION_OK)
		return status;
	return (VALIDATION_OK);
}

t_validation_status    check_bottom_and_top(char **map, char **flood_fill_map, int x_index)
{
	t_validation_status status;
    int y_index;

    y_index = 0;
    while (map[x_index][y_index])
    {
        if (map[x_index][y_index] == ' ')
		{
			status = run_outside_flood_fill(map, flood_fill_map, x_index, y_index);
			if (status == ERR_MAP_OPEN)
				return(status);
		}
        y_index++;
    }
	return (VALIDATION_OK);
}

t_validation_status    check_middle_line(char **map, char **flood_fill_map, int x_index)
{
	t_validation_status status;
    int width;
    
    width = get_line_width(map[x_index]);
    if (map[x_index][0] == ' ')
	{
        status = run_outside_flood_fill(map, flood_fill_map, x_index, 0);
		if (status == ERR_MAP_OPEN)
			return(status);
	}
    if (map[x_index][width - 1] == ' ')
	{
       status =  run_outside_flood_fill(map, flood_fill_map, x_index, width - 1);
	   if (status == ERR_MAP_OPEN)
			return(status);
	}
	return (VALIDATION_OK);
}

t_validation_status    outside_flood_fill(char **map, char **flood_fill_map)
{
    int x;
    int height;
	t_validation_status status;

    x = 1;
    height = get_map_height(map);
    status = check_bottom_and_top(map, flood_fill_map, 0);
	if (status == ERR_MAP_OPEN)
		return(status);
    status = check_bottom_and_top(map, flood_fill_map, height - 1);
	if (status == ERR_MAP_OPEN)
		return(status);
    while (x < get_map_height(map))
    {
        status = check_middle_line(map, flood_fill_map, x);
		if (status == ERR_MAP_OPEN)
			return(status);
        x++;
    }
	return (VALIDATION_OK);
}


