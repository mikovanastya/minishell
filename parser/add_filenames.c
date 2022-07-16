/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_filenames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:26:46 by eward             #+#    #+#             */
/*   Updated: 2022/07/16 17:21:42 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_filenames(char *str, char *first)
{
	int	rez;

	rez = 1;
	if (*first && !*str)
		return (1);
	while (*str && !n_a(*str))
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
			return (print_token_err('1'));
		else if (n_a(*str))
			return (rez);
		rez++;
	}
	return (print_token_err('2'));
}

int	filename_len(char *str)
{
	int	len;

	len = 0;
	while (*str && sp(*str))
		(str)++;
	while (*(str + len) && !sp(*(str + len))
		&& !n_a(*(str + len)) && !is_a((str + len)))
		len++;
	return (len);
}

void	choose_redir(char **str, t_cmd *cmd, int *len)
{
	if (is_a(*str))
	{
		(cmd->redir)[0] = **str;
		(*str)++;
		(cmd->redir)[1] = '\0';
		if (is_a(*str))
		{
			(cmd->redir)[1] = **str;
			(*str)++;
			(cmd->redir)[2] = '\0';
		}
	}
	*len = filename_len(*str);
}

void	create_filename(char **str, t_cmd *cmd, int *i, int *j)
{
	while (**str && sp(**str))
		(*str)++;
	while (**str && !sp(**str) && !n_a(**str) && !is_a(*str))
	{
		cmd->file_name[*i][*j] = **str;
		(*str)++;
		(*j)++;
	}
	cmd->file_name[*i][*j] = '\0';
	if (**str)
		while (**str && !n_a(**str) && !is_a(*str))
			(*str)++;
}

int	add_more(char **str, t_cmd *cmd, int i)
{
	int	len;
	int	j;

	j = 0;
	while (**str && sp(**str))
		(*str)++;
	if (!*str || n_a(**str))
		return (print_token_err('3'));
	if (!**str)
		return (0);
	choose_redir(str, cmd, &len);
	if (len == 0)
	{
		while (**str && sp(**str))
			(*str)++;
		return (print_token_err('4'));
	}
	cmd->file_name[i] = (char *)malloc(sizeof(char) * (len + 1));
	create_filename(str, cmd, &i, &j);
	return (0);
}
