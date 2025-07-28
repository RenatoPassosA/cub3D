/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/28 19:28:50 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "./utils/utils.h"

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct map_infos
{
	char	*NO_texture;
	char	*SO_texture;
	char	*WE_texture;
	char	*EA_texture;
	int		floor_rgb;
	int		ceiling_rgb;
	int		map_lines;
	char	**map;
} t_map;

#define	NO 0
#define	SO 1
#define	WE 2
#define	EA 3
#define	F_RGB 4
#define	C_RGB 5

//----------------

int		get_arr_size(char **arr);
bool	check_map_size(char **map);
bool	map_validations(char **av, int fd);
bool	is_type_identifier(char *splitted);
void	remove_backslash_n(char **content);
void	validate_edges(char **map, int fd);
void	validate_player(char **map, int fd);
void	free_bidimensional_array(char **arr);
void	validate_map_lines(int fd, char **map);
void	validate_colors(char ***content, int fd);
int		check_argument(int ac, char **av, int fd);
void	validate_textures(char ***content, int fd);
void	free_tridimensional_array(char ***content);
void	get_map_matrix(char **av, char ***map, char ***content);
void	validate_map_elements(char ***content, int fd);
void	validate_map_position(char ***content, int fd);
void	validate_map(char ***content, int fd);
void	check_double_identifier(char ***content, int fd);
void	check_missing_identifier(char ***content, int fd);
void	free_arr_with_null(char **arr, int splitted_arr_size);
void	clean_all_and_message_error(char *msg, char ***content, char **map, int fd);



#endif