/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_isolated_spaces.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:31:15 by renato            #+#    #+#             */
/*   Updated: 2025/07/29 13:32:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool find_isolated_spaces(char **map)
{
    int x;
    int y;

    x = 0;
    while (map[x])
    {
        y = 0;
        while (map[x][y])
        {
            if (map[x][y] == ' ')
                return (false);
            y++;
        }
        x++;
    }
    return (true);
}