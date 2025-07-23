/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:20:51 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/22 12:21:08 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			index;
	unsigned char	*s;

	index = 0;
	s = (unsigned char *)str;
	while (index < n)
	{
		s[index] = (unsigned char)c;
		index++;
	}
	return ((void *)s);
}