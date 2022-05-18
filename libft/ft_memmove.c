/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:58:16 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/20 15:15:26 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*tmp_dst;
	char			*tmp_src;
	unsigned int	i;

	tmp_dst = (char *)dest;
	tmp_src = (char *)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (tmp_src <= tmp_dst)
	{
		while (n-- != '\0')
		{
			tmp_dst[n] = tmp_src[n];
		}
	}
	else
	{
		while (i < n)
		{
			tmp_dst[i] = tmp_src[i];
			i++;
		}
	}
	return (dest);
}
