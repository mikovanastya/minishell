/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:41:01 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/15 15:08:27 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmp_dst;
	char	*tmp_src;

	tmp_dst = (char *)dest;
	tmp_src = (char *)src;
	if (tmp_dst == 0 && tmp_src == 0)
		return (0);
	while (n--)
	{
		*tmp_dst++ = *tmp_src++;
	}
	return (dest);
}
