/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_envp_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:14:39 by eward             #+#    #+#             */
/*   Updated: 2022/06/02 15:14:43 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	repl_equal(char **to_change, char *repl, int i)
{
	int	j;

	j = 0;
	while (*(repl + j))
	{
		*(*to_change + i + j) = *(repl + j);
		j++;
	}
	return (i + ft_strlen(repl));
}

int	repl_more(char **to_change, char *repl, int i, int a)
{
	int		j;
	int		b;

	b = ft_strlen(repl);
	j = 0;
	while (*(*to_change + i + j + a - b))
	{
		*(*to_change + i + j) = *(*to_change + i + j + a - b);
		j++;
	}
	*(*to_change + i + j) = '\0';
	repl_equal(to_change, repl, i);
	return (i + ft_strlen(repl));
}

int	delete_var(char **to_change, int i, int a)
{
	while (*(*to_change + i + a))
	{
		*(*to_change + i) = *(*to_change + i + a);
		i++;
	}
	*(*to_change + i) = '\0';
	return (i + 1);
}

int	repl_less(char **to_change, char *repl, int i, int a)
{
	char	*t;
	int		b;
	int		j;

	b = ft_strlen(repl);
	t = ft_strdup(*to_change);
	j = ft_strlen(t);
	while (j > i + a - 1)
	{
		(*to_change)[j + b - a] = (*to_change)[j];
		j--;
	}
	repl_equal(to_change, repl, i);
	*(*to_change + ft_strlen(t) + b - a) = '\0';
	free(t);
	return (i + ft_strlen(repl));
}

int	sub_envp(char **to_change, char **repl, int i, int a)
{
	if (*repl == 0)
		return (delete_var(to_change, i, a));
	else if (a == (int)ft_strlen(*repl))
		return (repl_equal(to_change, *repl, i));
	else if (a > (int)ft_strlen(*repl))
		return (repl_more(to_change, *repl, i, a));
	else if (a < (int)ft_strlen(*repl))
		return (repl_less(to_change, *repl, i, a));
	return (0);
}
