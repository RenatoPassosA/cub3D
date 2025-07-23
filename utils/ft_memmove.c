/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:24:21 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 09:24:26 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
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
	if (cdest <= csrc)
		return (ft_memcpy(dest, src, n));
	cdest += n - 1;
	csrc += n - 1;
	while (index < n)
	{
		*cdest-- = *csrc--;
		index++;
	}
	return (fp);
}