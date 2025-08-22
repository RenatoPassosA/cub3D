/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/22 12:54:55 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../../utils/utils.h"

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdint.h>

typedef struct s_camera {
	float pitch_offset;
    float pitch_sens;
    float yaw_sens;
    int pitch_max;
	int deadzone;
	bool ignore_warp;
	bool should_recentre;
	int center_x;
	int	center_y;
	float dx_prev_smooth;

	int last_x;
	int last_y;
	bool mouse_init;


	int edge_margin;
	int	edge_dir;
	float edge_intensity;
	float edge_gain;
} t_cam;

typedef struct s_minimap {
    int margin;
	int height;
	int width;
	int	pixels_per_cell;
	int wall_color;
	int floor_color;
	int player_color;
	int background_color;
	int	void_color;
	int	orientation_color;
	bool enabled;
} t_mini;

typedef struct s_tex {
    void   *img;
    char   *addr;
    int     width; 
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
} t_tex;

typedef struct s_input {
    int w;
	int s;
	int a;
	int d;
	int left;
	int right;
	int esc;
} t_input;

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
	double time;
	double old_time;
	double frame_time;
	double move_speed;
    double rotate_speed;
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
	double text_step;
	double text_position;
	int bytes;
	int offset;
	int tx;
    int ty;
	double wallX;
	
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
	t_input		input;
	t_render	render_data;
	t_mlx		mlx;
	t_tex		textures[4];
	t_mini		minimap;
	t_cam		cam;
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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define texWidth 64
#define texHeight 64

#define KEY_ESC     65307
#define KEY_LEFT    65361
#define KEY_RIGHT   65363
#define KEY_W       119
#define KEY_S       115
#define KEY_A       97
#define KEY_D       100

void	free_map_info(void);
void	init_data(char *path);
t_map	*get_map_instance(void);
int		get_arr_size(char **arr);
double	get_current_time_ms(void);
int		get_map_height(char **map);
int		get_line_width(char *line);
int		*get_player_position(char **map);
void	free_bidimensional_array(char **arr);
void	free_tridimensional_array(char ***content);
void	free_arr_with_null(char **arr, int splitted_arr_size);
void	clean_all_and_message_error(char *msg, char ***content, char **map);
void	handle_error(t_validation_status status, char ***content, char **map);

#endif