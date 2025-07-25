/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:46:08 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/24 21:01:54 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_colors(char **splitted)
{
	t_map	*map_info;
	char	**colors;
	int		size;

	map_info = get_map_instance();
	colors = ft_split(splitted[1], ',');
	size = get_arr_size(colors);
	if (size != 3)
	{
		printf("Error.\n Wrong color elements");
		free_arr_with_null(colors, get_arr_size(colors));
		free_arr_with_null(splitted, get_arr_size(splitted));
		free_map_info();
		exit(1);
	}
	else
	{
		if (ft_strcmp(splitted[0], "F") == 0)
			map_info->floor_rgb = get_rgb(ft_atoi(colors[0]), 
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		else if (ft_strcmp(splitted[0], "C") == 0)
			map_info->ceiling_rgb = get_rgb(ft_atoi(colors[0]), 
				ft_atoi(colors[1]), ft_atoi(colors[2]));
	}
}

void	set_flag(int *identifier, char *splitted)
{
	if (ft_strcmp(splitted, "NO") == 0)
		identifier[NO] = 1;
	if (ft_strcmp(splitted, "SO") == 0)
		identifier[SO] = 1;
	if (ft_strcmp(splitted, "WE") == 0)
		identifier[WE] = 1;
	if (ft_strcmp(splitted, "EA") == 0)
		identifier[EA] = 1;
	if (ft_strcmp(splitted, "F") == 0)
		identifier[F_RGB] = 1;
	if (ft_strcmp(splitted, "N") == 0)
		identifier[C_RGB] = 1;
}

void	get_identifier_content(int *identifier, char **splitted)
{
	t_map	*map_info;
	size_t	len;

	len = ft_strlen(splitted[1]);
	splitted[1][len - 1] = '\0';
	map_info = get_map_instance();
	if (ft_strcmp(splitted[0], "NO") == 0 && identifier[NO] != 1)
		map_info->NO_texture = ft_strdup(splitted[1]);
	else if (ft_strcmp(splitted[0], "SO") == 0 && identifier[SO] != 1)
		map_info->SO_texture = ft_strdup(splitted[1]);
	else if (ft_strcmp(splitted[0], "WE") == 0 && identifier[WE] != 1)
		map_info->WE_texture = ft_strdup(splitted[1]);
	else if (ft_strcmp(splitted[0], "EA") == 0 && identifier[EA] != 1)
		map_info->EA_texture = ft_strdup(splitted[1]);
	else if ((ft_strcmp(splitted[0], "F") == 0 && identifier[F_RGB] != 1) || 
		(ft_strcmp(splitted[0], "C") == 0 && identifier[C_RGB] != 1))	
		validate_colors(splitted);
	set_flag(identifier, splitted[0]);
}

bool	check_doubles(int *identifier, char *splitted)
{
	if (ft_strcmp(splitted, "N") == 0 && identifier[NO] == 1)
		return (false);
	if (ft_strcmp(splitted, "S") == 0 && identifier[SO] == 1)
		return (false);
	if (ft_strcmp(splitted, "W") == 0 && identifier[WE] == 1)
		return (false);
	if (ft_strcmp(splitted, "E") == 0 && identifier[EA] == 1)
		return (false);
	if (ft_strcmp(splitted, "F") == 0 && identifier[F_RGB] == 1)
		return (false);
	if (ft_strcmp(splitted, "C") == 0 && identifier[C_RGB] == 1)
		return (false);
	return(true);
}

static void	init_identifiers(int *identifiers)
{
	identifiers[0] = 0;
	identifiers[1] = 0;
	identifiers[2] = 0;
	identifiers[3] = 0;
	identifiers[4] = 0;
	identifiers[5] = 0;
}

/*bool	is_type_identifier(char *splitted)
{
	return (ft_strcmp(splitted, "NO") == 0 || 
		ft_strcmp(splitted, "SO") == 0 || 
		ft_strcmp(splitted, "WE") == 0 || 
		ft_strcmp(splitted, "EA") == 0 || 
		ft_strcmp(splitted, "F") == 0 || 
		ft_strcmp(splitted, "C") == 0);
}*/

void	set_map(char *line, int	*index)
{
	t_map	*map;
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	map = get_map_instance();
	map->map[*index] = ft_strdup(line);
	(*index)++;
}

void	check_content(char *line, int *identifiers, int *index)
{
	char	**splitted;
	
	splitted = ft_split(line, ' ');
	if (!check_doubles(identifiers, splitted[0]))
	{
		free_arr_with_null(splitted, get_arr_size(splitted));
		free_map_info();
		exit(1);
	}
	if (is_type_identifier(splitted[0]))
		get_identifier_content(identifiers, splitted);
	else
		set_map(line, index);	
}

void	parser(int fd)
{
	char	*line;
	int		identifiers[6];
	int		index;
	
	index = 0;
	init_identifiers(identifiers);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		check_content(line, identifiers, &index);
		free(line);
	}
}

//--------------


 //--------------
bool is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	validate_player_position(void)
{
	t_map	*map;
	int		index;
	bool	has_player;
	char	*line;

	map = get_map_instance();
	index = 0;
	has_player = false;
	while (index <= map->map_lines)
	{
		line = map->map[index];
		while (*line)
		{
			if (is_player_char(*line) && has_player == false)
				has_player = true;
			else if (is_player_char(*line) && has_player == true)
			{
				show_error_msg("Error.\nMore than one start position setted");
				free_map_info();
				exit(1);
			}
			line++;
		}
		index++;
	}
}
