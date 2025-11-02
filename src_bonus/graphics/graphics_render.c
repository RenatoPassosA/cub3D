/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviana-v <mviana-v@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:49 by renato            #+#    #+#             */
/*   Updated: 2025/11/02 18:16:26 by mviana-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"

static void    set_perp_dist(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    if (data->side == 0)
        data->perp_wall_dist = (data->map_x - map->player.pos_x + (1 - data->step_x) / 2) / data->ray_dir_x;
        
    else
        data->perp_wall_dist = (data->map_y - map->player.pos_y + (1 - data->step_y) / 2) / data->ray_dir_y;
    
}


void set_door_plane(t_map *map, int id)
{
    double offset;
    double x_plane;
    double y_plane;
    double t;
    double Y_hit;
    double X_hit;
    double frac;
    double perpdist;
    int tx;
    int tw;

    

    offset = map->doors[id].open_amount * 0.4999;
    if (map->doors[id].orientation == DOOR_VERTICAL)
    {
        if (map->doors[id].is_open)
            return;
        x_plane = map->doors[id].x + 0.5 + offset;
        if (!(map->doors[id].x <= x_plane && x_plane < map->doors[id].x + 1))
            return ;
        if (fabs(map->render_data.ray_dir_x) < 0.000001)
            return ;
        if (map->render_data.ray_dir_x != 0)
        {
            t = (x_plane - map->player.pos_x) / map->render_data.ray_dir_x;
            if (t <= 0)
            {
                return;
            }
            Y_hit = map->player.pos_y + t * map->render_data.ray_dir_y;
            if (!(map->doors[id].y <= Y_hit && Y_hit < map->doors[id].y + 1)) {
                return;
            }
         
            frac = Y_hit - floor(Y_hit);
            perpdist = t * map->render_data.ray_view_cos;
            if (perpdist <= 0)
                return;
            tx = (int)(frac * map->textures[6].width);
            if (tx < 0)
                tx = 0;
            tw = map->textures[6].width;
            if (tx >= tw)
                tx = tw - 1;
        }
         if (!map->render_data.door_has_hit || t < map->render_data.door_t)
         {
            map->render_data.door_has_hit = 1;
            map->render_data.door_t = t;
            map->render_data.door_perp_dist = perpdist;
            map->render_data.door_is_vertical = 1;
            map->render_data.door_hitx = x_plane;
            map->render_data.door_hity = Y_hit;
            map->render_data.door_tx = tx;
            map->render_data.door_id = id;
        }

        
    }
    else if (map->doors[id].orientation == DOOR_HORIZONTAL)
    {
        if (map->doors[id].is_open)
            return;
        y_plane = map->doors[id].y + 0.5 + offset;
        if (!(map->doors[id].y <= y_plane && y_plane < map->doors[id].y + 1))
            return ;
        if (fabs(map->render_data.ray_dir_y) < 0.000001)
            return ;
        if (map->render_data.ray_dir_y != 0)
        {
                        
            t = (y_plane - map->player.pos_y) / map->render_data.ray_dir_y;

            if (t <= 0)
                return;
            X_hit = map->player.pos_x + t * map->render_data.ray_dir_x;

            if (!(map->doors[id].x <= X_hit && X_hit < map->doors[id].x + 1))
                return;
            frac = X_hit - floor(X_hit);
            perpdist = t * map->render_data.ray_view_cos;
            if (perpdist <= 0)
                return;
            tx = (int)(frac * map->textures[6].width);
            if (tx < 0)
                tx = 0;
            tw = map->textures[6].width;
            if (tx >= tw)
                tx = tw - 1;
        }

         if (!map->render_data.door_has_hit || t < map->render_data.door_t)
         {
            map->render_data.door_has_hit = 1;
            map->render_data.door_t = t;
            map->render_data.door_perp_dist = perpdist;
            map->render_data.door_is_vertical = 0;
            map->render_data.door_hitx = X_hit;
            map->render_data.door_hity = y_plane;
            map->render_data.door_tx = tx;
            map->render_data.door_id = id;
        }

        
    }
    
    
}

static int is_wall_like(char c)
{
    return (c == '1' || c == ' ' || c == '\0');
}

static void    check_hit_wall(t_map *map)
{
    t_render *data;
    int roww;
    int did;

    data = &map->render_data;
    while (!data->hit)
    {
        if (data->side_dist_x < data->side_dist_y)
        {
            data->side_dist_x += data->delta_x;
            data->map_x += data->step_x;
            data->side = 0;
        }
        else
        {
            data->side_dist_y += data->delta_y;
            data->map_y += data->step_y;
            data->side = 1;
        }      
        if (data->map_y < 0 || data->map_y >= get_map_height(map->map))
        {
            data->hit = true;
            break;
        }

        roww = get_line_width(map->map[data->map_y]);
        if (data->map_x < 0 || data->map_x >= roww)
        {
            data->hit = true;
            break;
        }

        char cell = map->map[data->map_y][data->map_x];
        if (is_wall_like(cell))
            data->hit = true;
        else if (cell == 'D')
        {
            did = get_door_id(map, data->map_y, data->map_x);
            set_door_plane(map, did);
        }
    }
}

static void    get_ray_direction(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    if (data->ray_dir_x < 0)
    {
        data->step_x = -1;
        data->side_dist_x = (map->player.pos_x - data->map_x) * data->delta_x;
    }
    else
    {
        data->step_x = 1;
        data->side_dist_x = (data->map_x + 1.0 - map->player.pos_x) * data->delta_x;
    }
    if (data->ray_dir_y < 0)
    {
        data->step_y = -1;
        data->side_dist_y = (map->player.pos_y - data->map_y) * data->delta_y;
    }
    else
    {
        data-> step_y = 1;
        data->side_dist_y = (data->map_y + 1.0 - map->player.pos_y) * data->delta_y;
    }
}

static void    set_initial_data(t_map *map, int x)
{
    t_render *data;

    data = &map->render_data;
    data->map_x = (int)map->player.pos_x;
    data->map_y = (int)map->player.pos_y;
    data->hit = false;
    data->side = 0;
    data->camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1;
    data->ray_dir_x = map->player.dirX + map->player.planeX * data->camera_x;
    data->ray_dir_y = map->player.dirY + map->player.planeY * data->camera_x;
    data->delta_x = fabs(1 / data->ray_dir_x);
    data->delta_y = fabs(1 / data->ray_dir_y);
    data->is_door = 0;
	data->door_has_hit = false;
	
}

void    draw_target()
{
    t_map   *map;

    map = get_map_instance();
    
    int len = fmax(8, SCREEN_HEIGHT/100);
    int t = 2;
    int color = 0xFFFFFF;
    int cx = SCREEN_WIDTH / 2;
    int cy = SCREEN_HEIGHT / 2;
    int x = cx - len;
    int y = cy - t;

    while (x <= cx + len)
    {
       if (abs(x - cx) < 3)
            {
                x++;
                continue;
            }
        while (y <= cy + t)
        {
            if ((unsigned)x >= SCREEN_WIDTH || (unsigned)y >= SCREEN_HEIGHT)
                continue;
            map->render_data.offset = y * map->mlx.size_line + x * (map->mlx.bits_per_pixel/8);
            *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = color;
            y++;
        }
        y = cy - t;
        x++;
    }
    x = cx - t;
    while (y <= cy + len)
    {
       if (abs(y - cy) < 3)
            {
                y++;
                continue;
            }
        while (x <= cx + t)
        {
            if ((unsigned)x >= SCREEN_WIDTH || (unsigned)y >= SCREEN_HEIGHT)
                continue;
            map->render_data.offset = y * map->mlx.size_line + x * (map->mlx.bits_per_pixel/8);
            *(uint32_t *)(map->mlx.img_data + map->render_data.offset) = color;
            x++;
        }
        x = cx - t;
        y++;
    }
    
    
}

void    render()
{
    t_map   *map;
    t_tex   *texture;
    int x;
    float cosA;
    
    map = get_map_instance();
    x = -1;    
    ft_memset(map->mlx.img_data, 0, SCREEN_WIDTH * SCREEN_HEIGHT * (map->mlx.bits_per_pixel / 8));
    render_floor_and_ceiling();
    while (++x < SCREEN_WIDTH)
    {
        map->render_data.door_has_hit = 0;
        set_initial_data(map, x);
        get_ray_direction(map);

        cosA = map->render_data.ray_dir_x * map->player.dirX + map->render_data.ray_dir_y * map->player.dirY;
        map->render_data.ray_view_cos = cosA;
        
        check_hit_wall(map);
        set_perp_dist(map);
        if (map->render_data.perp_wall_dist <= 0)
            continue;
        set_texture_and_coordinates(map, &texture);
        if (map->render_data.door_has_hit && map->render_data.door_perp_dist < map->render_data.perp_wall_dist - 1e-6)
            set_door_height(map);
        else
            set_wall_height(map);
        if (map->render_data.draw_end < 0 || map->render_data.draw_start >= SCREEN_HEIGHT || map->render_data.line_height <= 0)
            continue;
        if (map->render_data.door_has_hit && map->render_data.door_perp_dist < map->render_data.perp_wall_dist - 1e-6)
            draw_doors(map, x);
        else
            draw_walls(map, texture, x);
    }
    set_priority_order();
    render_sprites();
    draw_target();
    mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win_ptr, map->mlx.img_ptr, 0, 0);
    // mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win_ptr, map->mlx.cursor_img, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

}










/*A cada coluna da tela (cada coluna de pixel vertical), você lança um raio da posição do jogador e vê onde ele bate numa parede.
Com isso, você calcula a que distância a parede está e desenha uma linha vertical com altura proporcional a essa distância.

formulas:
    camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        converte os valores de x (colunas de pixel da tela, de 0 até SCREEN_WIDTH - 1) em um intervalo contínuo de valores entre -1 e +1

    ray_dir_x = dir_x + plane_x * camera_x;
    ray_dir_y = dir_y + plane_y * camera_x;

    dir_x e dir_y - valores com base no plano cartesiano para ver pra onde está virado (N: 0, 1; S: 0, -1; E: 1, 0; W: -1, 0)
    plane_x e Y - FOV (field of view) - vetor perpendicular que define a abertura de angulo do campo de visão - defini como 0.66

    rayX e rayY representam para qual direção esse raio está apontando no espaço 2D - esse vetor não representa distância, mas sim orientação e inclinação do raio.
    

    delta_x e delta_y dizem quanto o raio anda em linha reta até bater na próxima linha de grade, no eixo X ou Y.
    delta_x = fabs(1 / ray_dir_x) - o 1 é uma convenção do tamanho do tile. se assume que o mapa está em escala 1:1, onde cada célula tem tamanho 1 no mundo 2D.

    step_x = -1 ou 1; - qual direção o raio vai andar no eixo X (esquerda ou direita)
    Se o raio está indo para a esquerda, você vai testar o tile map_x - 1, depois map_x - 2, etc.
    Se está indo para a direita, vai testar map_x + 1, map_x + 2, etc.

    side_dist_x = (pos_x - map_x) * delta_x; - qual a distância inicial do raio até a primeira linha vertical de tile que ele vai cruzar
    Se o raio está indo para a esquerda (ray_dir_x < 0):
    pos_x - map_x → quanto falta para chegar na borda esquerda do tile atual
    Multiplica por delta_x para saber quanto o raio anda em linha reta para chegar lá
    
    side_dist_x = (map_x + 1.0 - pos_x) * delta_x;
    map_x + 1.0 - pos_x → quanto falta para chegar na borda direita do tile atual
    Multiplica por delta_x para converter isso em distância reta no mundo

    perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
    é o quanto a parede está “para dentro” do cenário
    map_x - pos_x    → distância entre o jogador e a grade à esquerda da célula onde o raio bateu
    (1 - step_x) / 2    → compensação para saber em qual lado da célula o raio bateu:
    Se step_x == 1 (indo pra direita): (1 - 1)/2 = 0
    Se step_x == -1 (indo pra esquerda): (1 - (-1))/2 = 1
    ➤ Isso desloca a borda para o lado certo da célula.

    Soma tudo e divide por ray_dir_x
    → converte a distância X em distância real ao longo do raio
    (tipo: “andei X em linha reta na direção do raio: quantas unidades isso representa?”)
    perp_wall_dist é a distância real (corrigida) até a parede. Ela será usada para calcular a altura da parede renderizada

    line_height = SCREEN_HEIGHT / perp_wall_dist
    É a altura em pixels que a parede deve ter na tela.
    Quanto mais longe a parede estiver, menor será a linha.

    draw_start = -line_height / 2 + SCREEN_HEIGHT / 2
    draw_end = line_height / 2 + SCREEN_HEIGHT / 2
    draw start e draw end seria onde eu começaria a desenhar somente a parede
    esses limites fazem com que a parede seja desenhada crescendo metade para cima e metade para baixo do centro da tela
    Parede próxima → perp_wall_dist é pequeno → line_height é grande
    ⟶ A parede vai ocupar quase a tela inteira
    ⟶ O céu e o chão ficam pequenos (como se estivesse colado na parede)
    Parede distante → perp_wall_dist é grande → line_height é pequena
    ⟶ A parede ocupa pouca altura vertical
    ⟶ O céu e o chão ficam maiores (como se você visse ao longe)
    
    calculo do indice do pixel
    index = (y * line_length) + (x * (bits_per_pixel / 8))
    a imagem é um grande vetor de memória (um array de bytes), você precisa calcular o índice exato dentro desse vetor onde o pixel (x, y) está.
    A imagem é armazenada linha por linha na memória (como uma matriz linearizada). Cada linha contem a largura da imagem × bytes por pixel
    A imagem na MiniLibX é um bloco contínuo de memória (um array de bytes), e cada pixel ocupa múltiplos bytes (geralmente 4)
    Quando você quer desenhar um pixel na posição (x, y) você não acessa diretamente uma matriz do tipo image[y][x] Em vez disso, você calcula manualmente o 
    deslocamento (offset), ou seja, quantos bytes precisa pular para chegar naquele ponto no buffer da imagem.
    y * line_length: pula todas as linhas anteriores
    x * (bits_per_pixel / 8): pula os pixels anteriores daquela linha

    tx e ty são coordenadas da textura

    wall_x define Em que ponto da parede (ao longo da sua largura) o raio bateu
*/
