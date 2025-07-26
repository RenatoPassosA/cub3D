/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:57:23 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/25 13:47:20 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (!check_argument(ac, av, fd))
		exit(1);
	//init_data();
	if (!validate_map(av, fd))
		exit(1);
	close(fd);
	fd = open(av[1], O_RDONLY);
	//parser(fd);
	
	

	
}