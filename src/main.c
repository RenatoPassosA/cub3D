/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:57:23 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/12 10:05:56 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	quit(void)
{
	exit(1);
}

int	main(int ac, char **av)
{
	t_map *map;
	map = get_map_instance();
	
	if (!check_argument(ac, av))
		exit(1);
	init_data(av[1]);
	map_validations(av);
	init_mlx();
	init_player();
	render();
	mlx_hook(map->mlx.win_ptr, 17, 0, quit, NULL);
	mlx_loop(map->mlx.mlx_ptr);
	
	
	// for (int i = 0; map->map[i] != NULL; i++)
	// 	printf("-%s-\n", map->map[i]);




	
}