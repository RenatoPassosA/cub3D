/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_decorative_sprites.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:49:41 by renato            #+#    #+#             */
/*   Updated: 2025/09/11 11:24:47 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"

int    sprites_counter()
{
    t_map *map;
    int counter;
    int x;
    int y;

    map = get_map_instance();
    counter = 0;
    x = 0;
    y = 0;

    while (y < get_map_height(map->map))
    {
        while (x < get_line_width(map->map[0]))
        {
            if (map->map[y][x] == 'P' || map->map[y][x] == 'L' || map->map[y][x] == 'B')
                counter++;
            x++;
        }
        x = 0;
        y++;
    }
    return (counter);
}

int get_sprite_id(char c)
{
    if (c == 'P')
        return (PILLAR);
    else if (c == 'B')
        return (BARREL);
    else if (c == 'L')
        return (LIGHT);
    return (-1);
}

t_sprite    create_sprite(int y, int x, char c)
{
    t_sprite sprite;

    sprite.x = x + 0.5;
    sprite.y = y + 0.5;
    sprite.z_offset = 0.0;
    sprite.dist = 0.0;
    sprite.collision = false;
    if (c == 'B' || c == 'P')
        sprite.collision = true;
    sprite.texture_id = get_sprite_id(c);
    return (sprite);
}

void    fill_sprite_data(t_map *map)
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
            if (map->map[y][x] == 'L' || map->map[y][x] == 'P' || map->map[y][x] == 'B')
            {
                map->sprites[index] = create_sprite(y, x, map->map[y][x]);
                map->map[y][x] = '0';
                index++;
            }
            x++;
        }
        x = 0;
        y++;
    }
    
}

void    init_sprites()
{
    t_map *map;

    map = get_map_instance();
    map->num_sprites = sprites_counter();
    if (map->num_sprites)
    {
        map->sprites = (t_sprite *)malloc(sizeof(t_sprite) * map->num_sprites);
        if (!map->sprites)
            quit_game();
        fill_sprite_data(map);
    }  
}

void    sort_sprites(t_map *map)
{
    int i;
    int j;
    t_sprite tmp;

    i = 0;
    while (i < map->num_sprites - 1)
    {
        j = 0;
        while (j < map->num_sprites - i - 1)
        {
            if (map->sprites[j].transformY < map->sprites[j + 1].transformY)
            {
                tmp = map->sprites[j];
                map->sprites[j] = map->sprites[j + 1];
                map->sprites[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    set_sprites_projection()
{
    t_map *map;
    int counter;

    map = get_map_instance();
    counter = 0;


    
    float dx;
    float dy;
    double det;
    double invDet;
   
        
    while (counter < map->num_sprites)
    {
        dx = map->sprites[counter].x - map->player.posX;
        dy = map->sprites[counter].y - map->player.posY;
        det = map->player.dirY * map->player.planeX - map->player.dirX * map->player.planeY;
        invDet = 1.0 / det;
        map->sprites[counter].transformX = invDet * ( map->player.dirY * dx - map->player.dirX * dy );
        map->sprites[counter].transformY = invDet * (-map->player.planeY * dx + map->player.planeX * dy );
        counter++;
    }
}

void    render_decorative_sprites(void *sprite)
{
    t_map *map;

    t_sprite *s = (t_sprite *)sprite;

    map = get_map_instance();


   
    double spriteScreenX;

    double spriteHeight;
    double spriteWidth;

    double centerY;

    double drawStartX;
    double drawEndX;
    double drawStartY;
    double drawEndY;

    
    
    
   
        
   
   
    if (s->transformY <= 0)
        return;

    spriteScreenX = (SCREEN_WIDTH / 2) * (1 + s->transformX / s->transformY);
    
    
    spriteHeight = fabs(SCREEN_HEIGHT / s->transformY);
    if (spriteHeight < 1)
        spriteHeight = 1;

    spriteWidth = fabs(SCREEN_HEIGHT / s->transformY);
    if (spriteWidth  < 1)
        spriteWidth  = 1;


    

    float move_screen;
    double left = spriteScreenX - spriteWidth / 2.0;

    move_screen = -(s->z_offset) * (SCREEN_HEIGHT / s->transformY);
    centerY = (SCREEN_HEIGHT / 2) + map->cam.pitch_offset + move_screen ;
    drawStartX = (int)left;
    if (drawStartX < 0)
        drawStartX = 0;
    drawEndX = (int)(left + spriteWidth);
    if (drawEndX > SCREEN_WIDTH - 1)
        drawEndX = SCREEN_WIDTH - 1;
    

        
    drawStartY = (int)(centerY - spriteHeight / 2.0);
    if (drawStartY < 0)
        drawStartY = 0;
    else if (drawStartY > SCREEN_HEIGHT - 1)
        drawStartY = SCREEN_HEIGHT - 1;
    drawEndY = (int)(centerY + spriteHeight / 2.0);
    if (drawEndY > SCREEN_HEIGHT - 1)
        drawEndY = SCREEN_HEIGHT - 1;
    else if (drawEndY < 0)
        drawEndY  = 0;

    if (drawStartX > drawEndX || drawStartY > drawEndY)
        return;

    int x;
    int y;
    float tex_x;
    int tex_x_int;
    float tex_y;
    int tex_y_int;

    int tex_id;
    t_tex *text;
    
    tex_id = s->texture_id;
    text = &map->textures[tex_id];
    x = drawStartX;
    while (x <= (int)drawEndX)
    {
        if (s->transformY >= map->z_buffer[x])
        {
            x++;
            continue;
        }
        tex_x = (int)(((x - left) / spriteWidth) * text->width);
        if (tex_x < 0)
            tex_x = 0;
        else if (tex_x > text->width - 1)
            tex_x = text->width - 1;
        tex_x_int = (int)tex_x;
        y = drawStartY;
        while (y <= (int)drawEndY)
        {
            tex_y = (int)(((double)(y - drawStartY) / (double)(drawEndY - drawStartY + 1)) * text->height);
            if (tex_y < 0)
                tex_y = 0;
            else if (tex_y > text->height - 1)
                tex_y = text->height - 1;
            tex_y_int = (int)tex_y;
            map->render_data.color = texel_at(text, tex_x_int, tex_y_int);
            map->render_data.bytes = map->mlx.bits_per_pixel / 8;
            map->render_data.offset = y * map->mlx.size_line + x * map->render_data.bytes;
            if (map->render_data.color != CHROMA)
                *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = map->render_data.color;
            y++;
        }
        x++;
    }

}

// void    render_decorative_sprites()
// {
//     t_map *map;
//     int counter;

//     map = get_map_instance();
//     counter = 0;

   
//     double spriteScreenX;

//     double spriteHeight;
//     double spriteWidth;

//     double centerY;

//     double drawStartX;
//     double drawEndX;
//     double drawStartY;
//     double drawEndY;

    
    

   
        
//     counter = 0;
//     while (counter < map->num_sprites)
//     {
//         if (map->sprites[counter].transformY <= 0)
//         {
//             counter++; 
//             continue;
//         }

//         spriteScreenX = (SCREEN_WIDTH / 2) * (1 + map->sprites[counter].transformX / map->sprites[counter].transformY);
       
        
//         spriteHeight = fabs(SCREEN_HEIGHT / map->sprites[counter].transformY);
//         if (spriteHeight < 1)
//             spriteHeight = 1;

//         spriteWidth = fabs(SCREEN_HEIGHT / map->sprites[counter].transformY);
//         if (spriteWidth  < 1)
//             spriteWidth  = 1;


        

//         float move_screen;
//         double left = spriteScreenX - spriteWidth / 2.0;

//         move_screen = -(map->sprites[counter].z_offset) * (SCREEN_HEIGHT / map->sprites[counter].transformY);
//         centerY = (SCREEN_HEIGHT / 2) + map->cam.pitch_offset + move_screen;
//         drawStartX = (int)left;
//         if (drawStartX < 0)
//             drawStartX = 0;
//         drawEndX = (int)(left + spriteWidth);
//         if (drawEndX > SCREEN_WIDTH - 1)
//             drawEndX = SCREEN_WIDTH - 1;
        

            
//         drawStartY = (int)(centerY - spriteHeight / 2.0);
//         if (drawStartY < 0)
//             drawStartY = 0;
//         else if (drawStartY > SCREEN_HEIGHT - 1)
//             drawEndY = SCREEN_HEIGHT - 1;
//         drawEndY = (int)(centerY + spriteHeight / 2.0);
//         if (drawEndY > SCREEN_HEIGHT - 1)
//             drawEndY = SCREEN_HEIGHT - 1;
//         else if (drawEndY < 0)
//             drawEndY  = 0;

//         if (drawStartX > drawEndX || drawStartY > drawEndY)
//         {
//             counter++;
//             continue;
//         }

//         int x;
//         int y;
//         float tex_x;
//         int tex_x_int;
//         float tex_y;
//         int tex_y_int;
    
//         int tex_id;
//         t_tex *text;
        
//         tex_id = map->sprites[counter].texture_id;
//         text = &map->textures[tex_id];
//         x = drawStartX;
//         while (x <= (int)drawEndX)
//         {
//             if (map->sprites[counter].transformY >= map->z_buffer[x])
//             {
//                 x++;
//                 continue;
//             }
//             tex_x = (int)(((x - left) / spriteWidth) * text->width);
//             if (tex_x < 0)
//                 tex_x = 0;
//             else if (tex_x > text->width - 1)
//                 tex_x = text->width - 1;
//             tex_x_int = (int)tex_x;
//             y = drawStartY;
//             while (y <= (int)drawEndY)
//             {
//                 tex_y = (int)(((double)(y - drawStartY) / (double)(drawEndY - drawStartY + 1)) * text->height);
//                 if (tex_y < 0)
//                     tex_y = 0;
//                 else if (tex_y > text->height - 1)
//                     tex_y = text->height - 1;
//                 tex_y_int = (int)tex_y;
//                 map->render_data.color = texel_at(text, tex_x_int, tex_y_int);
//                 map->render_data.bytes = map->mlx.bits_per_pixel / 8;
//                 map->render_data.offset = y * map->mlx.size_line + x * map->render_data.bytes;
//                 if (map->render_data.color != CHROMA)
//                     *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = map->render_data.color;
//                 y++;
//             }
//             x++;
//         }
//         counter++;
//     }
// }