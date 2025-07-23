/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:25:04 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/22 14:25:01 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s)
{
	int		index;
	int		length;
	char	*result;

	index = 0;
	length = ft_strlen(s);
	result = (char *)ft_calloc(length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s && s[index])
	{
		result[index] = s[index];
		index++;
	}
	return (result);
}