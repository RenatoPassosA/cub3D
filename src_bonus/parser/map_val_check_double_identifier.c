/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val_check_double_identifier.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:30:01 by rpassos-          #+#    #+#             */
/*   Updated: 2025/08/26 15:11:22 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

static void	init_identifiers(int *identifiers)
{
	identifiers[0] = 0;
	identifiers[1] = 0;
	identifiers[2] = 0;
	identifiers[3] = 0;
	identifiers[4] = 0;
	identifiers[5] = 0;
}

static void	set_identifier_flag(int *identifier, char *splitted)
{
	if (ft_strcmp(splitted, "NO") == 0)
		identifier[NO] = 1;
	if (ft_strcmp(splitted, "SO") == 0)
		identifier[SO] = 1;
	if (ft_strcmp(splitted, "WE") == 0)
		identifier[WE] = 1;
	if (ft_strcmp(splitted, "EA") == 0)
		identifier[EA] = 1;
	if (ft_strcmp(splitted, "F") == 0)
		identifier[F_RGB] = 1;
	if (ft_strcmp(splitted, "C") == 0)
		identifier[C_RGB] = 1;
}

static bool	check_identifier_flag(int *identifier, char *splitted)
{
	return (((ft_strcmp(splitted, "NO") == 0) && identifier[NO]) ||
	((ft_strcmp(splitted, "SO") == 0) && identifier[SO]) ||
	((ft_strcmp(splitted, "WE") == 0) && identifier[WE]) ||
	((ft_strcmp(splitted, "EA") == 0) && identifier[EA]) ||
	((ft_strcmp(splitted, "F") == 0) &&	identifier[F_RGB]) ||
	((ft_strcmp(splitted, "C") == 0) &&	identifier[C_RGB]));
}

t_validation_status	check_double_identifier(char ***content)
{
	int		identifiers[6];
	int		index;

	index = 0;
	init_identifiers(identifiers);
	while(content[index] != NULL)
	{
		if (is_type_identifier(content[index][0]))
		{
			if (check_identifier_flag(identifiers, content[index][0]))
				return(ERR_DOUBLE_IDENTIFIER);
			else
				set_identifier_flag(identifiers, content[index][0]);
		}
		index++;
	}
	return(VALIDATION_OK);
}
