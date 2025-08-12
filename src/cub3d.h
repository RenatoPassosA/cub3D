/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/12 10:41:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../utils/utils.h"
//#include "../mlx/mlx.h"

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

typedef enum e_validation_status
{
    VALIDATION_OK = 0,
	ERR_MISSING_IDENTIFIER,
	ERR_DOUBLE_IDENTIFIER,
    ERR_MISSING_TEXTURE_PATH,
	ERR_INVALID_TEXTURE_PATH,
	ERR_MISSING_COLOR,
    ERR_INVALID_RGB,
	ERR_INVALID_MAP_POSITION,
	ERR_INVALID_MAP_ELEMENT,
	ERR_DATA_AFTER_MAP,
	ERR_MISSING_MAP,
	ERR_INVALID_MAP_SIZE,
	ERR_INVALID_MAP_CONTENT,
	ERR_INVALID_EDGES,
	ERR_MULTIPLAYERS,
	ERR_NO_PLAYER,
	ERR_COPY_MAP,
	ERR_INTER_SPACE,
	ERR_MAP_OPEN,
	ERR_MALLOC_CONTENT,
	ERR_MALLOC_MAP,
	ERR_MALLOC_MAP_AND_CONTENT
}   t_validation_status;

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
t_map	*get_map_instance(void);
int		get_arr_size(char **arr);
int		get_map_height(char **map);
int		get_line_width(char *line);
void	map_validations(char **av);
int		*get_player_position(char **map);
bool	find_isolated_spaces(char **map);
int		check_argument(int ac, char **av);
bool	check_player_one_line(char *line);
bool	is_type_identifier(char *splitted);
void	remove_backslash_n(char **content);
void	free_bidimensional_array(char **arr);
void	free_tridimensional_array(char ***content);
void	free_arr_with_null(char **arr, int splitted_arr_size);
void	fd_manage(char *path, int fd, char ***content, char **map);
void	clean_all_and_message_error(char *msg, char ***content, char **map);


t_validation_status set_matrix(char ***map);
char *fill_line(char *line, int	width);
int	get_line_width(char *line);
int	get_map_content_height(char ***content);
bool	find_map(char *line);
void	remove_backslash_n2(char *line);

//-----VALIDATIONS

t_validation_status outside_flood_fill(char **map, char **flood_fill_map);
t_validation_status set_map_data(char ***content, char **map);
t_validation_status	get_content_splitted(char *path, char ****content);
t_validation_status	flood_fill(char **map);
t_validation_status	validate_edges(char **map);
t_validation_status	validate_player(char **map);
t_validation_status validate_map_size(char **map);
t_validation_status	validate_map_lines(char **map);
t_validation_status	validate_colors(char ***content);
t_validation_status	validate_textures(char ***content);
t_validation_status	validate_map_elements(char ***content);
t_validation_status	validate_map_position(char ***content);
t_validation_status validate_map_existence(char ***content);
t_validation_status	check_double_identifier(char ***content);
t_validation_status	check_missing_identifier(char ***content);
t_validation_status	get_map_matrix(char **av, char ***map, char ***content);


#endif