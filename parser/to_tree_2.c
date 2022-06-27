/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:10:38 by eward             #+#    #+#             */
/*   Updated: 2022/06/27 21:10:40 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	separate_str(char ***arr, char **str, t_cmd	*cmd)
{
	int	i;
	int	j;

	((cmd)->redir) = NULL;
	i = 0;
	g_shell.quote = 0;
	while (**str && **str != '|' && !n_a(**str))
	{
		j = 0;
		(*arr)[i] = (char *)malloc(sizeof(char) * (word_len(*str) + 1));
		if (!(*arr)[i])
			return (-1);
		while (**str && sp(**str))
			(*str)++;
		while (**str && **str != '|' && !n_a(**str) && !sp(**str))
		{
			if (is_a(*str) != 0)
			{
				arrow_action(str, &cmd);
				j = 0;
				i++;
				(*arr)[i] = (char *)malloc(sizeof(char) * (word_len(*str) + 1));
				if (!(*arr)[i])
					return (-1);
				while (**str && sp(**str))
					(*str)++;
			}
			if (!g_shell.quote && (**str == '\"' || **str == '\''))
			{
				g_shell.quote = **str;
				(*str)++;
				while (**str && g_shell.quote != **str)
				{
					(*arr)[i][j++] = **str;
					(*str)++;
				}
				if (**str)
					(*str)++;
				g_shell.quote = 0;
			}
			else
			{
				(*arr)[i][j++] = **str;
				(*str)++;
			}
		}
		(*arr)[i][j] = '\0';
		if ((cmd->redir))
		{
			cmd->file_name = (char **)malloc(sizeof(char *));
			*(cmd->file_name) = ft_strdup((*arr)[i]);
			free((*arr)[i]);
			(*arr)[i] = NULL;
			if (**str)
				while (**str && sp(**str))
					(*str)++;
			if (**str)
				while (**str && **str != '|' && !n_a(**str))
					(*str)++;
		}
		if (**str)
			while (**str && sp(**str))
				(*str)++;
		i++;
	}
	(*arr)[i] = NULL;
	return (0);
}
