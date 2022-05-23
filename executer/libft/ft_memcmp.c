/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:42:46 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/15 15:00:28 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *dest, const void *src, size_t n)
{
	while (n--)
	{
		if ((*(unsigned char *)dest) != (*(unsigned char *)src))
			return ((*(unsigned char *)dest) - (*(unsigned char *)src));
		dest++;
		src++;
	}
	return (0);
}
