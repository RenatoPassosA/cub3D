/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render_floor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:21:29 by renato            #+#    #+#             */
/*   Updated: 2025/09/11 11:25:00 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"

void    render_floor_and_ceiling()
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
    int x;
    float posZ;
    double rowDistance;
    double floorStepX;
    double floorStepY;
    double floorX;
    double floorY;
    int cellX;
    int cellY;
    int tx;
    int ty;
    double fracX;
    double fracY;
    int p;
 
    horizon = SCREEN_HEIGHT / 2 + map->cam.pitch_offset ;
   
    
    posZ = 0.5 * SCREEN_HEIGHT;
    rayDirX0 = map->player.dirX - map->player.planeX;
    rayDirY0 = map->player.dirY - map->player.planeY;
    rayDirX1 = map->player.dirX + map->player.planeX;
    rayDirY1 = map->player.dirY + map->player.planeY;


    y = 0;
    x = 0;
    while (y < horizon - 1)
    {
        p = horizon - y;
        if (p <= 0)
        {
            y++;
            continue ;
        }
        rowDistance = posZ / p;  
        floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
        floorX = map->player.posX + rowDistance * rayDirX0;
        floorY = map->player.posY + rowDistance * rayDirY0;

        while (x < SCREEN_WIDTH)
        {
            cellX = (int)(floorX);
            cellY = (int)(floorY);

            fracX = floorX - cellX;
            fracY = floorY - cellY;

            
            tx = (int)(map->textures[5].width * fracX) & (map->textures[5].width - 1);
            ty = (int)(map->textures[5].height * fracY) & (map->textures[5].height - 1);

            data->color = texel_at(&map->textures[5], tx, ty);
            data->bytes = map->mlx.bits_per_pixel / 8;
            data->offset = y * map->mlx.size_line + x * data->bytes;
            *(uint32_t *)(map->mlx.img_data + data->offset) = data->color;
            floorX += floorStepX;
            floorY += floorStepY;
            x++;
        }
        x = 0;
        y++;
    }
    
    y = horizon + 1;
    while (y < SCREEN_HEIGHT - 1)
    {
        p = y - horizon;
        rowDistance = posZ / p;  
        floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
        floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
        floorX = map->player.posX + rowDistance * rayDirX0;
        floorY = map->player.posY + rowDistance * rayDirY0;

        while (x < SCREEN_WIDTH)
        {
            cellX = (int)(floorX);
            cellY = (int)(floorY);

            fracX = floorX - cellX;
            fracY = floorY - cellY;

            
            tx = (int)(map->textures[4].width * fracX) & (map->textures[4].width - 1);
            ty = (int)(map->textures[4].height * fracY) & (map->textures[4].height - 1);

            data->color = texel_at(&map->textures[4], tx, ty);
            data->bytes = map->mlx.bits_per_pixel / 8;
            data->offset = y * map->mlx.size_line + x * data->bytes;
            *(uint32_t *)(map->mlx.img_data + data->offset) = data->color;
            floorX += floorStepX;
            floorY += floorStepY;
            x++;
        }
        x = 0;


        y++;
    }
}
