/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:31:51 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/18 14:24:09 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			str = (char *)&s[i];
		}
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (str);
}
