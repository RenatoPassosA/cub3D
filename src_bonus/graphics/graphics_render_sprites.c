/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render_sprites.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:32:23 by renato            #+#    #+#             */
/*   Updated: 2025/09/09 16:49:44 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"

void    set_render_list()
{
    t_map *map;
    int counter;

    map = get_map_instance();
    counter = map->num_sprites + map->num_monsters;
    map->render_list = (t_render_list *)malloc(sizeof(t_render_list) * counter);
    if (!map->render_list)
        quit_game();
}

t_render_list ret_monster(t_map *map, t_render_list ret, int *counter_monster)
{
    ret.data = &map->monsters[*counter_monster];
    ret.type = MONSTER;
    ret.transform_y = map->monsters[*counter_monster].transformY;
    ret.render_fn = render_monsters;
    (*counter_monster)++;
    return (ret);
}

t_render_list ret_sprite(t_map *map, t_render_list ret, int *counter_sprite)
{
    ret.data = &map->sprites[*counter_sprite];
    ret.type = SPRITE;
    ret.transform_y = map->sprites[*counter_sprite].transformY;
    ret.render_fn = render_decorative_sprites;
    (*counter_sprite)++;
    return (ret);
}

bool    check_draw(double y1, double y2)
{
    double eps;

    eps = 1e-6 * fmax(1 , fmax(fabs(y1), fabs(y2)));
    if (fabs(y1 - y2) < eps)
        return (true);
    return (false);
}

t_render_list resolve_draw(t_map *map, int *counter_monster, int *counter_sprite)
{
    t_render_list ret;
    float dx;
    float dy;
    float dist_monster;
    float dist_sprite;
    
    dx = map->sprites[*counter_sprite].x - map->player.posX;
    dy = map->sprites[*counter_sprite].y - map->player.posY;
    dist_sprite = dx * dx + dy * dy;

    dx = map->monsters[*counter_monster].x - map->player.posX;
    dy = map->monsters[*counter_monster].y - map->player.posY;
    dist_monster = dx * dx + dy * dy;
    
    if (dist_sprite < dist_monster)
        return(ret_monster(map, ret, counter_monster));
    else
        return (ret_sprite(map, ret, counter_sprite));
}
t_render_list filter(t_map *map, int *counter_monster, int *counter_sprite)
{
    t_render_list ret;
    
    while (1)
    {   
        if (*counter_monster < map->num_monsters && *counter_sprite < map->num_sprites)
        {
            if (check_draw(map->monsters[*counter_monster].transformY, map->sprites[*counter_sprite].transformY))
                return (resolve_draw(map, counter_monster, counter_sprite));
            else if (map->monsters[*counter_monster].transformY > map->sprites[*counter_sprite].transformY)
                return (ret_monster(map, ret, counter_monster));
            else
                return (ret_sprite(map, ret, counter_sprite));
        }
        else if (*counter_monster < map->num_monsters)
            return (ret_monster(map, ret, counter_monster));
        else if (*counter_sprite < map->num_sprites)
            return (ret_sprite(map, ret, counter_sprite));
    }
    return (ret);
}

void    set_priority_order()
{
    t_map *map;
   
    
    int loop_counter;
    int loop_limit;
    int counter_sprite;
    int counter_monster;
    
    map = get_map_instance();
    counter_monster = 0;
    counter_sprite = 0;
    set_sprites_projection();
    sort_sprites(map);
    // printf("sprite 0:-----%f\n", map->sprites[0].transformY);
    // printf("sprite 2:-----%f\n", map->sprites[2].transformY);
    // printf("monster 0:-----%f\n", map->monsters[0].transformY);
    // printf("monster 1:-----%f\n", map->monsters[1].transformY);
    set_monsters_projection();
    sort_monsters(map);
    loop_limit = map->num_monsters + map->num_sprites;
    loop_counter = 0;
    while (loop_counter < loop_limit)
    {
        map->render_list[loop_counter] = filter(map, &counter_monster, &counter_sprite);
        loop_counter++;   
    }
}

void    render_sprites()
{
    t_map *map;
    int counter;
    int loop_limit;

    map = get_map_instance();
    counter = 0;
    loop_limit = map->num_monsters + map->num_sprites;
    while (counter < loop_limit)
    {
        map->render_list[counter].render_fn(map->render_list[counter].data);    
        counter++;
    }
    
}

