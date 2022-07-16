/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:54:48 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 16:55:20 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	separate_str(char ***arr, char **str, t_cmd	*cmd)
{
	t_for_array	pos;
	int			creation_rez;

	((cmd)->redir) = NULL;
	pos.i = 0;
	g_shell.quote = 0;
	while (**str && sp(**str))
				(*str)++;
	while (**str && !n_a(**str))
	{
		creation_rez = create_element(&pos, str, arr, cmd);
		if (creation_rez != 0)
			return (creation_rez);
	}
	if (**str)
		if (**str == '|')
			(*str)++;
	(*arr)[pos.i] = NULL;
	return (0);
}
