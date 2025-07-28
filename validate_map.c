/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/28 19:13:58 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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


void	get_content_splitted(char **av, char ****content, int fd)
{
	int		counter;
	char	*line;

	counter = 0;
	
	while ((line = get_next_line(fd)))
	{
		counter++;
		free(line);
	}
	*content = (char ***)malloc(sizeof(char **) * (counter + 1));
	if (!(*content))
	{
		close(fd);
		exit(1);
	}
	(*content)[counter] = NULL;
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	counter = 0;
	while ((line = get_next_line(fd)))
	{
		(*content)[counter] = ft_split(line, ' ');
		remove_backslash_n((*content)[counter]);
		free(line);
		counter++;
	}
	close(fd);
}

bool	map_validations(char **av, int fd)
{
	char	***content;
	char	**map;
	
	get_content_splitted(av, &content, fd);
	check_missing_identifier(content, fd);
	check_double_identifier(content, fd);
	validate_textures(content, fd);
	validate_colors(content, fd);
	validate_map_position(content, fd);
	validate_map_elements(content, fd);
	validate_map(content, fd); //OK - TESTAR
	get_map_matrix(av, &map, content);
	free_tridimensional_array(content);
	close(fd);
	// A PARTIR DAQUI TENHO O MAP EM MATRIZ
	
	validate_map_lines(fd, map); //testar
	validate_edges(map, fd);
	validate_player(map, fd);

	
	/*int	index3 = 0;
	while (map[index3])
	{
    	printf("content: %s-\n", map[index3]);
    	index3++;
	}	*/
	


	
	//check_holes_on_floor(av, fd, map);
	
	
	


	//falta validar se dentro do mapa há espaços entre paredes. para isso eu nao posso splitar.

	return (true);
}
