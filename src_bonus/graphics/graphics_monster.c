/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_monster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:49:25 by renato            #+#    #+#             */
/*   Updated: 2025/11/02 18:04:04 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"


void    check_damaged_monster()
{
    t_map *map;
    int     counter;

    map = get_map_instance();
    counter = 0;

    while (counter < map->num_monsters)
    {
        if (map->monsters[counter].is_damaged)
        {
            map->monsters[counter].damage_timer -= map->player.frame_time;
                if (map->monsters[counter].damage_timer <= 0)
                    map->monsters[counter].is_damaged = false;
        }
        counter++;
    }
}

uint32_t tint_red(uint32_t color, float strength)
{
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = (uint8_t)fminf(255, r + (255 - r) * strength); // puxa pro vermelho
    g = (uint8_t)(g * (1.0f - strength));              // diminui verde
    b = (uint8_t)(b * (1.0f - strength));              // diminui azul

    return (r << 16) | (g << 8) | b;
}

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
    map->monster_type[MUMMY].type = GROUND;
    map->monster_type[MUMMY].v_move_world = 0.75;
    

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
    map->monster_type[MONSTER].type = FLYING;
    map->monster_type[MONSTER].v_move_world = 2.5;
    
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
    monster.animation_index = 10;
    monster.t_animation = 0.0;
    monster.x_screen = 0;
	monster.height_screen = 0;
	monster.dist = 0;
	monster.transformY = 0;
	monster.x_left = 0;
	monster.x_right = 0;
	monster.y_top = 0;
	monster.y_bottom = 0;
	monster.y_center_monster = 0;
    monster.is_damaged = false;
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

bool    check_door_opened(int y, int x)
{
    t_map *map;
    int     counter;

    map = get_map_instance();
    counter = 0;

    while (counter < map->num_doors)
    {
        if (map->doors[counter].y == y && map->doors[counter].x == x)
        {
            if (map->doors[counter].open_amount > 0.90)
                return (true);
        }
        counter++;
    }
    return (false);
}

bool    check_sprite_collision(int y, int x)
{
    t_map *map;
    int     counter;

    map = get_map_instance();
    counter = 0;

    while (counter < map->num_sprites)
    {
        if ((int)map->sprites[counter].y == y && (int)map->sprites[counter].x == x)
        {
            if (map->sprites[counter].collision)
                return (true);
        }
        counter++;
    }
    return (false);
    
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
        dx = (map->player.pos_x - map->monsters[counter].x);
        dy = (map->player.pos_y - map->monsters[counter].y);
        dist = sqrt(dx * dx + dy * dy);
        if (map->monsters[counter].state != MON_DEAD && (dist <= (map->monster_type[map->monsters[counter].type_id].r_mon + map->player.r_player)))//////////////
            map->player.state = DEAD;
        

        next_x = map->monsters[counter].x + map->monsters[counter].x_speed * map->player.frame_time;
        if (next_x > get_line_width(map->map[0]))
            next_x = map->monsters[counter].x;
        
        if (map->map[(int)map->monsters[counter].y][(int)next_x] == 'D' && check_door_opened((int)map->monsters[counter].y, (int)next_x))
            map->monsters[counter].x = next_x;
        else if (check_sprite_collision((int)map->monsters[counter].y, next_x))
            ;
        else if (map->map[(int)map->monsters[counter].y][(int)next_x] == '0')
            map->monsters[counter].x = next_x;

        next_y = map->monsters[counter].y + map->monsters[counter].y_speed * map->player.frame_time;
        if (next_y > get_map_height(map->map) )
            next_y = map->monsters[counter].y;

    
        if (map->map[(int)next_y][(int)map->monsters[counter].x] == 'D' && check_door_opened((int)next_y, (int)map->monsters[counter].x))
            map->monsters[counter].y = next_y;
        else if (check_sprite_collision((int)next_y, (int)map->monsters[counter].x))
            ;
        else if (map->map[(int)next_y][(int)map->monsters[counter].x] == '0')
            map->monsters[counter].y = next_y;




        if (map->monsters[counter].state == MON_DEAD)
        {
            map->monsters[counter].x_speed = 0;
            map->monsters[counter].y_speed = 0;
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
            if (map->monsters[j].transformY < map->monsters[j + 1].transformY)
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

int get_sprite_index(t_map *map, t_monster *monster, t_mon_state state)
{
    if (state == MON_CHASE)
        return (monster->animation_index);
    if (state == MON_DEAD)
        return (map->monster_type[monster->type_id].index_died_sprite);
    return (map->monster_type[monster->type_id].index_walk_sprite_1);
    
}

void    set_monsters_projection()
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
    float move_screen;

    

    // --- Projeção dos monstros ---
    while (counter < map->num_monsters)
    {
        move_screen = 0;
        dx = map->monsters[counter].x - map->player.pos_x;
        dy = map->monsters[counter].y - map->player.pos_y;
        map->monsters[counter].dist = sqrt(dx * dx + dy * dy);

        det = map->player.dirY * map->player.planeX - map->player.dirX * map->player.planeY;
        invDet = 1.0 / det;
        transformX = invDet * (map->player.dirY * dx - map->player.dirX * dy);
        map->monsters[counter].transformY = invDet * (-map->player.planeY * dx + map->player.planeX * dy);
        if (map->monster_type[map->monsters[counter].id].type == GROUND)
            move_screen = - map->monster_type[map->monsters[counter].id].v_move_world / map->monsters[counter].transformY * SCREEN_HEIGHT;
        else if (map->monster_type[map->monsters[counter].id].type == FLYING)
            move_screen = - map->monster_type[map->monsters[counter].id].v_move_world / map->monsters[counter].transformY * SCREEN_HEIGHT;
    
        map->monsters[counter].x_screen = (int)((SCREEN_WIDTH / 2) * (1 + transformX / map->monsters[counter].transformY));
        map->monsters[counter].height_screen = (int)fabs((double)(SCREEN_HEIGHT / map->monsters[counter].transformY));
        map->monsters[counter].y_center_monster = SCREEN_HEIGHT/2 + map->cam.pitch_offset + move_screen;
    
        ////FAZER CLAMP:
        map->monsters[counter].x_left = map->monsters[counter].x_screen - map->monsters[counter].height_screen/2;
        map->monsters[counter].x_right = map->monsters[counter].x_screen + map->monsters[counter].height_screen / 2;
        map->monsters[counter].y_top = map->monsters[counter].y_center_monster - map->monsters[counter].height_screen / 2;
        map->monsters[counter]. y_bottom = map->monsters[counter].y_center_monster + map->monsters[counter].height_screen / 2;

        
        counter++;
    }
}

void    render_monsters(void *monster)
{
    
    t_map *map;

    t_monster *m = (t_monster *)monster;
    map = get_map_instance();


    

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

    
    sprite_width = m->height_screen;
    
    sprite_index = get_sprite_index(map, m, m->state);
    text = &map->textures[sprite_index];        

    move_screen = (0 + 0.5) / m->transformY * SCREEN_HEIGHT;

    y_floor = SCREEN_HEIGHT / 2 + map->cam.pitch_offset  + move_screen ;
    y_end = y_floor;
    y_e = y_end;
    if (y_end >= SCREEN_HEIGHT - 1)
        y_end = SCREEN_HEIGHT - 1;
    else if (y_end < 0)
        y_end = 0;
    y_start = y_end - m->height_screen;
    y_s = y_start;
    if (y_start < 0)
        y_start = 0;

    x_start = m->x_screen - sprite_width / 2;
    x_s = x_start;
    if (x_start < 0)
        x_start = 0;
    x_end = m->x_screen + sprite_width / 2;
    x_e = x_end;
    if (x_end > SCREEN_WIDTH - 1)
        x_end = SCREEN_WIDTH - 1;

    if (x_end <= x_start || y_end <= y_start)
        return;
    x = x_start;
    while (x <= (int)x_end)
    {
        if (x >= 0 && x < SCREEN_WIDTH &&
            m->transformY > 0.0 &&
            m->transformY < map->z_buffer[x])
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
                if (map->render_data.color == CHROMA)
                {
                    y++;
                    continue;
                }
                if (m->is_damaged)
                    map->render_data.color = tint_red(map->render_data.color, 0.6f);
                if (map->render_data.color != CHROMA)
                    *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = map->render_data.color;
                y++;
            }
        }
        x++;
    }
}
