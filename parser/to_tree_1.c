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
			{
				g_shell.quote = *src;
				src++;
				while (*src && g_shell.quote != *src)
					src++;
				if (*src)
					src++;
				g_shell.quote = 0;
			}
			if ((*src) == '|' || is_a(src) != 0)
				break ;
			src++;
		}
		if ((*src) == '|' || is_a(src) != 0)
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
		if (*(str + len) != '|' && is_a((str + len)) == 0
			&& n_a(*(str + len)) && !sp(*(str + len)))
			break ;
		len++;
	}
	return (len);
}

int	separate_str(char ***arr, char **str)
{
	int	i;
	int	j;

	i = 0;
	g_shell.quote = 0;
	while (**str && **str != '|' && is_a(*str) == 0
		&& !n_a(**str))
	{
		j = 0;
		(*arr)[i] = (char *)malloc(sizeof(char) * (word_len(*str) + 1));
		if (!(*arr)[i])
			return (-1);
		while (**str && sp(**str))
			(*str)++;
		while (**str && **str != '|' && is_a(*str) == 0
			&& !n_a(**str) && !sp(**str))
		{
			if (!g_shell.quote && (**str == '\"' || **str == '\''))
			{
				g_shell.quote = **str;
				(*str)++;
				while (**str && g_shell.quote != **str)
				{
					(*arr)[i][j] = **str;
					j++;
					(*str)++;
				}
				if (**str)
					(*str)++;
				g_shell.quote = 0;
			}
			else
			{
				(*arr)[i][j] = **str;
				j++;
				(*str)++;
			}
		}
		(*arr)[i][j] = '\0';
		if (**str)
			while (**str && sp(**str))
				(*str)++;
		i++;
	}
	(*arr)[i] = NULL;
	i = 0;
	while ((*arr)[i])
	{
		printf("%s\n", (*arr)[i]);
		i++;
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
	separate_str(&(new->argv), str);
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

void	fill_list(char	*str)
{
	g_shell.cmd_start = (t_cmd **)malloc(sizeof(t_cmd *));
	*(g_shell.cmd_start) = NULL;
	while (*str)
		add_elem(g_shell.cmd_start, &str);
}
