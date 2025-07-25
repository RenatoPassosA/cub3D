/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/24 21:00:04 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_content_splitted(char **av, char ***map, int fd)
{
	int		counter;
	char	*line;

	counter = 0;
	while ((line = get_next_line(fd)))
	{
		counter++;
		free(line);
	}
	*map = (char ***)malloc(sizeof(char **) * (counter + 1));
	if (!(*map))
	{
		close(fd);
		exit(1);
	}
	close(fd);
	fd = open(av[1], O_RDONLY);
	counter = 0;
	while ((line = get_next_line(fd)))
	{
		(*map)[counter] = ft_split(line, ' ');		
		free(line);
		counter++;
	}	
	(*map)[counter] = NULL;
}





bool	validate_map(char **av, int fd)
{
	char	***content;
	char	**map;
	
	get_content_splitted(av, &content, fd);
	check_missing_identifier(content);
	check_double_identifier(content);
	validate_textures(content);
	validate_colors(content);
	validate_map_position(content);
	check_valid_lines(content);
	check_map(content, &map);//aqui ja verifica se nao tiver mapa
	
	
	
}
