/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:57:23 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/11 14:49:35 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	
	if (!check_argument(ac, av))
		exit(1);
	init_data(av[1]);
	map_validations(av);
	//init_mlx();
	//init_player();
	
	t_map *map;
	map = get_map_instance();

	for (int i = 0; map->map[i] != NULL; i++)
		printf("-%s-\n", map->map[i]);



	//render();

	//mlx_loop(map->mlx.mlx_ptr);
	
}