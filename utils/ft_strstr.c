/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:41:57 by rpassos-          #+#    #+#             */
/*   Updated: 2025/07/23 13:42:17 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *ft_strstr(const char *haystack, const char *needle)
{
    size_t i;
    size_t j;

    if (!*needle)
        return (char *)haystack;
    i = 0;
    while (haystack[i])
    {
        j = 0;
        while (needle[j] && haystack[i + j] == needle[j])
            j++;
        if (!needle[j])
            return (char *)&haystack[i];
        i++;
    }
    return NULL;
}
