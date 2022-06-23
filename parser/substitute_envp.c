/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:49:33 by eward             #+#    #+#             */
/*   Updated: 2022/06/02 12:49:35 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*тут запихиваем переменные среды в глобальную переменную */

int	arr_len(char **arr)
{
	int	rez;

	rez = 0;
	while (*(arr + rez))
		rez++;
	return (rez);
}

int	set_envp(char **envp)
{
	int	i;

	i = 0;
	g_shell.envp = (char **)malloc(sizeof(char *) * (arr_len(envp) + 1));
	if (!g_shell.envp)
		return (-1);
	while (envp[i])
	{
		g_shell.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_shell.envp[i] = NULL;
	return (1);
}

char	*find_var(char *what_to_find)
{
	int		i;
	int		j;
	int		found;

	found = 0;
	i = 0;
	while (g_shell.envp[i] && found == 0)
	{
		j = 0;
		while (g_shell.envp[i][j] == what_to_find[j])
			j++;
		if (g_shell.envp[i][j] == '=' && !what_to_find[j])
			found = 1;
		i++;
	}
	i--;
	if (found == 1)
		return (ft_strdup(g_shell.envp[i] + j + 1));
	return (0);
}

void	skip_quotes(char *input, int *i)
{
	g_shell.quote = input[(*i)++];
	if (*(input + (*i) - 1) == '\'' && g_shell.quote != '\"')
	{
		(*i)++;
		while (*(input + (*i)) && *(input + (*i)) != '\'')
			(*i)++;
	}
}

int	substitute_envp(char *input, char **envp)
{
	int		i;

	i = 0;
	if (!set_envp(envp))
		return (-1);
	while (*(input + i))
	{
		while (*(input + i) && is_space(*(input + i)))
			i++;
		if ((*(input + i) == '\'' || *(input + i) == '\"') && !g_shell.quote)
			skip_quotes(input, &i);
		if (*(input + i) == '$' && g_shell.quote != '\'')
			replace(&input, i);
		if (*(input + i))
			i++;
		if ((*(input + i) == '\'' || *(input + i) == '\"')
			&& g_shell.quote == *(input + i))
			g_shell.quote = 0;
	}
	return (0);
}
