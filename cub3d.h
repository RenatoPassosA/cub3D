/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 16:17:54 by rpassos-         ###   ########.fr       */
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

void	parser(int fd);
t_map	*init_data(void);
void	free_map_info(void);
bool	validate_map(int fd);
void	show_error_msg(char *msg);
t_map	*get_map_instance(void);
int		get_arr_size(char **arr);
int		get_rgb(int r, int g, int b);
bool	is_valid_map_char(char *line);
bool	check_valid_content(char *line);
bool	is_type_identifier(char *splitted);
int		check_argument(int ac, char **av, int fd);
bool	clean_map_error(int fd, char *line, char **splitted);
void	free_arr_with_null(char **arr, int splitted_arr_size);


#endif