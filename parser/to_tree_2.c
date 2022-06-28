/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:10:38 by eward             #+#    #+#             */
/*   Updated: 2022/06/28 20:34:22 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_filename(t_cmd	*cmd, char **str, char **a)
{
	cmd->file_name = (char **)malloc(sizeof(char *));
	*(cmd->file_name) = ft_strdup(*a);
	free(*a);
	*a = NULL;
	if (**str)
		while (**str && sp(**str))
	(*str)++;
	if (**str)
		while (**str && **str != '|' && !n_a(**str))
			(*str)++;
}

void	skip_quotes_in_separation(char **str, char *a, int *j)
{
	g_shell.quote = **str;
	(*str)++;
	while (**str && g_shell.quote != **str)
	{
		a[(*j)++] = **str;
		(*str)++;
	}
	if (**str)
		(*str)++;
	g_shell.quote = 0;
}

int	new_elem(char **str, char ***arr, int *i, int *j)
{
	*j = 0;
	(*i)++;
	(*arr)[*i] = (char *)malloc(sizeof(char) * (word_len(*str) + 1));
	if (!(*arr)[*i])
		return (-1);
	while (**str && sp(**str))
		(*str)++;
	return (0);
}

void	create_element(t_for_array	*pos, char **str, char ***arr,
	t_cmd	*cmd)
{
	if (is_a(*str) != 0)
	{
		arrow_action(str, &cmd);
		new_elem(str, arr, &(pos->i), &(pos->j));
	}
	if (!g_shell.quote && (**str == '\"' || **str == '\''))
		skip_quotes_in_separation(str, (*arr)[pos->i], &(pos->j));
	else
	{
		(*arr)[pos->i][pos->j++] = **str;
		(*str)++;
	}
}

int	separate_str(char ***arr, char **str, t_cmd	*cmd)
{
	t_for_array	pos;

	((cmd)->redir) = NULL;
	pos.i = 0;
	g_shell.quote = 0;
	while (**str && **str != '|' && !n_a(**str))
	{
		go_to_word(&((*arr)[pos.i]), &(pos.j), str);
		while (**str && **str != '|' && !n_a(**str) && !sp(**str))
			create_element(&pos, str, arr, cmd);
		(*arr)[pos.i][pos.j] = '\0';
		if ((cmd->redir))
			add_filename(cmd, str, &((*arr)[pos.i]));
		else
			cmd->file_name = NULL;
		if (**str)
			while (**str && sp(**str))
				(*str)++;
		pos.i++;
	}
	if (**str)
		if (**str == '|')
			(*str)++;
	(*arr)[pos.i] = NULL;
	return (0);
}
