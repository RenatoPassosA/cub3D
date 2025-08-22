/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_map_position.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:36:27 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/19 13:54:51 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	check_map_on_top(char ***content)
{
	if (!is_type_identifier(content[0][0]) && ft_strcmp(content[0][0], "\n") != 0)
		return(false);
	return(true);
}

static bool	check_map_on_middle(char ***content)
{
	int		index;
	int		identifier_counter;
	
	index = 0;
	identifier_counter = 0;
	while(content[index] != NULL)
	{
		if (is_type_identifier(content[index][0]))
			identifier_counter++;
		else if (ft_strcmp(content[index][0], "\n") == 0)
		{
			index++;
			continue;
		}
		else if (!is_type_identifier(content[index][0]) &&
				ft_strcmp(content[index][0], "\n") != 0 &&
				identifier_counter != 6)
			return (false);
		index++;
	}
	return (true);
}

t_validation_status	validate_map_position(char ***content)
{
	if (!check_map_on_top(content) || !check_map_on_middle(content))
		return(ERR_INVALID_MAP_POSITION);
	return(VALIDATION_OK);
}
