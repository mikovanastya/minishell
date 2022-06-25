/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:14:51 by eward             #+#    #+#             */
/*   Updated: 2022/06/24 15:14:53 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_to_pipe(char **src)
{
	int	i;

	i = 1;
	if (!*src)
		return(1);
	while (*(src + 1 + i) && (*(src + i))[0] != '|')
		i++;
	if (*(src + i))
		return(i + 2);
	else
		return (i + 1);
}

void	fill_list(char	**str)
{
	t_cmd	*s, *e;
	int		i;

	g_shell.cmd_start = (t_cmd *)malloc(sizeof(t_cmd));
	s = (t_cmd *)malloc(sizeof(t_cmd));
	g_shell.cmd_start->prev = NULL;
	e = g_shell.cmd_start;
	e->next = s;
	s->prev = e;
	while (*str)
	{
		e = s;
		i = 0;
		s->argv = (char **)malloc(sizeof(char *) * len_to_pipe(str));
		printf("len to pipe %d\n", len_to_pipe(str));
		while (*str && **str != '|')
		{
			s->argv[i] = ft_strdup(*str);
			str++;
			i++;
		}
		s = (t_cmd *)malloc(sizeof(t_cmd));
		e->next = s;
		s->prev = e;
		if (*str)
			str++;
	}
	e->next = NULL;
	// while(h->prev)
	// 	h = h->prev;
}
