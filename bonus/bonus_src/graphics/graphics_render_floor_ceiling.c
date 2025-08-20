/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render_floor_ceiling2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:21:29 by renato            #+#    #+#             */
/*   Updated: 2025/08/18 17:06:06 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    render_floor_ceiling()
{
    t_map *map;
    t_render *data;

    map = get_map_instance();
    data = &map->render_data;

    float rayDirX0;
    float rayDirY0;
    float rayDirX1;
    float rayDirY1;
    int horizon;
    int y;
    float posZ;
    float rowDistance;
    float floorStepX;
    float floorStepY;
    float floorX;
    float floorY;
    int cellX;
    int cellY;
    int tx;
    int ty;
    double fracX;
    double fracY;
    int floor_color;
    int ceiling_color;


    rayDirX0 = map->player.dirX - map->player.planeX;
    rayDirY0 = map->player.dirY - map->player.planeY;
    rayDirX1 = map->player.dirX + map->player.planeX;
    rayDirY1 = map->player.dirY + map->player.planeY;
    horizon = y - SCREEN_HEIGHT / 2;
    posZ = 0.5 * SCREEN_HEIGHT;
    rowDistance = posZ / horizon;
    floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
    floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
    floorX = map->player.posX + rowDistance * rayDirX0;
    floorY = map->player.posY + rowDistance * rayDirY0;
    
    while (y < SCREEN_HEIGHT - 1)
    {
        if (horizon == 0)
            continue;
        cellX = (int)(floorX);
        cellY = (int)(floorY);

        fracX = floorX - cellX;
        fracY = floorY - cellY;

        
        tx = (int)(texWidth * fracX) & (texWidth - 1);
        ty = (int)(texHeight * fracY) & (texHeight - 1);

        floorX += floorStepX;
        floorY += floorStepY;
        
       
    
        y++;
    }

    
}