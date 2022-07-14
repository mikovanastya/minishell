/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:10:38 by eward             #+#    #+#             */
/*   Updated: 2022/07/12 15:50:15 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_token_err(char c)
{
	printf("minishell: syntax error near unexpected token ");
	if (c)
		printf("`%c'\n", c);
	else
		printf("`newline'\n");
	return (-1);
}

int count_filenames(char *str, char *first)
{
	int	rez;

	rez = 1;
	if (*first && !*str)
		return (1);
	while(*str && !n_a(*str))
	{
		while (*str && !n_a(*str) && !is_a(str))
			str++;
		if (!*str)
			return (rez);
		if (is_a(str))
			str++;
		while (*str && sp(*str))
			str++;
		if (*str == '&' || !*str)
			return (print_token_err(*str));
		else if (n_a(*str))
			return (rez);
		rez++;
	}
	return (print_token_err(*str));
}

void	add_more(char **str, t_cmd *cmd)
{
	while (**str && sp(**str))
		(*str)++;
	
	if (**str)
		while (**str && !n_a(**str))
			(*str)++;
}

int	add_filename(t_cmd	*cmd, char **str, char **a)
{
	int	len;

	len = count_filenames(*str, *a);
	printf("count_filename(*str)= %d\n", len);
	if (len == -1)
		return (-1);
	cmd->file_name = (char **)malloc(sizeof(char *) * (len + 1));
	*(cmd->file_name) = ft_strdup(*a);
	free(*a);
	*a = NULL;
	if (**str)
		add_more(str, cmd);
	return (0);
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

int	separate_str(char ***arr, char **str, t_cmd	*cmd)
{
	t_for_array	pos;

	((cmd)->redir) = NULL;
	pos.i = 0;
	g_shell.quote = 0;
	while (**str && sp(**str))
				(*str)++;
	while (**str && !n_a(**str))
	{
		go_to_word(&((*arr)[pos.i]), &(pos.j), str);
		while (**str && !n_a(**str) && !sp(**str))
			create_element(&pos, str, arr, cmd);
		(*arr)[pos.i][pos.j] = '\0';
		if ((cmd->redir))
		{
			if (add_filename(cmd, str, &((*arr)[pos.i])) == -1)
				return (-1);
			pos.i--;
		}
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
	//
	// pos.i = 0;
	// while ((*arr)[pos.i] != NULL)
	// {
	// 	printf("in sep %s\n", (*arr)[pos.i]);
	// 	pos.i++;
	// }
	return (0);
}
