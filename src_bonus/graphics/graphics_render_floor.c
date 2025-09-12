/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render_floor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:21:29 by renato            #+#    #+#             */
/*   Updated: 2025/09/12 10:51:20 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"

void    render_floor_and_ceiling()
{
    t_map *map;
    t_render *data;
    t_tex   *texture;
    
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
    texture = &map->textures[5];
    if (map->player.is_high)
        texture = &map->textures[18];
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

            
            tx = (int)(texture->width * fracX) & (texture->width - 1);
            ty = (int)(texture->height * fracY) & (texture->height - 1);
            if (map->player.is_high)
                trippy_effect(map, y, &ty, texture);
            data->color = texel_at(texture, tx, ty);
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
    


    texture = &map->textures[4];
    if (map->player.is_high)
        texture = &map->textures[18];
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

            
            tx = (int)(texture->width * fracX) & (texture->width - 1);
            ty = (int)(texture->height * fracY) & (texture->height - 1);

            if (map->player.is_high)
                trippy_effect(map, y, &ty, texture);
            data->color = texel_at(texture, tx, ty);
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
