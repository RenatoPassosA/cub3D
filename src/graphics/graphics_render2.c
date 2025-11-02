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

#include "graphics.h"

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
    data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2;
    data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2;
    if (data->draw_start < 0)
        data->draw_start = 0;
    if (data->draw_end >= SCREEN_HEIGHT)
        data->draw_end = SCREEN_HEIGHT - 1;
}

void    draw_ceiling(t_map *map, int x)
{
    int y;
    t_render *data;

    y = 0;
    data = &map->render_data;
    while (y < map->render_data.draw_start)
    {
        data->bytes = map->mlx.bits_per_pixel / 8;
        data->offset = y * map->mlx.size_line + x * data->bytes;
        *(uint32_t *)(map->mlx.img_data + data->offset) = map->ceiling_rgb;
        y++;
    }   
}

void    draw_walls(t_map *map, t_tex *texture, int x)
{
    int y;
    t_render *data;

    data = &map->render_data;
    data->text_step = (double)texture->height / (double)data->line_height;
    data->text_position = (data->draw_start - SCREEN_HEIGHT/2 + data->line_height/2) * data->text_step;
    y = data->draw_start;
    while (y < data->draw_end)
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
}

void    draw_floor(t_map *map, int x)
{
    int y;
    t_render *data;

    data = &map->render_data;
    y = map->render_data.draw_end + 1;
    while (y < SCREEN_HEIGHT)
    {
        data->bytes = map->mlx.bits_per_pixel / 8;
        data->offset = y * map->mlx.size_line + x * data->bytes;
        *(uint32_t *)(map->mlx.img_data + data->offset) = map->floor_rgb;
        y++;
    }
}
