/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:14:51 by eward             #+#    #+#             */
/*   Updated: 2022/07/05 17:52:16 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quotes_in_len(char **src)
{
	g_shell.quote = **src;
	(*src)++;
	while (**src && g_shell.quote != **src)
		(*src)++;
	if (**src)
		(*src)++;
	g_shell.quote = 0;
}

int	len_to_pipe(char *src)
{
	int	i;

	g_shell.quote = 0;
	i = 0;
	if (!src)
		return (1);
	while (*src)
	{
		while (*src && sp(*src))
			src++;
		while (*src && !sp(*src))
		{
			if (!g_shell.quote && (*src == '\"' || *src == '\''))
				skip_quotes_in_len(&src);
			if ((*src) == '|')
				break ;
			if (*src != '\0')
				src++;
		}
		if (src)
			if ((*src) == '|')
				break ;
		i++;
	}
	return (i + 1);
}

int	word_len(char *str)
{
	int	len;

	len = 0;
	g_shell.quote = 0;
	while (*(str + len))
	{
		if (!g_shell.quote && (*(str + len) == '\"' || *(str + len) == '\''))
		{
			g_shell.quote = *(str + len);
			len++;
			while (*(str + len) && g_shell.quote != *(str + len))
				len++;
			if (*(str + len))
				len++;
			g_shell.quote = 0;
		}
		if (n_a(*(str + len)) || sp(*(str + len)) || !(*(str + len)))
			break ;
		len++;
	}
	return (len);
}

int	arrow_action(char **str, t_cmd	**cmd)
{
	((*cmd)->redir) = (char **)malloc(sizeof(char *));// проверка
	*((*cmd)->redir) = (char *)malloc(sizeof(char) * 3);
	if (is_a(*str) % 2)
	{
		ft_strlcpy(*((*cmd)->redir), *str, 2);
		(*str)++;
	}
	else
	{
		ft_strlcpy(*((*cmd)->redir), *str, 3);
		*str = (*str) + 2;
	}
	return (0);
}

int	add_elem(t_cmd **cmd, char **str)
{
	t_cmd	*new;
	t_cmd	*last;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	last = *cmd;
	new->argv = (char **)malloc(sizeof(char *) * len_to_pipe(*str));
	if (separate_str(&(new->argv), str, new) == -1)
		return (-1);
	new->next = NULL;
	if (*cmd == NULL)
	{
		new->prev = NULL;
		*cmd = new;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	if (**str)
		(*str)++;
	return (0);
}
