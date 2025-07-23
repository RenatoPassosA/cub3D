/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:29:00 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 09:29:07 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*str1;
	unsigned char	*str2;

	index = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (index < n)
	{
		if (str1[index] != str2[index])
			return (str1[index] - str2[index]);
		index++;
	}
	return (0);
}