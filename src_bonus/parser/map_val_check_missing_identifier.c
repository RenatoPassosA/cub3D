/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_missing_identifier.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:30:01 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/26 15:11:16 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

t_validation_status	check_missing_identifier(char ***content)
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
			return (ERR_MISSING_IDENTIFIER);
	return(VALIDATION_OK);
}
