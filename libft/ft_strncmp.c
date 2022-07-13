/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:13:29 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/12 19:57:18 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strncmp(const char *str1, const char *str2, size_t n)
// {
// 	unsigned char	*s1;
// 	unsigned char	*s2;

// 	s1 = (unsigned char *)str1;
// 	s2 = (unsigned char *)str2;
// 	while (n-- && (*s1 != '\0' || *s2 != '\0'))
// 	{
// 		if (*s1 != *s2)
// 		{
// 			return (*s1 - *s2);
// 		}
// 		s1++;
// 		s2++;
// 	}
// 	return (0);
// }
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		ret;
	size_t	i;

	i = 1;
	ret = 0;
	if (n == 0)
		return (0);
	while (*((unsigned char *)s1) && *((unsigned char *)s2) && i < n)
	{
		if (*((unsigned char *)s1) == *((unsigned char *)s2))
		{
			++i;
			++s1;
			++s2;
		}
		else
			break ;
	}	
	ret = *((unsigned char *)s1) - *((unsigned char *)s2);
	return (ret);
}
