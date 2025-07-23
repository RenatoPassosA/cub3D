/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:21:20 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/22 12:21:33 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*cdest;
	char	*csrc;
	char	*fp;
	size_t	index;

	cdest = (char *)dest;
	csrc = (char *)src;
	fp = cdest;
	index = 0;
	if (!csrc && !cdest)
		return (NULL);
	while (index < n)
	{
		cdest[index] = csrc[index];
		index++;
	}
	return (fp);
}