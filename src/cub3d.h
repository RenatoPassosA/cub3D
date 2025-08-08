/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/08 10:16:07 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../utils/utils.h"
#include "../mlx/mlx.h"

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

typedef struct mlx_data
{
	void				*mlx_ptr;
	void				*win_ptr;	
	void				*img_ptr;
	void				*img_data;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
} t_mlx;

typedef struct player_infos
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_player;

typedef struct render_data
{
	double	cameraX;
    double	rayDirX;
    double	rayDirY;
    int		mapX;
    int		mapY;
    double	deltaDistX;
    double	deltaDistY;
    double	stepX;
    double	stepY;
    double	sideDistX;
    double	sideDistY;
    bool	hit;
    int		side;
    double	perpWallDist;
    int		lineHeight;
    int		drawStart;
    int		drawEnd;
	int		color;
} t_render;

typedef struct map_infos
{
	char		*NO_texture;
	char		*SO_texture;
	char		*WE_texture;
	char		*EA_texture;
	int			floor_rgb;
	int			ceiling_rgb;
	int			map_lines;
	int			fd;
	char		**map;
	t_player	player;
	t_render	render_data;
	t_mlx		mlx;
} t_map;

#define	NO 0
#define	SO 1
#define	WE 2
#define	EA 3
#define	F_RGB 4
#define	C_RGB 5

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


//----------------

void    render();
void    init_mlx();
void    init_player();
void	free_map_info(void);
void	init_data(char *path);
void    flood_fill(char **map);
t_map	*get_map_instance(void);
int		get_arr_size(char **arr);
int		get_map_height(char **map);
int		get_line_width(char *line);
bool	check_map_size(char **map);
bool	map_validations(char **av);
void	validate_edges(char **map);
void	validate_player(char **map);
void	validate_map(char ***content);
void	validate_map_lines(char **map);
int		*get_player_position(char **map);
void	validate_colors(char ***content);
bool	find_isolated_spaces(char **map);
int		check_argument(int ac, char **av);
bool	check_player_one_line(char *line);
bool	is_type_identifier(char *splitted);
void	remove_backslash_n(char **content);
void	validate_textures(char ***content);
void	free_bidimensional_array(char **arr);
void	validate_map_elements(char ***content);
void	validate_map_position(char ***content);
void	check_double_identifier(char ***content);
void    set_map_data(char ***content, char **map);
void	check_missing_identifier(char ***content);
void	free_tridimensional_array(char ***content);
void    outside_flood_fill(char **map, char **flood_fill_map);
void	free_arr_with_null(char **arr, int splitted_arr_size);
void	get_map_matrix(char **av, char ***map, char ***content);
void	fd_manage(char *path, int fd, char ***content, char **map);
void	clean_all_and_message_error(char *msg, char ***content, char **map);



#endif