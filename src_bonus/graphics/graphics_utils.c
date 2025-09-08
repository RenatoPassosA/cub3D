/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:43:54 by renato            #+#    #+#             */
/*   Updated: 2025/09/04 15:48:23 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"

double	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
}

void	init_textures()
{
	t_map   *map;
    
    map = get_map_instance();

	map->textures[0].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, (char *)map->NO_texture, &map->textures[0].width, &map->textures[0].height);
	map->textures[1].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, (char *)map->SO_texture, &map->textures[1].width, &map->textures[1].height);
	map->textures[2].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, (char *)map->WE_texture, &map->textures[2].width, &map->textures[2].height);
	map->textures[3].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, (char *)map->EA_texture, &map->textures[3].width, &map->textures[3].height);
	map->textures[4].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/colorstone.xpm", &map->textures[4].width, &map->textures[4].height);
	map->textures[5].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/ceiling.xpm", &map->textures[5].width, &map->textures[5].height);
	map->textures[6].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/door.xpm", &map->textures[6].width, &map->textures[6].height);
	map->textures[7].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/pillar.xpm", &map->textures[7].width, &map->textures[7].height);
	map->textures[8].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/light.xpm", &map->textures[8].width, &map->textures[8].height);
	map->textures[9].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/barrel.xpm", &map->textures[9].width, &map->textures[9].height);
	map->textures[10].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/mummy-l.xpm", &map->textures[10].width, &map->textures[10].height);
	map->textures[11].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/mummy-r.xpm", &map->textures[11].width, &map->textures[11].height);
	map->textures[12].img = mlx_xpm_file_to_image(map->mlx.mlx_ptr, "./textures/diedmummy.xpm", &map->textures[12].width, &map->textures[12].height);
	

	if (!map->textures[0].img || !map->textures[1].img || !map->textures[2].img || !map->textures[3].img || !map->textures[4].img || !map->textures[5].img) //inserir loop para verificar tudo
	{
		clean_all_and_message_error("Error on loading texture.", NULL, NULL);
		quit_game();
	}
	
	map->textures[0].addr = mlx_get_data_addr(map->textures[0].img, &map->textures[0].bpp, &map->textures[0].line_len, &map->textures[0].endian);
	map->textures[1].addr = mlx_get_data_addr(map->textures[1].img, &map->textures[1].bpp, &map->textures[1].line_len, &map->textures[1].endian);
	map->textures[2].addr = mlx_get_data_addr(map->textures[2].img, &map->textures[2].bpp, &map->textures[2].line_len, &map->textures[2].endian);
	map->textures[3].addr = mlx_get_data_addr(map->textures[3].img, &map->textures[3].bpp, &map->textures[3].line_len, &map->textures[3].endian);
	map->textures[4].addr = mlx_get_data_addr(map->textures[4].img, &map->textures[4].bpp, &map->textures[4].line_len, &map->textures[4].endian);
	map->textures[5].addr = mlx_get_data_addr(map->textures[5].img, &map->textures[5].bpp, &map->textures[5].line_len, &map->textures[5].endian);
	map->textures[6].addr = mlx_get_data_addr(map->textures[6].img, &map->textures[6].bpp, &map->textures[6].line_len, &map->textures[6].endian);
	map->textures[7].addr = mlx_get_data_addr(map->textures[7].img, &map->textures[7].bpp, &map->textures[7].line_len, &map->textures[7].endian);
	map->textures[8].addr = mlx_get_data_addr(map->textures[8].img, &map->textures[8].bpp, &map->textures[8].line_len, &map->textures[8].endian);
	map->textures[9].addr = mlx_get_data_addr(map->textures[9].img, &map->textures[9].bpp, &map->textures[9].line_len, &map->textures[9].endian);
	map->textures[10].addr = mlx_get_data_addr(map->textures[10].img, &map->textures[10].bpp, &map->textures[10].line_len, &map->textures[10].endian);
	map->textures[11].addr = mlx_get_data_addr(map->textures[11].img, &map->textures[11].bpp, &map->textures[11].line_len, &map->textures[11].endian);
	map->textures[12].addr = mlx_get_data_addr(map->textures[12].img, &map->textures[12].bpp, &map->textures[12].line_len, &map->textures[12].endian);
	

	if (!map->textures[0].addr || !map->textures[1].addr || !map->textures[2].addr || !map->textures[3].addr || !map->textures[4].addr || !map->textures[5].addr  || !map->textures[6].addr) //inserir loop para verificar tudo
	{
		clean_all_and_message_error("Error on loading texture.", NULL, NULL);
		quit_game();
	}

}



uint32_t texel_at(const t_tex *t, int tx, int ty)
{
    int bytes;
    size_t offset;

	bytes = t->bpp / 8; 
	offset = (size_t)ty * t->line_len + (size_t)tx * bytes;
    return (*(uint32_t *)((unsigned char *)t->addr + offset));
}

