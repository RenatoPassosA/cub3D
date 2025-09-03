/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:14:41 by renato            #+#    #+#             */
/*   Updated: 2025/09/03 10:54:32 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"


static int in_bounds(int x, int y)
{
    t_map *map;

    map = get_map_instance();
    return (y >= 0 && y < get_map_height(map->map) && x >= 0 && x < get_line_width(map->map[0]));
}

static int is_wall_like_xy(int x, int y)
{
    char c;
    
    if (!in_bounds(x, y))
        return (1);
    c = get_map_instance()->map[y][x];
    return (c == '1');
}

int door_orientation(int y, int x)
{
    int L;
    int R;
    int U;
    int D;
    
    if (!in_bounds(x, y))
        return (0);
    L = is_wall_like_xy(x - 1, y);
    R = is_wall_like_xy(x + 1, y);
    U = is_wall_like_xy(x, y - 1);
    D = is_wall_like_xy(x, y + 1);
    if (L && R && !(U && D))
        return (DOOR_HORIZONTAL);
    if (U && D && !(L && R))
        return (DOOR_VERTICAL);
    return (DOOR_VERTICAL);
}

int    doors_counter()
{
    t_map *map;
    int doors_counter;
    int x;
    int y;

    map = get_map_instance();
    doors_counter = 0;
    x = 0;
    y = 0;

    while (y < get_map_height(map->map))
    {
        while (x < get_line_width(map->map[0]))
        {
            if (map->map[y][x] == 'D')
                doors_counter++;
            x++;
        }
        x = 0;
        y++;
    }
    return (doors_counter);
}

t_door    create_door(int y, int x)
{
    t_door door;

    door.x = x;
    door.y = y;
    door.orientation = door_orientation(y, x);
    door.is_open = false;
	door.opened_at = 0;
    door.open_amount = 0.0;
    door.opening_dir = 0;
    return (door);
}
void    fill_door_data(t_map *map)
{
    int x;
    int y;
    int index;

    x = 0;
    y = 0;
    index = 0;
    while (y < get_map_height(map->map))
    {
        while (x < get_line_width(map->map[0]))
        {
            if (map->map[y][x] == 'D')
            {
                map->doors[index] = create_door(y, x);
                index++;
            }
            x++;
        }
        x = 0;
        y++;
    }
    
}

void    init_door()
{
    t_map *map;

    map = get_map_instance();
    map->num_doors = doors_counter();
    if (map->num_doors)
    {
        map->doors = (t_door *)malloc(sizeof(t_door) * map->num_doors);
        if (!map->doors)
            quit_game();
        fill_door_data(map);
    }  
}


void	door_animation(double delta_time)
{
	t_map *map;
	float speed;
	int	counter;
    long long now;

    now = get_current_time_ms();
	if (delta_time > 0.1)
		delta_time = 0.1;
	map = get_map_instance();
	speed = 0.5;
	counter = 0;
	while (counter < map->num_doors)
	{
        map->doors[counter].open_amount += map->doors[counter].opening_dir * speed * delta_time;
        if (map->doors[counter].opening_dir == 1)
        {
            
            if (map->doors[counter].open_amount >= 1.0)
            {
			    map->doors[counter].open_amount = 1.0;
                map->doors[counter].opened_at = now;
                map->doors[counter].opening_dir = 0;
                map->doors[counter].is_open = true;
            }
        }
        else if (map->doors[counter].opening_dir == 0 && map->doors[counter].is_open == true && (now - map->doors[counter].opened_at > 2000))
            map->doors[counter].opening_dir = -1;
        else if (map->doors[counter].opening_dir == -1)
        {
            if (map->doors[counter].open_amount <= 0.0)
            {
			    map->doors[counter].open_amount = 0.0;
                map->doors[counter].opening_dir = 0;
                map->doors[counter].is_open = false;
            }
        }
        counter++;
	}
}


