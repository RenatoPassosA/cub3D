/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:54:51 by renato            #+#    #+#             */
/*   Updated: 2025/08/13 17:30:42 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	quit_game(void)
{
	exit(1);
}

int	update_frame(void)
{
	t_map *map = get_map_instance();

	map->player.old_time = map->player.time;
	map->player.time = get_current_time_ms();
	map->player.frame_time = (map->player.time - map->player.old_time) / 1000.0;
	map->player.move_speed = map->player.frame_time * 5.0;
	map->player.rot_speed  = map->player.frame_time * 2.0;

	render();
    return (0);
}

void    game_loop(void)
{
    t_map *map;
    
    map = get_map_instance();
    mlx_key_hook(map->mlx.win_ptr, keyboard_inputs, NULL);
	mlx_hook(map->mlx.win_ptr, 17, 0, quit_game, map); // evento de fechar janela
	mlx_loop_hook(map->mlx.mlx_ptr, update_frame, NULL); // chamada contínua por frame
	mlx_loop(map->mlx.mlx_ptr); // loop principal do MLX
}