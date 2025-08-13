/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:59:03 by renato            #+#    #+#             */
/*   Updated: 2025/08/13 17:39:15 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int is_walkable(t_map *map, int x, int y)
{
    int width;
    
    if (y < 0 || y >= get_map_height(map->map))           // altura
        return 0;
    width = (int)ft_strlen(map->map[y]);    // largura da linha y
    if (x < 0 || x >= width)
        return 0;
    return (map->map[y][x] == '0');             // célula livre
}

int    keyboard_inputs(int key)
{
    printf("Key pressed: %d\n", key);
    double oldDirX;
    double oldPlaneX;
    double nextX;
    double nextY;
    t_map   *map;

    map = get_map_instance();
    
    oldDirX = 0;
    oldPlaneX = 0;
    printf("----posX:%f\n", map->player.posX);
    printf("----posY:%f\n", map->player.posY);
    printf("----MS:%f\n", map->player.move_speed);
    printf("----dirX:%f\n", map->player.dirX);
    printf("----dirY:%f\n", map->player.dirY);
    if (key == KEY_ESC)
		exit(1);
	else if (key == KEY_W)
    {
        nextX = map->player.posX + map->player.dirX * map->player.move_speed;
        nextY = map->player.posY + map->player.dirY * map->player.move_speed;
        
        if (is_walkable(map, (int)floor(nextX), (int)floor(map->player.posY)))
            map->player.posX = nextX;
        if (is_walkable(map, (int)floor(map->player.posX), (int)floor(nextY)))
            map->player.posY = nextY;
    }
    
	else if (key == KEY_S)
	{
        nextX = map->player.posX - map->player.dirX * map->player.move_speed;
        nextY = map->player.posY - map->player.dirY * map->player.move_speed;
        if (is_walkable(map, (int)floor(nextX), (int)floor(map->player.posY)))
            map->player.posX = nextX;
        if (is_walkable(map, (int)floor(map->player.posX), (int)floor(nextY)))
            map->player.posY = nextY;

    }
	else if (key == KEY_A)
	{
        nextX = map->player.posX - map->player.planeX * map->player.move_speed;
        nextY = map->player.posY - map->player.planeY * map->player.move_speed;
        if (is_walkable(map, (int)floor(nextX), (int)floor(map->player.posY)))
            map->player.posX = nextX;
        if (is_walkable(map, (int)floor(map->player.posX), (int)floor(nextY)))
            map->player.posY = nextY;
    }
	else if (key == KEY_D)
    {
        nextX = map->player.posX + map->player.planeX * map->player.move_speed;
        nextY = map->player.posY + map->player.planeY * map->player.move_speed;
        if (is_walkable(map, (int)floor(nextX), (int)floor(map->player.posY)))
            map->player.posX = nextX;
        if (is_walkable(map, (int)floor(map->player.posX), (int)floor(nextY)))
            map->player.posY = nextY;

    }
    else if (key == KEY_LEFT) //esquerda
    {
        oldDirX = map->player.dirX;
        map->player.dirX = map->player.dirX * cos(-map->player.rot_speed) - map->player.dirY * sin(-map->player.rot_speed);
        map->player.dirY = oldDirX * sin(-map->player.rot_speed) + map->player.dirY * cos(-map->player.rot_speed);

        oldPlaneX = map->player.planeX;
        map->player.planeX = map->player.planeX * cos(-map->player.rot_speed) - map->player.planeY * sin(-map->player.rot_speed);
        map->player.planeY = oldPlaneX * sin(-map->player.rot_speed) + map->player.planeY * cos(-map->player.rot_speed);
    }
    else if (key == KEY_RIGHT) //direita
    {
        oldDirX = map->player.dirX;
        map->player.dirX = map->player.dirX * cos(map->player.rot_speed) - map->player.dirY * sin(map->player.rot_speed);
        map->player.dirY = oldDirX * sin(map->player.rot_speed) + map->player.dirY * cos(map->player.rot_speed);

        oldPlaneX = map->player.planeX;
        map->player.planeX = map->player.planeX * cos(map->player.rot_speed) - map->player.planeY * sin(map->player.rot_speed);
        map->player.planeY = oldPlaneX * sin(map->player.rot_speed) + map->player.planeY * cos(map->player.rot_speed);
    } 	
    return (0);
}

