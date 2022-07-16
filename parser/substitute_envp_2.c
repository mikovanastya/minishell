/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_envp_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 13:59:38 by eward             #+#    #+#             */
/*   Updated: 2022/07/16 16:49:10 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace(char **to_change, int i)
{
	char	*repl;
	int		a;
	char	*var_name;
	int		rez;

	rez = 0;
	a = 1;
	var_name = NULL;
	if (*(*to_change + i + 1) == '$')
		return (repl_less(to_change, ft_itoa(g_shell.pid), i, 2));
	while (ft_isalpha(*(*to_change + i + a)) || *(*to_change + i + a) == '_'
		|| (ft_isdigit(*(*to_change + i + a)) && *(*to_change + i + a) != 1)
		|| *(*to_change + i + a) == '?')
		a++;
	var_name = (char *)malloc(sizeof(char) * (a + 1));
	ft_memmove(var_name, *to_change + i + 1, a - 1);
	var_name[a - 1] = '\0';
	repl = find_var(var_name);
	rez = sub_envp(to_change, &repl, i, a);
	if (repl)
		free(repl);
	if (var_name)
		free(var_name);
	return (rez);
}

void	skip_quotes(char *input, int *i)
{
	if ((*(input + (*i)) == '\'' || *(input + (*i)) == '\"') && !g_shell.quote)
	{
		g_shell.quote = *(input + (*i));
		(*i)++;
		if (*(input + (*i) - 1) == '\'' && g_shell.quote != '\"')
		{
			(*i)++;
			while (*(input + (*i)) && *(input + (*i)) != '\'')
				(*i)++;
		}
	}
}
