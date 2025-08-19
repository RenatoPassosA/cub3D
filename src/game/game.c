/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:54:51 by renato            #+#    #+#             */
/*   Updated: 2025/08/19 13:52:48 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	quit_game(void)
{
	t_map *map;

	map = get_map_instance();
	free_bidimensional_array(map->map);
	free(map->NO_texture);
	free(map->SO_texture);
	free(map->WE_texture);
	free(map->EA_texture);
	
	mlx_destroy_image(map->mlx.mlx_ptr, map->textures[0].img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->textures[1].img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->textures[2].img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->textures[3].img);
	mlx_destroy_image(map->mlx.mlx_ptr, map->mlx.img_ptr);
	mlx_destroy_window(map->mlx.mlx_ptr, map->mlx.win_ptr);
	mlx_loop_end(map->mlx.mlx_ptr);
	mlx_destroy_display(map->mlx.mlx_ptr);
	free(map->mlx.mlx_ptr);
	exit(1);
}

int	update_frame(void)
{
	t_map *map;

	map = get_map_instance();
	map->player.old_time = map->player.time;
	map->player.time = get_current_time_ms();
	map->player.frame_time = (map->player.time - map->player.old_time) / 1000.0;
	map->player.move_speed = map->player.frame_time * 6.0;
	map->player.rotate_speed  = map->player.frame_time * 3.0;
	keyboard_inputs(map);
	render();
    return (0);
}

void    game_loop(void)
{
    t_map *map;
    
    map = get_map_instance();
    mlx_hook(map->mlx.win_ptr, 2, 1L<<0, on_key_press, map);
	mlx_hook(map->mlx.win_ptr, 3, 1L<<1, on_key_release, map); 
	mlx_hook(map->mlx.win_ptr, 17, 0, quit_game, map);
	mlx_loop_hook(map->mlx.mlx_ptr, update_frame, NULL);
	mlx_loop(map->mlx.mlx_ptr);
}
