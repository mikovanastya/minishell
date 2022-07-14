/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_filenames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:26:46 by eward             #+#    #+#             */
/*   Updated: 2022/07/14 12:26:48 by eward            ###   ########.fr       */
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
			return (print_token_err(*str));
		else if (n_a(*str))
			return (rez);
		rez++;
	}
	return (print_token_err(*str));
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

int	add_more(char **str, t_cmd *cmd, int i)
{
	int	len;
	int	j;

	j = 0;
	while (**str && sp(**str))
		(*str)++;
	if (!*str || n_a(**str))
		return (print_token_err(**str));
	if (is_a(*str))
	{
		(*(cmd->redir))[0] = **str;
		(*str)++;
		(*(cmd->redir))[1] = '\0';
		if (is_a(*str))
		{
			(*(cmd->redir))[1] = **str;
			(*str)++;
			(*(cmd->redir))[2] = '\0';
		}
	}
	len = filename_len(*str);
	printf("filename len %d\n", len);
	if (len == 0)
	{
		while (**str && sp(**str))
			(*str)++;
		return (print_token_err(**str));
	}
	cmd->file_name[i] = (char *)malloc(sizeof(char) * (len + 1));
	while (**str && sp(**str))
		(*str)++;
	while (**str && !sp(**str) && !n_a(**str) && !is_a(*str))
	{
		cmd->file_name[i][j] = **str;
		(*str)++;
		j++;
	}
	cmd->file_name[i][j] = '\0';
	if (**str)
		while (**str && !n_a(**str) && !is_a(*str))
			(*str)++;
	return (0);
}

int	add_filename(t_cmd	*cmd, char **str, char **a)
{
	int	len;
	int	i;

	if (!**a)
	{
		if (**str)
			while (**str && sp(**str))
				(**str)++;
		return (print_token_err(**str));
	}
	len = count_filenames(*str, *a);
	if (len == -1)
		return (-1);
	cmd->file_name = (char **)malloc(sizeof(char *) * (len + 1));
	*(cmd->file_name) = ft_strdup(*a);
	free(*a);
	*a = NULL;
	i = 1;
	if (**str)
	{
		while (**str)
		{
			if (add_more(str, cmd, i) == -1)
				return (-1);
			i++;
		}
	}
	cmd->file_name[i] = "\0";
	return (0);
}
