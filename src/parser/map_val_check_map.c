/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:00:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 13:55:29 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_validation_status validate_map_existence(char ***content)
{
	int index;
	int	map_height;
	
	index = 0;
	map_height = 0;
	while (content[index] && (is_type_identifier(content[index][0]) ||
       ft_strcmp(content[index][0], "\n") == 0))
		index++;
	while (content[index] && *content[index][0] == '1')
	{
		index++;
		map_height++;
	}
	while (content[index])
		return(ERR_DATA_AFTER_MAP);
	if (map_height == 0)
		return(ERR_MISSING_MAP);
	return(VALIDATION_OK);
}
