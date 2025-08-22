/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:48:31 by renato            #+#    #+#             */
/*   Updated: 2025/08/19 14:07:51 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../cub3d.h"

bool                find_map(char *line);
t_validation_status	flood_fill(char **map);
t_validation_status set_matrix(char ***map);
int                 get_arr_size(char **arr);
int                 get_line_width(char *line);
t_validation_status	validate_edges(char **map);
int                 get_map_height(char **map);
int                 get_line_width(char *line);
void                map_validations(char **av);
t_validation_status	validate_player(char **map);
t_validation_status validate_map_size(char **map);
t_validation_status	validate_map_lines(char **map);
void                 remove_backslash_n2(char *line);
t_validation_status	validate_colors(char ***content);
int	                *get_player_position(char **map);
bool                find_isolated_spaces(char **map);
int	                check_argument(int ac, char **av);
bool                check_player_one_line(char *line);
bool                is_type_identifier(char *splitted);
void                remove_backslash_n(char **content);
t_validation_status	validate_textures(char ***content);
char                *fill_line(char *line, int	width);
bool                check_find_map(char *line, int *index);
t_validation_status	validate_map_elements(char ***content);
t_validation_status	validate_map_position(char ***content);
t_validation_status validate_map_existence(char ***content);
int                 get_map_content_height(char ***content);
t_validation_status	check_double_identifier(char ***content);
t_validation_status	check_missing_identifier(char ***content);
t_validation_status set_map_data(char ***content, char **map);
t_validation_status	get_content_splitted(char *path, char ****content);
t_validation_status outside_flood_fill(char **map, char **flood_fill_map);
t_validation_status	get_map_matrix(char **av, char ***map, char ***content);
void                fd_manage(char *path, int fd, char ***content, char **map);

#endif