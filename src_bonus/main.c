/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:57:23 by rpassos-          #+#    #+#             */
/*   Updated: 2025/09/10 15:06:31 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "./parser/parser_bonus.h"
#include "./game/game_bonus.h"
#include "./graphics/graphics_bonus.h"

int	check_argument(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		printf("Error.\nCheck the arguments");
		return (0);
	}
	len = ft_strlen(av[1]);
	if (ft_strnstr(&av[1][len - 4], ".cub", 4) == NULL)
	{
		printf("Error.\nInvalid map file\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (!check_argument(ac, av))
		exit(1);
	init_data(av[1]);
	map_validations(av);
	init_mlx();
	init_player();
	init_gun();
	init_monster_type();
	init_monsters();
	init_textures();
	init_sprites();
	init_cam();
	init_door();
	set_render_list();
	game_loop();
	return (0);
}

