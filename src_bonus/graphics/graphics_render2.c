/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:49 by renato            #+#    #+#             */
/*   Updated: 2025/09/03 16:44:51 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"

void    set_texture_and_coordinates(t_map *map, t_tex **texture)
{
    int texture_index;
    t_render *data;

    data = &map->render_data;
    if (data->side == 0 && data->rayDirX > 0)
        texture_index = WE;
    else if (data->side == 0 && data->rayDirX < 0)
        texture_index = EA;
    else if (data->side == 1 && data->rayDirY > 0)
        texture_index = NO;
    else if (data->side == 1 && data->rayDirY < 0)
        texture_index = SO;
    *texture = &map->textures[texture_index];
    if (data->side == 0)
        data->wallX = map->player.posY + data->perpWallDist * data->rayDirY;
    else
        data->wallX = map->player.posX + data->perpWallDist * data->rayDirX;

    data->wallX = data->wallX - floor(data->wallX);    
    data->tx = (int)(data->wallX * (*texture)->width);

    if (data->side == 0 && data->rayDirX > 0)
        data->tx = (*texture)->width - data->tx - 1;
    else if (data->side == 1 && data->rayDirY < 0)
        data->tx = (*texture)->width - data->tx - 1;
}

void    set_wall_height(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    data->lineHeight = (int)(SCREEN_HEIGHT / data->perpWallDist);
    data->drawStart = -data->lineHeight / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    data->drawEnd = data->lineHeight / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    if (data->drawStart < 0)
        data->drawStart = 0;
    if (data->drawEnd >= SCREEN_HEIGHT)
        data->drawEnd = SCREEN_HEIGHT - 1;
}

void    set_door_height(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    data->lineHeight = (int)(SCREEN_HEIGHT / data->door_perp_dist);
    data->drawStart = -data->lineHeight / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    data->drawEnd = data->lineHeight / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    if (data->drawStart < 0)
        data->drawStart = 0;
    if (data->drawEnd >= SCREEN_HEIGHT)
        data->drawEnd = SCREEN_HEIGHT - 1;
}

void    draw_doors(t_map *map, int x)
{
    int y;
    t_render *data;
    t_tex *texture;
    
    data = &map->render_data;
    texture = &map->textures[6];
    data->text_step = (double)texture->height / (double)data->lineHeight;
    data->text_position = (data->drawStart - (SCREEN_HEIGHT/2 + map->cam.pitch_offset) + data->lineHeight/2) * data->text_step;
    y = data->drawStart;
    while (y < data->drawEnd)
    {
        data->ty = (int)data->text_position;
        if (data->ty < 0)
            data->ty = 0;
        else if (data->ty >= texture->height)
            data->ty = texture->height - 1;
        data->text_position += data->text_step;
        data->color = texel_at(texture, data->door_tx, data->ty);
        data->bytes = map->mlx.bits_per_pixel / 8;
        data->offset = y * map->mlx.size_line + x * data->bytes;
        *(uint32_t *)(map->mlx.img_data + data->offset) = data->color;
        y++;
    }
    map->z_buffer[x] = 0;
}

void    draw_walls(t_map *map, t_tex *texture, int x)
{
    int y;
    t_render *data;

    data = &map->render_data;
    data->text_step = (double)texture->height / (double)data->lineHeight;
    data->text_position = (data->drawStart - (SCREEN_HEIGHT/2 + map->cam.pitch_offset) + data->lineHeight/2) * data->text_step;
    y = data->drawStart;
    while (y < data->drawEnd)
    {
        data->ty = (int)data->text_position;
        if (data->ty < 0)
            data->ty = 0;
        else if (data->ty >= texture->height)
            data->ty = texture->height - 1;
        data->text_position += data->text_step;
        data->color = texel_at(texture, data->tx, data->ty);
        data->bytes = map->mlx.bits_per_pixel / 8;
        data->offset = y * map->mlx.size_line + x * data->bytes;
        *(uint32_t *)(map->mlx.img_data + data->offset) = data->color;
        y++;
    }
    map->z_buffer[x] = data->perpWallDist;
}
