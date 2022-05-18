/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:35:50 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/16 13:56:18 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (destsize == 0)
		return (ft_strlen(src));
	while (dest[j] != '\0' && j < destsize)
		j++;
	while (src[i] != '\0' && (j + i) < (destsize - 1))
	{
		dest[j + i] = src[i];
		i++;
	}
	if (j + i < destsize)
		dest[j + i] = '\0';
	return (j + ft_strlen(src));
}
