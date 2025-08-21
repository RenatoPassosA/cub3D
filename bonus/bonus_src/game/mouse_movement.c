/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:52:19 by renato            #+#    #+#             */
/*   Updated: 2025/08/21 17:12:47 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void    init_cam()
{
    t_map *map;

    map = get_map_instance();
    map->cam.pitch_offset = 0;
    map->cam.pitch_sens = 0.3;
    map->cam.yaw_sens = 0.0009;
    map->cam.pitch_max = SCREEN_HEIGHT / 4;
	map->cam.deadzone = 2;
	map->cam.ignore_warp = false;
    map->cam.should_recentre = false;
    map->cam.center_x = SCREEN_WIDTH / 2;
    map->cam.center_y = SCREEN_HEIGHT / 2;
    map->cam.dx_prev_smooth = 0;

}
void    recenter_mouse()
{
    t_map *map;

    map = get_map_instance();

    if (map->cam.should_recentre)
    {
        map->cam.ignore_warp = true;
        mlx_mouse_move(map->mlx.mlx_ptr, map->mlx.win_ptr, map->cam.center_x, map->cam.center_y);
        map->cam.should_recentre = false;
    }
}


int     mouse_movement(int x, int y, void *param)
{
    t_map *map;
    int dy = 0;
    int dx = 0;
    float yaw = 0;
    float dx_smooth = 0;
    float smoothiness = 0.35;
    float fdx;
    float fdy;
    float ratio;

    map = (t_map *)param;
    if (map->cam.ignore_warp && (x == map->cam.center_x && y == map->cam.center_y))
    {
        map->cam.ignore_warp = false;
        return (0);
    }
    
    dx = x - map->cam.center_x;
    dy = y - map->cam.center_y;
    
    if (abs(dx) < map->cam.deadzone)
    {
        dx = 0;
        map->cam.dx_prev_smooth = 0;
    }

    if (abs(dy) < map->cam.deadzone)
        dy = 0;
    
   

   

   


    fdx = fabsf(dx);
    fdy = fabsf(dy);
    ratio = 0.15f;

    
    if (fdy <= ratio * fdx)
        dy = 0;
    else if (fdx <= ratio * fdy)
    {
        map->cam.dx_prev_smooth = 0;
        dx = 0;
    }


    if (dx == 0 && dy == 0)
        return (0);

    if (dx > 18)
        dx = 18;
    if (dx < -18)
        dx = -18;
        
    dx_smooth = smoothiness * dx + (1 - smoothiness) * map->cam.dx_prev_smooth;
    map->cam.dx_prev_smooth = dx_smooth;
    yaw = dx_smooth * map->cam.yaw_sens;
    if (yaw < -0.03)
        yaw = -0.03;
    if (yaw > 0.03)
        yaw = 0.03;
    rotate_player(map, yaw);
    map->cam.pitch_offset += dy * map->cam.pitch_sens;
    if (map->cam.pitch_offset < -map->cam.pitch_max)
        map->cam.pitch_offset = -map->cam.pitch_max;
    if (map->cam.pitch_offset > map->cam.pitch_max)
        map->cam.pitch_offset = map->cam.pitch_max;
    
    map->cam.should_recentre = true;

    return (0);
}



/*yaw = rotação esquerda/direita (mouse X).
pitch = rotação cima/baixo (mouse Y).*/