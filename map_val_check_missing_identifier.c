/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_missing_identifier.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:30:01 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/30 10:50:39 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_missing_identifier(char ***content)
{
	int		index;
	int		identifier_counter;

	index = 0;
	identifier_counter = 0;
	while(content[index] != NULL)
	{
		if (is_type_identifier(content[index][0]))
			identifier_counter++;
		index++;
	}
	if (identifier_counter != 6)
		clean_all_and_message_error("Error.\n Missing type identifier element.", content, NULL);
}