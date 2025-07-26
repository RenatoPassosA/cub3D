/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_validate_map_position.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:36:27 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/26 09:24:00 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		else if (!is_type_identifier(content[index][0]) && ft_strcmp(content[index][0], "\n") != 0 && identifier_counter != 6)
			return (false);
		index++;
	}
	return (true);
}

void	validate_map_position(char ***content, int fd)
{
	if (!check_map_on_top(content) || !check_map_on_middle(content))
		clean_all_and_message_error("Error.\nInvalid map position on content.", content, NULL, fd);
}
