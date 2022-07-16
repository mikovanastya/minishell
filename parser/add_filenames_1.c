/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_filenames_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:38:34 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 17:23:01 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_filenames(t_cmd *cmd, char **str)
{
	int	i;

	i = 1;
	while (**str && sp(**str))
		(*str)++;
	if (**str)
	{
		while (**str)
		{
			if (add_more(str, cmd, i) == -1)
				return (-1);
			i++;
		}
	}
	cmd->file_name[i] = NULL;
	return (0);
}

int	add_filename(t_cmd	*cmd, char **str, char **a)
{
	int	len;

	if (!**a)
	{
		if (**str)
			while (**str && sp(**str))
				(**str)++;
		return (print_token_err('5'));
	}
	len = count_filenames(*str, *a);
	if (len == -1)
		return (-1);
	cmd->file_name = (char **)malloc(sizeof(char *) * (len + 1));
	*(cmd->file_name) = ft_strdup(*a);
	free(*a);
	*a = NULL;
	return (fill_filenames(cmd, str));
}
