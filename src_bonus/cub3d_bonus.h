/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:55 by rpassos-          #+#    #+#             */
/*   Updated: 2025/11/02 18:20:44 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

#include "../utils/utils.h"

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdint.h>

typedef void (*t_render_fn)(void *data);

typedef enum e_monster_type {
    FLYING = 0,
    GROUND  = 1,
}   t_mon_type;

typedef enum e_monster_state {
    MON_IDLE = 0,
    MON_CHASE  = 1,
    MON_DEAD   = 2
}   t_mon_state;

typedef enum e_player_state {
    ALIVE = 0,
    DEAD   = 1
}   t_player_state;

typedef struct s_gun {
	double cooldown;
	double fire_interval;
	int damage;
	float recoil_kick_y;
	float recoil_decay_y;
	bool is_firing;
	bool	shot_pressed;
} t_gun;

typedef struct s_monster_type {
	int	type_id;
	int		max_hp;
	float r_mon;
	float speed_chase;
	float	r_detect;
	float	r_lost;
	int		index_walk_sprite_1;
	int		index_walk_sprite_2;
	int		index_died_sprite;
	float		time_frame_walk;
	float v_move_world;
	t_mon_type type;
	
	
} t_monster_type;

typedef struct s_monster {
	int	id;
	int	type_id;
	float x;
	float y;
	float x_speed;
	float y_speed;
	int	hp;
	t_mon_state	state;
	int	animation_index;
	float t_animation;
	float x_screen;
	float height_screen;
	float dist;
	double transformY;
	float x_left;
	float x_right;
	float y_top;
	float y_bottom;
	float y_center_monster;
	bool is_damaged;
	float damage_timer;
} t_monster;

typedef struct s_sprites {
    float x;
	float y;
	float	z_offset;
	int	texture_id;
	int	opening_dir;
	bool	collision;
	float	dist;
	double transformY;
	double transformX;
	bool	is_mush;
	bool	is_visible;
} t_sprite;

typedef enum e_sprite_type {
    MONSTER = 0,
    SPRITE  = 1,
}   t_type;

typedef struct e_render_list {
	void *data;
	t_render_fn	render_fn;
	float	transform_y;
	t_type	type;
	
} t_render_list;

typedef struct s_door {
    int x;
	int y;
	int	orientation;
	double open_amount;
	int	opening_dir;
	bool	is_open;
	long long opened_at;
} t_door;

typedef struct s_camera {
	float pitch_offset;
	float base_pitch;
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
	int	door_color;
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
	int use;
	int esc;
} t_input;

typedef struct mlx_data
{
	void				*mlx_ptr;
	void				*win_ptr;	
	void				*img_ptr;
	void				*img_data;
	void				*cursor_img;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
} t_mlx;

typedef struct player_infos
{
	double	pos_x;
	double	pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double time;
	double old_time;
	double frame_time;
	double move_speed;
    double rotate_speed;
	double r_player;
	t_player_state state;
	bool	is_high;
	float	trippy_duration;
	float	trippy_phase;
} t_player;

typedef struct render_data
{
	double	camera_x;
    double	ray_dir_x;
    double	ray_dir_y;
    int		map_x;
    int		map_y;
    double	delta_x;
    double	delta_y;
    double	step_x;
    double	step_y;
    double	side_dist_x;
    double	side_dist_y;
    bool	hit;
    int		side;
    double	perp_wall_dist;
    int		line_height;
    int		draw_start;
    int		draw_end;
	int		color;
	double text_step;
	double text_position;
	int bytes;
	int offset;
	int tx;
    int ty;
	double wall_x;

	int is_door;
	bool door_has_hit;
	double door_t;
	double door_perp_dist;
	double door_hitx;
	double door_hity;
	int door_is_vertical;
	int door_tx;
	int door_id;
	
	float ray_view_cos;
} t_render;

typedef struct map_infos
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_rgb;
	int			ceiling_rgb;
	int			map_lines;
	int			fd;
	char		**map;
	int			num_doors;
	int			num_sprites;
	int			num_monsters;
	double		*z_buffer;
	t_player	player;
	t_input		input;
	t_render	render_data;
	t_mlx		mlx;
	t_tex		textures[19];
	t_mini		minimap;
	t_cam		cam;
	t_door		*doors;
	t_sprite	*sprites;
	t_monster_type monster_type[2];
	t_monster	*monsters;
	t_render_list	*render_list;
	t_gun	gun;

	int frame_index;
	float time_accumulator;
	float frame_duration;
	int frames [4];

	
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

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define TEXT_WIDTH 64
#define TEXT_HEIGHT 64
#define PI 3.14

#define DOOR_VERTICAL 1
#define DOOR_HORIZONTAL 2

#define DOOR_THRESHOLD 0.88

#define KEY_ESC     65307
#define KEY_W       119
#define KEY_S       115
#define KEY_A       97
#define KEY_D       100
#define KEY_E		101

#define PILLAR 7
#define LIGHT 8
#define BARREL 9
#define MUSH 13

#define CHROMA 0x000000

#define MUMMY 0
#define MONSTER 1



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
