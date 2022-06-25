/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:14:51 by eward             #+#    #+#             */
/*   Updated: 2022/06/25 16:17:00 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_to_pipe(char **src)
{
	int	i;

	i = 0;
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
	t_cmd	*s, *e, *f;
	int		i;
	
	f = (t_cmd *)malloc(sizeof(t_cmd));
	g_shell.cmd_start = &f;
	s = (t_cmd *)malloc(sizeof(t_cmd));
	f->prev = NULL;
	e = f;
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
