/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:10:38 by eward             #+#    #+#             */
/*   Updated: 2022/07/16 17:50:29 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	create_argv(t_for_array	*pos, char **str, char ***arr,
	t_cmd	*cmd)
{
	if (is_a(*str) != 0)
	{
		arrow_action(str, &cmd);
		new_elem(str, arr, &(pos->i), &(pos->j));
		pos->i--;
	}
	if (!g_shell.quote && (**str == '\"' || **str == '\''))
		skip_quotes_in_separation(str, (*arr)[pos->i], &(pos->j));
	else
	{
		(*arr)[pos->i][pos->j++] = **str;
		(*str)++;
	}
}

void	skip_spaces(char **str)
{
	if (**str)
		while (**str && sp(**str))
			(*str)++;
}

int	create_element(t_for_array	*pos, char **str, char ***arr,
	t_cmd	*cmd)
{
	go_to_word(&((*arr)[pos->i]), &(pos->j), str);
	while (**str && !n_a(**str) && !sp(**str))
		create_argv(pos, str, arr, cmd);
	(*arr)[pos->i][pos->j] = '\0';
	if (cmd->redir)
	{
		while (*((*arr)[pos->i]) && sp(*((*arr)[pos->i])))
			((*arr)[pos->i])++;
		if (is_a(((*arr)[pos->i])))
			return (print_token_err('7'));
		if (add_filename(cmd, str, &((*arr)[pos->i])) == -1)
			return (-1);
		if (is_a(cmd->redir) == 4)
		{
			cmd->file_name = NULL;
			return (0);
		}
		pos->i--;
	}
	else
		cmd->file_name = NULL;
	skip_spaces(str);
	pos->i++;
	return (0);
}
