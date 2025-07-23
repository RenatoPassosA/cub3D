/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:26:54 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 09:27:16 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	void	*result;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	s += start;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	result = ft_calloc(len + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	result = ft_memmove(result, s, len);
	return ((char *)result);
}