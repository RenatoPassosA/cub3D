/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:49 by renato            #+#    #+#             */
/*   Updated: 2025/09/01 13:01:11 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_bonus.h"
#include "../game/game_bonus.h"

static void    set_perp_dist(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    if (data->side == 0)
        data->perpWallDist = (data->mapX - map->player.posX + (1 - data->stepX) / 2) / data->rayDirX;
    else
        data->perpWallDist = (data->mapY - map->player.posY + (1 - data->stepY) / 2) / data->rayDirY;
    
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
        if (fabs(map->render_data.rayDirX) < 0.000001)
            return ;
        if (map->render_data.rayDirX != 0)
        {
            t = (x_plane - map->player.posX) / map->render_data.rayDirX;
            if (t <= 0)
            {
                return;
            }
            Y_hit = map->player.posY + t * map->render_data.rayDirY;
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
        if (fabs(map->render_data.rayDirY) < 0.000001)
            return ;
        if (map->render_data.rayDirY != 0)
        {
                        
            t = (y_plane - map->player.posY) / map->render_data.rayDirY;

            if (t <= 0)
                return;
            X_hit = map->player.posX + t * map->render_data.rayDirX;

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
        if (data->sideDistX < data->sideDistY)
        {
            data->sideDistX += data->deltaDistX;
            data->mapX += data->stepX;
            data->side = 0;
        }
        else
        {
            data->sideDistY += data->deltaDistY;
            data->mapY += data->stepY;
            data->side = 1;
        }      
        if (data->mapY < 0 || data->mapY >= get_map_height(map->map))
        {
            data->hit = true;
            break;
        }

        roww = get_line_width(map->map[data->mapY]);
        if (data->mapX < 0 || data->mapX >= roww)
        {
            data->hit = true;
            break;
        }

        char cell = map->map[data->mapY][data->mapX];
        if (is_wall_like(cell))
            data->hit = true;
        else if (cell == 'D')
        {
            did = get_door_id(map, data->mapY, data->mapX);
            set_door_plane(map, did);
        }
    }
}

static void    get_ray_direction(t_map *map)
{
    t_render *data;

    data = &map->render_data;
    if (data->rayDirX < 0)
    {
        data->stepX = -1;
        data->sideDistX = (map->player.posX - data->mapX) * data->deltaDistX;
    }
    else
    {
        data->stepX = 1;
        data->sideDistX = (data->mapX + 1.0 - map->player.posX) * data->deltaDistX;
    }
    if (data->rayDirY < 0)
    {
        data->stepY = -1;
        data->sideDistY = (map->player.posY - data->mapY) * data->deltaDistY;
    }
    else
    {
        data-> stepY = 1;
        data->sideDistY = (data->mapY + 1.0 - map->player.posY) * data->deltaDistY;
    }
}

static void    set_initial_data(t_map *map, int x)
{
    t_render *data;

    data = &map->render_data;
    data->mapX = (int)map->player.posX;
    data->mapY = (int)map->player.posY;
    data->hit = false;
    data->side = 0;
    data->cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1;
    data->rayDirX = map->player.dirX + map->player.planeX * data->cameraX;
    data->rayDirY = map->player.dirY + map->player.planeY * data->cameraX;
    data->deltaDistX = fabs(1 / data->rayDirX);
    data->deltaDistY = fabs(1 / data->rayDirY);
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

        cosA = map->render_data.rayDirX * map->player.dirX + map->render_data.rayDirY * map->player.dirY;
        map->render_data.ray_view_cos = cosA;
        
        check_hit_wall(map);
        set_perp_dist(map);
        if (map->render_data.perpWallDist <= 0)
            continue;
        set_texture_and_coordinates(map, &texture);
        if (map->render_data.door_has_hit && map->render_data.door_perp_dist < map->render_data.perpWallDist - 1e-6)
            set_door_height(map);
        else
            set_wall_height(map);
        if (map->render_data.drawEnd < 0 || map->render_data.drawStart >= SCREEN_HEIGHT || map->render_data.lineHeight <= 0)
            continue;
        if (map->render_data.door_has_hit && map->render_data.door_perp_dist < map->render_data.perpWallDist - 1e-6)
            draw_doors(map, x);
        else
            draw_walls(map, texture, x);
    }
    draw_target();
    mlx_put_image_to_window(map->mlx.mlx_ptr, map->mlx.win_ptr, map->mlx.img_ptr, 0, 0);
}










/*A cada coluna da tela (cada coluna de pixel vertical), você lança um raio da posição do jogador e vê onde ele bate numa parede.
Com isso, você calcula a que distância a parede está e desenha uma linha vertical com altura proporcional a essa distância.

formulas:
    cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        converte os valores de x (colunas de pixel da tela, de 0 até SCREEN_WIDTH - 1) em um intervalo contínuo de valores entre -1 e +1

    rayDirX = dirX + planeX * cameraX;
    rayDirY = dirY + planeY * cameraX;

    dirX e dirY - valores com base no plano cartesiano para ver pra onde está virado (N: 0, 1; S: 0, -1; E: 1, 0; W: -1, 0)
    planeX e Y - FOV (field of view) - vetor perpendicular que define a abertura de angulo do campo de visão - defini como 0.66

    rayX e rayY representam para qual direção esse raio está apontando no espaço 2D - esse vetor não representa distância, mas sim orientação e inclinação do raio.
    

    deltaDistX e deltaDistY dizem quanto o raio anda em linha reta até bater na próxima linha de grade, no eixo X ou Y.
    deltaDistX = fabs(1 / rayDirX) - o 1 é uma convenção do tamanho do tile. se assume que o mapa está em escala 1:1, onde cada célula tem tamanho 1 no mundo 2D.

    stepX = -1 ou 1; - qual direção o raio vai andar no eixo X (esquerda ou direita)
    Se o raio está indo para a esquerda, você vai testar o tile mapX - 1, depois mapX - 2, etc.
    Se está indo para a direita, vai testar mapX + 1, mapX + 2, etc.

    sideDistX = (posX - mapX) * deltaDistX; - qual a distância inicial do raio até a primeira linha vertical de tile que ele vai cruzar
    Se o raio está indo para a esquerda (rayDirX < 0):
    posX - mapX → quanto falta para chegar na borda esquerda do tile atual
    Multiplica por deltaDistX para saber quanto o raio anda em linha reta para chegar lá
    
    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    mapX + 1.0 - posX → quanto falta para chegar na borda direita do tile atual
    Multiplica por deltaDistX para converter isso em distância reta no mundo

    perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    é o quanto a parede está “para dentro” do cenário
    mapX - posX    → distância entre o jogador e a grade à esquerda da célula onde o raio bateu
    (1 - stepX) / 2    → compensação para saber em qual lado da célula o raio bateu:
    Se stepX == 1 (indo pra direita): (1 - 1)/2 = 0
    Se stepX == -1 (indo pra esquerda): (1 - (-1))/2 = 1
    ➤ Isso desloca a borda para o lado certo da célula.

    Soma tudo e divide por rayDirX
    → converte a distância X em distância real ao longo do raio
    (tipo: “andei X em linha reta na direção do raio: quantas unidades isso representa?”)
    perpWallDist é a distância real (corrigida) até a parede. Ela será usada para calcular a altura da parede renderizada

    lineHeight = SCREEN_HEIGHT / perpWallDist
    É a altura em pixels que a parede deve ter na tela.
    Quanto mais longe a parede estiver, menor será a linha.

    drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2
    drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2
    draw start e draw end seria onde eu começaria a desenhar somente a parede
    esses limites fazem com que a parede seja desenhada crescendo metade para cima e metade para baixo do centro da tela
    Parede próxima → perpWallDist é pequeno → lineHeight é grande
    ⟶ A parede vai ocupar quase a tela inteira
    ⟶ O céu e o chão ficam pequenos (como se estivesse colado na parede)
    Parede distante → perpWallDist é grande → lineHeight é pequena
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

    wallx define Em que ponto da parede (ao longo da sua largura) o raio bateu
*/