/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:49 by renato            #+#    #+#             */
/*   Updated: 2025/08/08 10:17:38 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render()
{
    t_map   *map;
    int x;
    int y;
    
    map = get_map_instance();
    x = 0;    
    while (x < SCREEN_WIDTH)
    {
        map->render_data.mapX = (int)map->player.posX;
        map->render_data.mapY = (int)map->player.posY;
        map->render_data.hit = false;
        map->render_data.cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1;
        map->render_data.rayDirX = map->player.dirX + map->player.planeX * map->render_data.cameraX;
        map->render_data.rayDirY = map->player.dirY + map->player.planeY * map->render_data.cameraX;
        map->render_data.deltaDistX = fabs(1 / map->render_data.rayDirX);
        map->render_data.deltaDistY = fabs(1 / map->render_data.rayDirY);
        if (map->render_data.rayDirX < 0)
        {
            map->render_data.stepX = -1;
            map->render_data.sideDistX = (map->player.posX - map->render_data.mapX) * map->render_data.deltaDistX;
        }
        else
        {
            map->render_data.stepX = 1;
            map->render_data.sideDistX = (map->render_data.mapX + 1.0 - map->player.posX) * map->render_data.deltaDistX;
        }
        if (map->render_data.rayDirY < 0)
        {
            map->render_data.stepY = -1;
            map->render_data.sideDistY = (map->player.posY - map->render_data.mapY) * map->render_data.deltaDistY;
        }
        else
        {
            map->render_data. stepY = 1;
            map->render_data.sideDistY = (map->render_data.mapY + 1.0 - map->player.posY) * map->render_data.deltaDistY;
        }
        while (!map->render_data.hit)
        {
            if (map->render_data.sideDistX < map->render_data.sideDistY)
            {
                map->render_data.sideDistX += map->render_data.deltaDistX;
                map->render_data.mapX += map->render_data.stepX;
                map->render_data.side = 0;
            }
            else
            {
                map->render_data.sideDistY += map->render_data.deltaDistY;
                map->render_data.mapY += map->render_data.stepY;
                map->render_data.side = 1;
            }
            if (map->map[map->render_data.mapY][map->render_data.mapX] == '1')
               map->render_data. hit = true;
        }
        if (map->render_data.side == 0)
            map->render_data.perpWallDist = (map->render_data.mapX - map->player.posX + (1 - map->render_data.stepX) / 2) / map->render_data.rayDirX;
        else
            map->render_data.perpWallDist = (map->render_data.mapY - map->player.posY + (1 - map->render_data.stepY) / 2) / map->render_data.rayDirY;
        
        map->render_data.lineHeight = (int)(SCREEN_HEIGHT / map->render_data.perpWallDist);




        map->render_data.drawStart = -map->render_data.lineHeight / 2 + SCREEN_HEIGHT / 2;
        map->render_data.drawEnd = map->render_data.lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (map->render_data.drawStart < 0)
            map->render_data.drawStart = 0;
        if (map->render_data.drawEnd >= SCREEN_HEIGHT)
            map->render_data.drawEnd = SCREEN_HEIGHT - 1;
            
        int index;
        y = map->render_data.drawStart;
        while (y < map->render_data.drawEnd)
        {
            index = (y * map->mlx.size_line) + (x * (map->mlx.bits_per_pixel / 8));
            if (map->render_data.side == 0 && map->render_data.rayDirX > 0)
                map->render_data.color = 0xFF0000; // leste
            else if (map->render_data.side == 0 && map->render_data.rayDirX < 0)
                map->render_data.color = 0x800000; // oeste
            else if (map->render_data.side == 1 && map->render_data.rayDirY > 0)
                map->render_data.color = 0x00FF00; // sul
            else if (map->render_data.side == 1 && map->render_data.rayDirY < 0)
                map->render_data.color = 0x008000; // norte
            *((int *)(map->mlx.img_data + index)) = map->render_data.color;
            
            y++;
        }
        x++;
    }
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

    rayX e rayY rerpesentam para qual direção esse raio está apontando no espaço 2D - esse vetor não representa distância, mas sim orientação e inclinação do raio.
    

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
*/