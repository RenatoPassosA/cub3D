/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:27:27 by renato            #+#    #+#             */
/*   Updated: 2025/11/02 18:04:04 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"

void    init_minimap_data()
{
    t_map   *map;

    map = get_map_instance();
    map->minimap.margin = 16;
    map->minimap.pixels_per_cell = 12;
    map->minimap.width = 12 * map->minimap.pixels_per_cell;
    map->minimap.height = 12 * map->minimap.pixels_per_cell;
    map->minimap.background_color = 0x88000000;
    map->minimap.wall_color = 0xFFFFFFFF;
    map->minimap.floor_color = 0xFF777777;
    map->minimap.player_color = 0xFFFF0000;
    map->minimap.void_color = 0xFF222222;
    map->minimap.orientation_color = 0xFFFFFF00;
    map->minimap.door_color = 0x88000000;
    map->minimap.enabled = true;
}
void    render_minimap()
{
    t_map *map;
    int originX;
    int originY;
    int x;
    int y;
    int destX;
    int destY;
    
    x = 0;
    y = 0;
    map = get_map_instance();
    originX = SCREEN_WIDTH - map->minimap.margin - map->minimap.width;
    originY = SCREEN_HEIGHT - map->minimap.margin - map->minimap.height;
    map->render_data.bytes = map->mlx.bits_per_pixel / 8;
    
    while (y < map->minimap.height)
    {
        while (x < map->minimap.width)
        {
            destX = originX + x;
            destY = originY + y;
            if (destX < 0 || destX >= SCREEN_WIDTH || destY < 0 || destY >= SCREEN_HEIGHT)
            {
                x++;
                continue;
            }
            map->render_data.offset = destY * map->mlx.size_line + destX * map->render_data.bytes;
            *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = map->minimap.background_color;
            x++;
        }
        x = 0;
        y++;
    }

    int visible_cells;
    int start_col;
    int start_row;
    int row;
    int col;

    int map_row;
    int map_col;

    int x_local = 0;
    int y_local = 0;

    int px = 0;
    int py = 0;

    int cell_color;

   
    row = 0;
    col = 0;

    visible_cells = 12;
    start_col = floor(map->player.pos_x) - visible_cells/2;
    start_row = floor(map->player.pos_y) - visible_cells/2;

    while (row < visible_cells)
    {
        while (col < visible_cells)
        {
            map_col = start_col + col;
            map_row = start_row + row;
            x_local = col * map->minimap.pixels_per_cell;
            y_local = row * map->minimap.pixels_per_cell;
            destX = originX + x_local;
            destY = originY + y_local;
            if (map_row < 0 || map_row >= get_map_height(map->map))
                cell_color = map->minimap.void_color;
            else if (map_col < 0 || map_col >= get_line_width(map->map[map_row]))
                cell_color = map->minimap.void_color;
            else if (map->map[map_row][map_col] == '0')
                cell_color = map->minimap.floor_color;
            else if (map->map[map_row][map_col] == '1')
                cell_color = map->minimap.wall_color;
            else if (map->map[map_row][map_col] == ' ')
                cell_color = map->minimap.void_color;
            else if (map->map[map_row][map_col] == 'D')
                cell_color = map->minimap.door_color;
            while (px < map->minimap.pixels_per_cell)
            {
                while (py < map->minimap.pixels_per_cell)
                {
                    x = destX + px;
                    y = destY + py;
                    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
                    {
                        py++;
                        continue;
                    }
                    map->render_data.offset = y * map->mlx.size_line + x * (map->mlx.bits_per_pixel/8);
                    *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = cell_color;
                    py++;  
                }
                py = 0;
                px++;
            }
            px = 0;
            col++;
        }
        col = 0;
        row++;
    }


    //////DRAW PLAYER

    

    float frac_x = map->player.pos_x - floor(map->player.pos_x);
    float frac_y = map->player.pos_y - floor(map->player.pos_y);

    
    int center_player_x = originX + (visible_cells/2) * map->minimap.pixels_per_cell + (int)(frac_x * map->minimap.pixels_per_cell);
    int center_player_y = originY + (visible_cells/2) * map->minimap.pixels_per_cell + (int)(frac_y * map->minimap.pixels_per_cell);
    
    px = center_player_x;
    py = center_player_y;
    
    cell_color = 0xFFFF0000;


    int minX = originX;
    int minY = originY;
    int maxX = originX + visible_cells * map->minimap.pixels_per_cell - 1;
    int maxY = originY + visible_cells * map->minimap.pixels_per_cell - 1;


    
    int dx = -2; //deslocamentos
    int dy = -2;
    
    int cx;
    int cy;
    
    while (dx <= 2)
    {
        while (dy <= 2)
        {
            cx = px + dx;
            cy = py + dy;
            if (cx < minX || cx > maxX || cy < minY || cy > maxY)
            {
                dy++;
                continue;
            }
            if (cx < 0 || cx >= SCREEN_WIDTH || cy < 0 || cy >= SCREEN_HEIGHT)
            {
                dy++;
                continue;
            }
            map->render_data.offset = cy * map->mlx.size_line + cx * (map->mlx.bits_per_pixel/8);
            *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = cell_color;
            dy++;
        }
        dy = -1;
        dx++;
    }


    //DRAW ORIENTATION
    
    int len = map->minimap.pixels_per_cell;
    int steps = ceil(len);
    int i = 0;
    int x0;
    int y0;
    float toX = px + map->player.dirX * len;
    float toY = py + map->player.dirY * len;

    cell_color = 0xFFFFFF00;
    while (i < steps)
    {
        toX = px + map->player.dirX * ((float)i * len / (float)steps);
        toY = py + map->player.dirY * ((float)i * len / (float)steps);
        x0 = (int)round(toX);
        y0 = (int)round(toY);
        if (x0 < minX || x0 > maxX || y0 < minY || y0 > maxY)
            break;
        if (x0 < 0 || x0 >= SCREEN_WIDTH || y0 < 0 || y0 >= SCREEN_HEIGHT)
            break;
        map->render_data.offset = y0 * map->mlx.size_line + x0 * (map->mlx.bits_per_pixel/8);
        *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = cell_color;
        i++;
    }
    
    
    
}
