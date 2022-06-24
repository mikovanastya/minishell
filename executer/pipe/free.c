/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:47:56 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/24 17:49:49 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_free_str(char **s)
{
	if (*s != NULL)
	{
		free(*s);
	}
	*s = NULL;
	return (0);
}

void	*ft_free_str_arr(char ***arr)
{
	int	i;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	i = 0;
	if ((*arr) != NULL)
	{
		while ((*arr)[i] != NULL)
		{
			if ((*arr)[i] != NULL)
			{
				free((*arr)[i]);
				(*arr)[i] = NULL;
			}
			i++;
		}
		if (*arr != NULL)
			free(*arr);
		*arr = NULL;
	}
	return (NULL);
}

