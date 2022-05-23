/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:11:44 by rtwitch           #+#    #+#             */
/*   Updated: 2021/10/23 17:12:57 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int		i;
	int		words;	

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i] != '\0')
				i++;
			words++;
		}
		else
			i++;
	}
	return (words);
}

static char	**ft_write(char **str, char const *s, char c)
{
	unsigned int	j;
	unsigned int	len;
	const char		*start;

	j = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		start = (char *)s;
		while (*s != c && *s)
		{	
			s++;
			len++;
		}
		if (*(s - 1) != c)
			str[j++] = ft_substr(start, 0, len);
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char			**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!str)
		return (NULL);
	return (ft_write(str, s, c));
}
