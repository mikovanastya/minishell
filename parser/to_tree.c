/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:07:52 by eward             #+#    #+#             */
/*   Updated: 2022/06/18 14:07:54 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// &
// | +
// > 1
// >> 2
// < 3
// << 4

// int	service_symbol(char **str)
// {

// }

int	count_elements(char **str)
{
	int	n;
	int	i;

	n = 1;
	i = 0;
	g_shell.quote = 0;
	while (*(*str + i))
	{
		if ((*(*str + i) == '\'' || *(*str + i) == '\"') && !g_shell.quote)
		{
			g_shell.quote = *(*str + i);
			n++;
			i++;
			while (*(*str + i) != g_shell.quote && *(*str + i))
				i++;
			i++;
			g_shell.quote = 0;
		}
		while (is_space(*(*str + i)))
			i++;
		if (*(*str + i))
			n++;
		printf("%d %d %d %d\n", !is_space(*(*str + i)), *(*str + i), !is_arrow(*str + i), not_allowed(*(*str + i)));
		while (!is_space(*(*str + i)) && *(*str + i) && !is_arrow(*str + i) && !not_allowed(*(*str + i)))
			i++;
		i++;
	}
	return (n);
}

int	count_until_spaces(char	*str)
{
	int	i;

	i = 0;
	g_shell.quote = 0;
	while (str[i] != ' ' && str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && !g_shell.quote)
		{
			g_shell.quote = str[i];
			i++;
			while (str[i] != g_shell.quote && str[i])
				i++;
			g_shell.quote = 0;
		}
		i++;
	}
	i++;
	printf("word len %d\n", i);
	return (i + 1);
}
int	put_str_to_tree(char **str)
{
	char	**rez;
	int		num;
	int		i;
	int		j;
	int		k;

	num = count_elements(str);
	rez = (char **)malloc(sizeof(char *) * num);
	if (!rez)
		return (0);
	rez[num - 1] = NULL;
	i = 0;
	k = 0;
	g_shell.quote = 0;
	while (i < num - 1)
	{
		while (is_space(*(*str + k)))
			k++;
		rez[i] = (char *)malloc(sizeof(char) * count_until_spaces(*str + k));
		j = 0;
		while (*(*str + k) != ' ' && *(*str + k))
		{
			if ((*(*str + k) == '\"' || *(*str + k) == '\'') && !g_shell.quote)
			{
				g_shell.quote = *(*str + k);
				k++;
				while (*(*str + k) != g_shell.quote && *(*str + k))
				{
					rez[i][j] = *(*str + k);
					j++;
					k++;
				}
				g_shell.quote = 0;
			}
			else
			{
				rez[i][j] = *(*str + k);
				j++;
			}
			
			k++;
		}
		rez[i][j] = '\0';
		printf("rez %s\n", rez[i]);
		i++;
	}
	return (0);
}