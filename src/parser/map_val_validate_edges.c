/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_edges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 13:55:36 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool check_top_and_bottom_edge_no_alloc(char *line)
{
    while (*line)
    {
        if (*line == ' ')
        {
            line++;
            continue;
        }
        if (*line != '1')
            return (false);
        line++;
    }
    return (true);       
}

static bool check_middle_edges_no_alloc(char *line)
{
    char *start;
    char *end;

    start = line;
    while (*start == ' ')
        start++;
    if (*start != '1')
        return (false);
    end = start + ft_strlen(start) - 1;
    while (end > start && *end == ' ')
        end--;
    if (*end != '1')
        return (false);
    return (true);        
}

t_validation_status validate_edges(char **map)
{
    int size;
    int index;

    size = 0;
    index = 0;
    while (map[size] != NULL)
        size++;
    if (!check_top_and_bottom_edge_no_alloc(map[0]))
        return (ERR_INVALID_EDGES);
    if (!check_top_and_bottom_edge_no_alloc(map[size - 1]))
        return (ERR_INVALID_EDGES);
    while (index < size - 1)
    {
        if (!check_middle_edges_no_alloc(map[index]))
            return (ERR_INVALID_EDGES);
        index++;
    }
    return (VALIDATION_OK);
}
