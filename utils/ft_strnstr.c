/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:28:34 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/22 16:28:43 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	char	*str;
	int		diff;

	index = 0;
	str = (char *)big;
	diff = 0;
	if (!*little)
		return (str);
	while (*str && index < len)
	{
		if (index + ft_strlen(little) > len)
			break ;
		if (ft_memcmp(str, little, ft_strlen(little) + diff) == 0)
			return (str);
		str++;
		index++;
	}
	return (NULL);
}
