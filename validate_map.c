/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/25 18:07:37 by rpassos-         ###   ########.fr       */
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

bool	validate_map(char **av, int fd)
{
	char	***content;
	char	**map;
	
	get_content_splitted(av, &content, fd); //aqui joga o cursor lá pra baixo
	check_missing_identifier(content);
	check_double_identifier(content);
	validate_textures(content);
	validate_colors(content);
	validate_map_position(content);
	check_valid_lines(content);
	check_map(content, &map);//aqui ja verifica se nao tiver mapa
	//se n usar mais o content - dar free
	free_tridimensional_array(content); //----verificar se isso fica
	validate_edges(map);
	validate_player(map);
	
	
	


	//falta validar se dentro do mapa há espaços entre paredes. para isso eu nao posso splitar.

	return (true);
}
