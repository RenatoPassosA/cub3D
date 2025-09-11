/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:16:27 by renato            #+#    #+#             */
/*   Updated: 2025/09/11 13:14:06 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"
#include "../graphics/graphics_bonus.h"

void    init_gun()
{
    t_map *map;

    map = get_map_instance();
    map->gun.cooldown = 0.0;
    map->gun.fire_interval = 0.5;
    map->gun.damage = 1;
    map->gun.recoil_decay_y = 0.12;
    map->gun.recoil_kick_y = 0;
    map->gun.is_firing = false;
    map->gun.shot_pressed = false;
}

void    set_cooldown()
{
    t_map *map;
    
    map = get_map_instance();
    map->gun.cooldown -= map->player.frame_time;
    if (map->gun.cooldown <= 0)
        map->gun.cooldown = 0;
}

void    relax_recoil()
{
    t_map *map;
    double   decay;
    float   max_kick;
    
    map = get_map_instance();
    decay = exp(-map->player.frame_time / map->gun.recoil_decay_y);
    max_kick = 3 * 0.007 * SCREEN_HEIGHT;
    
    map->gun.recoil_kick_y *= decay;
    
    if ((fabsf)(map->gun.recoil_kick_y) < 0.05)
        map->gun.recoil_kick_y = 0;
        

    if (map->gun.recoil_kick_y > +max_kick)
        map->gun.recoil_kick_y = max_kick;
    if (map->gun.recoil_kick_y < -max_kick)
        map->gun.recoil_kick_y = -max_kick;        
}

void    shoot()
{
    t_map *map;
    int x_center;
    float y_center;
    double target;
    double  monster_depth;
    double best_depth;
    int counter;
    float x_pad;
    int best_monster;
    // float vertical_tolerance;
    // float min_px_tolerance;
    // float px_tolerance;
    float left_padded;
    float right_padded;
    double relative_eps;

    float kick;
    float max_kick;

    map = get_map_instance();
    x_center = SCREEN_WIDTH / 2;
    y_center = SCREEN_HEIGHT/2 - map->cam.pitch_offset + map->gun.recoil_kick_y;

 
    target = map->z_buffer[x_center];
    best_depth = target;

    x_pad = 2.0;
    best_monster = -1;
    
    // vertical_tolerance = 0.5;
    // min_px_tolerance = 10;
    
    kick = 20;
    
    counter = 0;
    while (counter < map->num_monsters)
    {
        if (map->monsters[counter].transformY <= 0 || map->monsters[counter].state == MON_DEAD)
        {
            printf("transformy < 0 ou MON_DEAAD\n");
            counter++;
            continue;
        }
        // px_tolerance = fmaxf((vertical_tolerance * map->monsters[counter].height_screen), min_px_tolerance);
        left_padded = map->monsters[counter].x_left - x_pad;
        if (left_padded < 0)
            left_padded = 0;
        if (left_padded > SCREEN_WIDTH - 1)
            left_padded = SCREEN_WIDTH - 1;
        right_padded = map->monsters[counter].x_right + x_pad;
        if (right_padded < 0)
            right_padded = 0;
        if (right_padded > SCREEN_WIDTH - 1)
            right_padded = SCREEN_WIDTH - 1;
        if (x_center < left_padded || x_center > right_padded)
        {
            printf("x_center < oui > left/right\n");
            counter++;
            continue;
        }
        if (y_center < map->monsters[counter].y_top || y_center > map->monsters[counter].y_bottom)
        {
            printf("Fora da hitbox vertical\n");
            counter++;
            continue;
        }
        monster_depth = map->monsters[counter].transformY;
        relative_eps = 1e-6 * fmax(1, fmax(fabs(monster_depth), fabs(target)));
        if (monster_depth >= target - relative_eps)
        {
            printf("monster depth > target\n");
            counter++;
            continue;
        }
        if (monster_depth + relative_eps < best_depth)
        {
            best_depth = monster_depth;
            best_monster = counter;
        }
        counter++;
    }
    printf("best: %d\n", best_monster);
    if (best_monster >= 0)
    {
        map->monsters[best_monster].hp -= map->gun.damage;
        map->monsters[best_monster].is_damaged = true;
        map->monsters[best_monster].damage_timer = 0.1f;
        printf("monstert hp:%d\n", map->monsters[best_monster].hp);
        if (map->monsters[best_monster].hp == 0)
            map->monsters[best_monster].state = MON_DEAD;
    }
    max_kick = 20 * 0.07 * SCREEN_HEIGHT;
    // max_kick = 50;
    map->gun.recoil_kick_y -= (kick);

    map->gun.recoil_kick_y = 100;
    
    
    
    
    map->gun.recoil_kick_y -= kick;
    if (map->gun.recoil_kick_y < -max_kick)
        map->gun.recoil_kick_y = -max_kick;
    if (map->gun.recoil_kick_y > max_kick)
        map->gun.recoil_kick_y = max_kick;
    
    map->gun.cooldown = map->gun.fire_interval;    
}


int on_mouse_press(int button, int x, int y, t_map *map)
{
    (void)x;
    (void)y;
    if (button == 1)
    {
        if (map->gun.cooldown <= 0)
        {
            map->gun.shot_pressed = true;
            return (0);
        }
    }
    return (0);
}
