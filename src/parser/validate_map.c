/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 10:16:52 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_type_identifier(char *splitted)
{
	return (ft_strcmp(splitted, "NO") == 0 || 
		ft_strcmp(splitted, "SO") == 0 || 
		ft_strcmp(splitted, "WE") == 0 || 
		ft_strcmp(splitted, "EA") == 0 || 
		ft_strcmp(splitted, "F") == 0 || 
		ft_strcmp(splitted, "C") == 0);
}

void	remove_backslash_n(char **content)
{
	int	index;
	int	len;
	
	index = 0;
	while (content[index] != NULL)
	{
		if (ft_strcmp(content[index], "\n") == 0)
		{
			index++;
			continue;
		}
		else if (ft_strstr(content[index],"\n"))
		{
			len = ft_strlen(content[index]);
			content[index][len - 1] = '\0';
		}
		index++;
	}
}


void	get_content_splitted(char **av, char ****content)
{
	int		counter;
	char	*line;
	t_map	*map_data;

	counter = 0;
	map_data = get_map_instance();
	while ((line = get_next_line(map_data->fd)))
	{
		counter++;
		free(line);
	}
	*content = (char ***)malloc(sizeof(char **) * (counter + 1));
	if (!(*content))
		clean_all_and_message_error("Error on malloc.", NULL, NULL);
	(*content)[counter] = NULL;
	fd_manage(av[1], map_data->fd, *content, NULL); //preciso reabrir o fd pra subir o cursor
	counter = 0;
	while ((line = get_next_line(map_data->fd)))
	{
		(*content)[counter] = ft_split(line, ' ');
		remove_backslash_n((*content)[counter]);
		free(line);
		counter++;
	}
	close(map_data->fd);
}

bool	map_validations(char **av)
{
	char	***content;
	char	**map;
	
	get_content_splitted(av, &content);//saio daqui com o fd fechado
	check_missing_identifier(content);
	check_double_identifier(content);
	validate_textures(content);
	validate_colors(content);
	validate_map_position(content);
	validate_map_elements(content);
	validate_map(content);
	get_map_matrix(av, &map, content);
	//--A PARTIR DAQUI TENHO O MAP EM MATRIZ--
	validate_map_lines(map);
	validate_edges(map);
	validate_player(map);
	flood_fill(map);
	set_map_data(content, map);
		

	/*t_map	*map_data;
	map_data = get_map_instance();
	int i = 0;
	while (map_data->map[i])
	{
		printf("---%s-\n", map_data->map[i]);
		i++;
	}
	printf("----------%d\n", map_data->ceiling_rgb);
	printf("----------%d\n", map_data->floor_rgb);
	printf("----------%s\n", map_data->WE_texture);
	printf("----------%s\n", map_data->EA_texture);
	printf("----------%s\n", map_data->SO_texture);
	printf("----------%s\n", map_data->NO_texture);*/

	/*int i = 0;
	while (content[i])
	{
		int j = 0;
		printf("Bloco %d:\n", i);
		while (content[i][j])
		{
			printf("  [%d][%d]: %s\n", i, j, content[i][j]);
			j++;
		}
		i++;
	}*/

	free_tridimensional_array(content);

	


	// int	index3 = 0;
	// while (map[index3])
	// {
    // 	printf("content: %s-\n", map[index3]);
    // 	index3++;
	// }
	
	//flood fill do player pra ver se ele nao consegue ir pra fora da borda
	//dar um jeito de verificar o mapa forbidden

	
	

	return (true);
}
