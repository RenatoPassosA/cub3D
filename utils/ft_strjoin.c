/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:22:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/22 12:22:26 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*result;
	char	*first_point;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	first_point = result;
	if (result)
	{
		if (s1 && *s1)
			ft_memmove(result, s1, len_s1);
		result += len_s1;
		if (s2 && *s2)
			ft_memmove(result, s2, len_s2);
	}
	return (first_point);
}