/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:09 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/18 17:34:21 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	if (!s)
		return (0);
	j = (size_t) start;
	if ((size_t) start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len < (ft_strlen(s) - (size_t) start))
		size = len;
	else
		size = ft_strlen(s) - (size_t) start;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i++] = s[j++];
	}
	str[i] = '\0';
	return (str);
}
