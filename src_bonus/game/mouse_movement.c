/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:52:19 by renato            #+#    #+#             */
/*   Updated: 2025/08/28 12:09:52 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_bonus.h"

void    init_cam()
{
    t_map *map;

    map = get_map_instance();
    map->cam.pitch_offset = 0;
    map->cam.pitch_sens = 0.9;
    map->cam.yaw_sens = 0.004;
    map->cam.pitch_max = SCREEN_HEIGHT / 4;
	map->cam.deadzone = 2;
	map->cam.ignore_warp = false;
    map->cam.should_recentre = false;
    map->cam.center_x = SCREEN_WIDTH / 2;
    map->cam.center_y = SCREEN_HEIGHT / 2;
    map->cam.dx_prev_smooth = 0;
    map->cam.last_x = 0;
	map->cam.last_y = 0;
	map->cam.mouse_init = false;
    map->cam.edge_margin = 80;
	map->cam.edge_dir = 0;
	map->cam.edge_intensity = 0.0;
    map->cam.edge_gain = 1.0;    
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
    float smoothiness = 0.35;
    float smooth_dx = 0;

    map = (t_map *)param;


    if (!map->cam.mouse_init)
    {
        map->cam.last_x = x;
        map->cam.last_y = y;
        map->cam.dx_prev_smooth = 0.0f;
        map->cam.mouse_init = true;
    }


       
    dx = x - map->cam.last_x;
    dy = y - map->cam.last_y;
    
    if (abs(dx) < map->cam.deadzone)
    {
        dx = 0;
        map->cam.dx_prev_smooth = 0.0f;
    }

    if (abs(dy) < map->cam.deadzone)
        dy = 0;
    
    if ((dx != 0) && (map->cam.dx_prev_smooth != 0.0f) && ((dx > 0 && map->cam.dx_prev_smooth < 0.0f) || (dx < 0 && map->cam.dx_prev_smooth > 0.0f)))
    {
        map->cam.dx_prev_smooth = 0.0f;
    }
       
    smooth_dx = smoothiness * (float)dx + (1.0f - smoothiness) * map->cam.dx_prev_smooth;
    map->cam.dx_prev_smooth = smooth_dx;


    if (x <= map->cam.edge_margin)
    {
        map->cam.edge_dir = -1;
        map->cam.edge_intensity = (float)(map->cam.edge_margin - x) / (float)map->cam.edge_margin;
        if (map->cam.edge_intensity < 0)
            map->cam.edge_intensity = 0;
        else if (map->cam.edge_intensity > 1)
            map->cam.edge_intensity = 1;
    }
    else if (x >= SCREEN_WIDTH - map->cam.edge_margin)
    {
        map->cam.edge_dir = 1;
        map->cam.edge_intensity = (float)(x - (SCREEN_WIDTH - map->cam.edge_margin)) / (float)map->cam.edge_margin;
        if (map->cam.edge_intensity < 0)
            map->cam.edge_intensity = 0;
        else if (map->cam.edge_intensity > 1)
            map->cam.edge_intensity = 1;
    }
    else
    {
        map->cam.edge_dir = 0;
        map->cam.edge_intensity = 0.0f;
    }

    float t;
    if (x <= map->cam.edge_margin)
    {
        map->cam.edge_dir = -1;
        t = (float)(map->cam.edge_margin - x) / (float)map->cam.edge_margin;
        if (t < 0.0f)
            t = 0.0f;
        if (t > 1.0f)
            t = 1.0f;
        map->cam.edge_intensity = t;
    }
    else if (x >= SCREEN_WIDTH - map->cam.edge_margin)
    {
        map->cam.edge_dir = +1;
        t = (float)(x - (SCREEN_WIDTH - map->cam.edge_margin)) / (float)map->cam.edge_margin;
        if (t < 0.0f)
            t = 0.0f;
        if (t > 1.0f)
            t = 1.0f;
        map->cam.edge_intensity = t;
    }
    else
    {
        map->cam.edge_dir = 0;
        map->cam.edge_intensity = 0.0f;
    }

    
    yaw = smooth_dx * map->cam.yaw_sens;
    if (yaw < -0.03)
        yaw = -0.03;
    if (yaw > 0.03)
        yaw = 0.03;
    if (yaw != 0.0f)
        rotate_player(map, yaw);
    if (dy != 0)
    {
        map->cam.pitch_offset += dy * map->cam.pitch_sens;
        if (map->cam.pitch_offset < -map->cam.pitch_max)
            map->cam.pitch_offset = -map->cam.pitch_max;
        if (map->cam.pitch_offset > map->cam.pitch_max)
            map->cam.pitch_offset = map->cam.pitch_max;
    }
    
    map->cam.last_x = x;
    map->cam.last_y = y;

    return (0);
}

void	check_rotate_on_edge(t_map *map)
{
	float yaw_extra;
	
	if (map->cam.edge_dir != 0)
	{
		yaw_extra = map->cam.edge_dir * map->player.rotate_speed * map->cam.edge_gain * map->cam.edge_intensity;
		rotate_player(map, yaw_extra);
	}
}





/*yaw = rotação esquerda/direita (mouse X).
pitch = rotação cima/baixo (mouse Y).*/