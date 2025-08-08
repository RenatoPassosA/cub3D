/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:57:23 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 11:56:17 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	
	if (!check_argument(ac, av))
		exit(1);
	init_data(av[1]);
	map_validations(av);
	/*init_mlx();
	init_player();
	
	t_map *map;
	map = get_map_instance();

	printf("dirX = %.2f, dirY = %.2f | planeX = %.2f, planeY = %.2f | POS x = %.2f, POS Y = %.2f\n",
    map->player.dirX, map->player.dirY,
    map->player.planeX, map->player.planeY,
	map->player.posX, map->player.posY);



	
	




	render();

	mlx_loop(map->mlx.mlx_ptr);*/
	
}