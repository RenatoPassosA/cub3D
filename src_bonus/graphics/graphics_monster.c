/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_monster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:49:25 by renato            #+#    #+#             */
/*   Updated: 2025/09/08 16:13:17 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"

void    init_monster_type()
{
    t_map *map;

    map = get_map_instance();
    map->monster_type[MUMMY].type_id = MUMMY;
    map->monster_type[MUMMY].max_hp = 3;
    map->monster_type[MUMMY].r_mon = 0.30;
    map->monster_type[MUMMY].speed_chase = 0.5;
    map->monster_type[MUMMY].r_detect = 5.0;
    map->monster_type[MUMMY].r_lost = 8.0;
    map->monster_type[MUMMY].index_walk_sprite_1 = 10;
    map->monster_type[MUMMY].index_walk_sprite_2 = 11;
    map->monster_type[MUMMY].index_died_sprite = 12;
    map->monster_type[MUMMY].time_frame_walk = 0.30;

    map->monster_type[MONSTER].type_id = MONSTER;
    map->monster_type[MONSTER].max_hp = 5;
    map->monster_type[MONSTER].r_mon = 0.30;
    map->monster_type[MONSTER].speed_chase = 1.5;
    map->monster_type[MONSTER].r_detect = 6.0;
    map->monster_type[MONSTER].r_lost = 9.0;
    map->monster_type[MONSTER].index_walk_sprite_1 = 10;
    map->monster_type[MONSTER].index_walk_sprite_2 = 11;
    map->monster_type[MONSTER].index_died_sprite = 12;
    map->monster_type[MONSTER].time_frame_walk = 0.10;
    
}


int    monsters_counter()
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
            if (map->map[y][x] == 'M' || map->map[y][x] == 'N' || map->map[y][x] == 'O')
                counter++;
            x++;
        }
        x = 0;
        y++;
    }
    return (counter);
}

int get_type_id(char c)
{
    if (c == 'M')
        return (MUMMY);
    if (c == 'N')
        return (MONSTER);
    if (c == 'O')
        return (MUMMY);
    return (MUMMY);    
}

t_monster    create_monster_sprite(int y, int x, char c, int index)
{
    t_map *map;
    t_monster monster;

    map = get_map_instance();
    monster.id = index;
    monster.type_id = get_type_id(c);
    monster.x = x + 0.5;
    monster.y = y + 0.5;
    monster.x_speed = 0;
    monster.y_speed = 0;
    monster.hp = map->monster_type[monster.type_id].max_hp;
    monster.state = MON_IDLE;
    monster.animation_index = 0;
    monster.t_animation = 0.0;
    return (monster);
}



void    fill_monster_data(t_map *map)
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
            if (map->map[y][x] == 'M' || map->map[y][x] == 'N' || map->map[y][x] == 'O')
            {
                map->monsters[index] = create_monster_sprite(y, x, map->map[y][x], index);
                map->map[y][x] = '0';
                index++;
            }
            x++;
        }
        x = 0;
        y++;
    }
    
}

void    init_monsters()
{
    t_map *map;

    map = get_map_instance();
    map->num_monsters = monsters_counter();
    if (map->num_monsters)
    {
        map->monsters = (t_monster *)malloc(sizeof(t_monster) * map->num_monsters);
        if (!map->monsters)
            quit_game();
        fill_monster_data(map);
    }  
}

void    monster_animation()
{
    t_map *map;
    int counter;
    
    map = get_map_instance();
    counter = 0;

    float dist;
    float dx;
    float dy;
    float ux;
    float uy;
    float next_x;
    float next_y;
    

    while (counter < map->num_monsters)
    {
        map->monsters[counter].t_animation += map->player.frame_time;
        dx = (map->player.posX - map->monsters[counter].x);
        dy = (map->player.posY - map->monsters[counter].y);
        dist = sqrt(dx * dx + dy * dy);
        if (dist <= (map->monster_type[map->monsters[counter].type_id].r_mon + map->player.r_player))
            map->player.state = DEAD;
        

        next_x = map->monsters[counter].x + map->monsters[counter].x_speed * map->player.frame_time;
        if (next_x > get_line_width(map->map[0]))
            next_x = map->monsters[counter].x;
        
        if (map->map[(int)map->monsters[counter].y][(int)next_x] != '1' && map->map[(int)map->monsters[counter].y][(int)next_x] != 'D')
            map->monsters[counter].x = next_x;

        next_y = map->monsters[counter].y + map->monsters[counter].y_speed * map->player.frame_time;
        if (next_y > get_map_height(map->map) )
            next_y = map->monsters[counter].y;

        if (map->map[(int)next_y][(int)map->monsters[counter].x] != '1' && map->map[(int)next_y][(int)map->monsters[counter].x] != 'D')
            map->monsters[counter].y = next_y;




        if (map->monsters[counter].state == MON_DEAD)
        {
            counter++;
            continue;
        }
        
        if (map->monsters[counter].state == MON_IDLE && dist < map->monster_type[map->monsters[counter].type_id].r_detect)
            map->monsters[counter].state = MON_CHASE;
        else if (map->monsters[counter].state == MON_CHASE && dist >= map->monster_type[map->monsters[counter].type_id].r_lost)
            map->monsters[counter].state = MON_IDLE;
            
        if (map->monsters[counter].state == MON_IDLE)
        {
            map->monsters[counter].x_speed = 0;
            map->monsters[counter].y_speed = 0;
            map->monsters[counter].animation_index = 10;
        }
        
        if (map->monsters[counter].state == MON_CHASE)
        {
            ux = dx / fmax(dist, 0.0001);
            uy = dy / fmax(dist, 0.0001);
            map->monsters[counter].x_speed = map->monster_type[map->monsters[counter].type_id].speed_chase * ux;
            map->monsters[counter].y_speed = map->monster_type[map->monsters[counter].type_id].speed_chase * uy;
            
            if (map->monsters[counter].t_animation > (map->monster_type[map->monsters[counter].type_id].time_frame_walk))
            {
                if (map->monsters[counter].animation_index == 10)
                    map->monsters[counter].animation_index = 11;
                else
                    map->monsters[counter].animation_index = 10;
                map->monsters[counter].t_animation = 0;
            }
            
        }
            
           counter++; 
    }   
}

// void    monster_animation()
// {
//     t_map *map;
//     int counter;
    
//     map = get_map_instance();
//     counter = 0;

//     float dist;
//     float dx;
//     float dy;
//     float ux;
//     float uy;
//     float next_x;
//     float next_y;
    

//     while (counter < map->num_monsters)
//     {
//         map->monsters[counter].t_animation += map->player.frame_time;
//         dx = (map->player.posX - map->monsters[counter].x);
//         dy = (map->player.posY - map->monsters[counter].y);
//         dist = sqrt(dx * dx + dy * dy);
//         if (dist <= (map->monster_type[map->monsters[counter].type_id].r_mon + map->player.r_player))
//             map->player.state = DEAD;
//         if (map->monsters[counter].state == MON_DEAD)
//         {
//             counter++;
//             continue;
//         }
        
//         if (map->monsters[counter].state == MON_IDLE && dist < map->monster_type[map->monsters[counter].type_id].r_detect)
//             map->monsters[counter].state = MON_CHASE;
//         else if (map->monsters[counter].state == MON_CHASE && dist >= map->monster_type[map->monsters[counter].type_id].r_lost)
//             map->monsters[counter].state = MON_IDLE;
            
//         if (map->monsters[counter].state == MON_IDLE)
//         {
//             map->monsters[counter].x_speed = 0;
//             map->monsters[counter].y_speed = 0;
//             map->monsters[counter].animation_index = 10;
//         }
//         else if (map->monsters[counter].state == MON_CHASE)
//         {
//             ux = dx / fmax(dist, 0.0001);
//             uy = dy / fmax(dist, 0.0001);
//             map->monsters[counter].x_speed = map->monster_type[map->monsters[counter].type_id].speed_chase * ux;
//             map->monsters[counter].y_speed = map->monster_type[map->monsters[counter].type_id].speed_chase * uy;
            
//             next_x = map->monsters[counter].x + map->monsters[counter].x_speed * map->player.frame_time;
//             if (next_x > get_line_width(map->map[0]))
//                 next_x = get_line_width(map->map[0]);
//             next_y = map->monsters[counter].y + map->monsters[counter].y_speed * map->player.frame_time;
//             if (next_y > get_map_height(map->map) )
//                 next_y = get_map_height(map->map);
//             if (map->map[(int)map->monsters[counter].y][(int)next_x] != '1' && map->map[(int)map->monsters[counter].y][(int)next_x] != 'D')
//                 map->monsters[counter].x = next_x;
//             else
//             {
//                 if (map->map[(int)next_y][(int)map->monsters[counter].x] != '1' && map->map[(int)next_y][(int)map->monsters[counter].x] != 'D')
//                     map->monsters[counter].y = next_y;
//             }
//             if (map->monsters[counter].t_animation > (map->monster_type[map->monsters[counter].type_id].time_frame_walk))
//             {
//                 if (map->monsters[counter].animation_index == 10)
//                     map->monsters[counter].animation_index = 11;
//                 else
//                     map->monsters[counter].animation_index = 10;
//                 map->monsters[counter].t_animation = 0;
//             }
            
//         }
            
            
    
//            counter++; 
//     }
        


        
    
// }

void    sort_monsters(t_map *map)
{
    int i;
    int j;
    t_monster tmp;

    i = 0;
    while (i < map->num_monsters - 1)
    {
        j = 0;
        while (j < map->num_monsters - i - 1)
        {
            if (map->monsters[j].dist < map->monsters[j + 1].dist)
            {
                tmp = map->monsters[j];
                map->monsters[j] = map->monsters[j + 1];
                map->monsters[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

int get_sprite_index(t_map *map, int counter, t_mon_state state)
{
    if (state == MON_CHASE)
        return (map->monsters[counter].animation_index);
    if (state == MON_DEAD)
        return (map->monster_type[map->monsters[counter].type_id].index_died_sprite);
    return (map->monster_type[map->monsters[counter].type_id].index_walk_sprite_1);
}

void    render_monsters()
{
    
    t_map *map;
    int counter;
    
    map = get_map_instance();
    counter = 0;

    float dx;
    float dy;
    double det;
    double invDet;
    double transformX;

    // --- Projeção dos monstros ---
    while (counter < map->num_monsters)
    {
        dx = map->monsters[counter].x - map->player.posX;
        dy = map->monsters[counter].y - map->player.posY;
        map->monsters[counter].dist = sqrt(dx * dx + dy * dy);

        det = map->player.dirY * map->player.planeX - map->player.dirX * map->player.planeY;
        invDet = 1.0 / det;
        transformX = invDet * (map->player.dirY * dx - map->player.dirX * dy);
        map->monsters[counter].transformY = invDet * (-map->player.planeY * dx + map->player.planeX * dy);
    
        map->monsters[counter].x_screen = (int)((SCREEN_WIDTH / 2) * (1 + transformX / map->monsters[counter].transformY));
        map->monsters[counter].height_screen = (int)fabs((double)(SCREEN_HEIGHT / map->monsters[counter].transformY));
        counter++;
    }

    sort_monsters(map);

    int x;
    int sprite_index;
    int y;
    float tex_x;
    int tex_x_int;
    float tex_y;
    int tex_y_int;
    t_tex *text;

    float y_floor;
    float y_end;
    float y_start;
    float move_screen;
    float x_start;
    float x_end;

    float x_s;
    float x_e;
    float y_s;
    float y_e;

    
    int sprite_width;

    counter = 0;
    while (counter < map->num_monsters)
    {
        sprite_width = map->monsters[counter].height_screen;
      
        sprite_index = get_sprite_index(map, counter, map->monsters[counter].state);
        text = &map->textures[sprite_index];        

        dx = map->monsters[counter].x - map->player.posX;
        dy = map->monsters[counter].y - map->player.posY;

        move_screen = (0 + 0.5) / map->monsters[counter].transformY * SCREEN_HEIGHT;

        y_floor = SCREEN_HEIGHT / 2 + map->cam.pitch_offset + move_screen;
        y_end = y_floor;
        y_e = y_end;
        if (y_end >= SCREEN_HEIGHT - 1)
            y_end = SCREEN_HEIGHT - 1;
        else if (y_end < 0)
            y_end = 0;
        y_start = y_end - map->monsters[counter].height_screen;
        y_s = y_start;
        if (y_start < 0)
            y_start = 0;

        x_start = map->monsters[counter].x_screen - sprite_width / 2;
        x_s = x_start;
        if (x_start < 0)
            x_start = 0;
        x_end = map->monsters[counter].x_screen + sprite_width / 2;
        x_e = x_end;
        if (x_end > SCREEN_WIDTH - 1)
            x_end = SCREEN_WIDTH - 1;

        if (x_end <= x_start || y_end <= y_start)
        {
            counter++;
            continue;
        }
        x = x_start;
        while (x <= (int)x_end)
        {
            if (x >= 0 && x < SCREEN_WIDTH &&
                map->monsters[counter].transformY > 0.0 &&
                map->monsters[counter].transformY < map->z_buffer[x])
            {
                tex_x = (x - x_s) * text->width / (float)(x_e - x_s);
                if (tex_x < 0)
                    tex_x = 0;
                else if (tex_x > text->width - 1)
                    tex_x = text->width - 1;
                tex_x_int = (int)tex_x;

                y = (int)y_start;
                while (y <= (int)y_end)
                {
                    tex_y = (y - y_s) * text->height / (y_e - y_s);
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
            }
            x++;
        }
      

        counter++;
    }
}

