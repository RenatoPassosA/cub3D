/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:49 by renato            #+#    #+#             */
/*   Updated: 2025/11/02 18:16:26 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"

void    set_texture_and_coordinates(t_map *map, t_tex **texture)
{
    int texture_index;
    t_render *data;

    data = &map->render_data;
    if (data->side == 0 && data->ray_dir_x > 0)
        texture_index = WE;
    else if (data->side == 0 && data->ray_dir_x < 0)
        texture_index = EA;
    else if (data->side == 1 && data->ray_dir_y > 0)
        texture_index = NO;
    else if (data->side == 1 && data->ray_dir_y < 0)
        texture_index = SO;
    *texture = &map->textures[texture_index];
    if (data->side == 0)
        data->wall_x = map->player.pos_y + data->perp_wall_dist * data->ray_dir_y;
    else
        data->wall_x = map->player.pos_x + data->perp_wall_dist * data->ray_dir_x;

    data->wall_x = data->wall_x - floor(data->wall_x);    
    data->tx = (int)(data->wall_x * (*texture)->width);

    if (data->side == 0 && data->ray_dir_x > 0)
        data->tx = (*texture)->width - data->tx - 1;
    else if (data->side == 1 && data->ray_dir_y < 0)
        data->tx = (*texture)->width - data->tx - 1;
}

void    set_wall_height(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
    data->draw_start = -data->line_height / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    data->draw_end = data->line_height / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    if (data->draw_start < 0)
        data->draw_start = 0;
    if (data->draw_end >= SCREEN_HEIGHT)
        data->draw_end = SCREEN_HEIGHT - 1;
}

void    set_door_height(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    data->line_height = (int)(SCREEN_HEIGHT / data->door_perp_dist);
    data->draw_start = -data->line_height / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    data->draw_end = data->line_height / 2 + (SCREEN_HEIGHT / 2 + map->cam.pitch_offset);
    if (data->draw_start < 0)
        data->draw_start = 0;
    if (data->draw_end >= SCREEN_HEIGHT)
        data->draw_end = SCREEN_HEIGHT - 1;
}

void    trippy_effect(t_map *map, int y, int *ty, t_tex *texture)
{
    
    float offset;
    float frequency;
    float wave_size;
    float wave_offset;

    frequency = 2.0;
    
    wave_size = 0.1;
    wave_offset = 5;
    offset = sin(map->player.trippy_phase * frequency + y * wave_size) * wave_offset;
    *ty += offset;
    if (*ty < 0)
        *ty = 0;
    else if (*ty >= texture->height)
        *ty = texture->height - 1;
}

void    draw_doors(t_map *map, int x)
{
    int y;
    t_render *data;
    t_tex *texture;
    
    data = &map->render_data;
    texture = &map->textures[6];
    data->text_step = (double)texture->height / (double)data->line_height;
    data->text_position = (data->draw_start - (SCREEN_HEIGHT/2 + map->cam.pitch_offset) + data->line_height/2) * data->text_step;
    y = data->draw_start;
    while (y < data->draw_end)
    {
        data->ty = (int)data->text_position;
        if (data->ty < 0)
            data->ty = 0;
        else if (data->ty >= texture->height)
            data->ty = texture->height - 1;
        data->text_position += data->text_step;
        if (map->player.is_high)
            trippy_effect(map, y, &data->ty, texture);
        data->color = texel_at(texture, data->door_tx, data->ty);
        data->bytes = map->mlx.bits_per_pixel / 8;
        data->offset = y * map->mlx.size_line + x * data->bytes;
        *(uint32_t *)(map->mlx.img_data + data->offset) = data->color;
        y++;
    }
    map->z_buffer[x] = data->door_perp_dist;
}



void    draw_walls(t_map *map, t_tex *texture, int x)
{
    int y;
    t_render *data;
    
    if (map->player.is_high)
        texture = &map->textures[map->frame_index];
    data = &map->render_data;
    data->text_step = (double)texture->height / (double)data->line_height;
    data->text_position = (data->draw_start - (SCREEN_HEIGHT/2 + map->cam.pitch_offset) + data->line_height/2) * data->text_step;
    y = data->draw_start;
    while (y < data->draw_end)
    {
        data->ty = (int)data->text_position;
        if (data->ty < 0)
            data->ty = 0;
        else if (data->ty >= texture->height)
            data->ty = texture->height - 1;
        data->text_position += data->text_step;
        if (map->player.is_high)
            trippy_effect(map, y, &data->ty, texture);
        data->color = texel_at(texture, data->tx, (int)data->ty);
        data->bytes = map->mlx.bits_per_pixel / 8;
        data->offset = y * map->mlx.size_line + x * data->bytes;
        *(uint32_t *)(map->mlx.img_data + data->offset) = data->color;
        y++;
    }
    map->z_buffer[x] = data->perp_wall_dist;
}
