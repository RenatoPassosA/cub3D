/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_player_info.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:05:40 by renato            #+#    #+#             */
/*   Updated: 2025/08/13 18:17:56 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    set_player_direction(t_player *player, char c)
{
    if (c == 'N')
    {
        player->dirX = 0;
        player->dirY = -1;
    }
    else if (c == 'S')
    {
        player->dirX = 0;
        player->dirY = 1;
    }
    else if (c == 'E')
    {
        player->dirX = 1;
        player->dirY = 0;
    }
    else if (c == 'W')
    {
        player->dirX = -1;
        player->dirY = 0;
    }
}

void    set_plane_direction(t_player *player, char c)
{
    if (c == 'N')
    {
        player->planeX = 0.66;
        player->planeY = 0;
    }
    else if (c == 'S')
    {
        player->planeX = -0.66;
        player->planeY = 0;
    }
    else if (c == 'E')
    {
        player->planeX = 0;
        player->planeY = 0.66;
    }
    else if (c == 'W')
    {
        player->planeX = 0;
        player->planeY = -0.66;
    }
}
char    get_player_direction(char **map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (map[y])
    {
        while(map[y][x])
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' ||  map[y][x] == 'W')
                return (map[y][x]);
            x++;
        }
        x = 0;
        y++;
    }
    return ('\0');
}

void    init_player()
{
    t_map   *map;
    char    direction;
    int     *player;
    
    map = get_map_instance();
    direction = get_player_direction(map->map);
    player = get_player_position(map->map);
    set_player_direction(&map->player, direction);
    set_plane_direction(&map->player, direction);
    map->player.posY = player[0] + 0.5;
    map->player.posX = player[1] + 0.5;
    map->player.time = get_current_time_ms();
    map->player.old_time = map->player.time;
    map->player.frame_time = 0;
    map->player.rotate_speed = 0;
    map->player.move_speed = 0;
    free(player);
    for (int i = 0; map->map[i] != NULL; i++)           // percorre linhas
	{
		for (int j = 0; map->map[i][j] != '\0'; j++)    // percorre caracteres da linha
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E')
				map->map[i][j] = '0';
		}
	}
}

