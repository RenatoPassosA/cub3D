/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/25 20:35:15 by rpassos-         ###   ########.fr       */
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

/*void	parser(int fd);
t_map	*init_data(void);
void	free_map_info(void);
//bool	validate_map(int fd);
//void	validate_edges(void);
void	show_error_msg(char *msg);
t_map	*get_map_instance(void);
int		get_arr_size(char **arr);
int		get_rgb(int r, int g, int b);
bool	is_valid_map_char(char *line);
void	validate_player_position(void);
bool	check_valid_content(char *line);
bool	is_type_identifier(char *splitted);
int		check_argument(int ac, char **av, int fd);
bool	clean_map_error(int fd, char *line, char **splitted);
*/

//----------------

int		get_arr_size(char **arr);
void	show_error_msg(char *msg);
void	validate_edges(char **map);
void	validate_player(char **map);
bool	validate_map(char **av, int fd);
void	validate_colors(char ***content);
void	validate_textures(char ***content);
bool	is_type_identifier(char *splitted);
void	check_valid_lines(char ***content);
void	free_bidimensional_array(char **arr);
void	validate_map_position(char ***content);
void	check_map(char ***content, char ***map);
void	check_double_identifier(char ***content);
void	check_missing_identifier(char ***content);
int		check_argument(int ac, char **av, int fd);
void	free_tridimensional_array(char ***content);
void	free_arr_with_null(char **arr, int splitted_arr_size);
void	clean_all_and_message_error(char *msg, char ***content, char **map);



#endif