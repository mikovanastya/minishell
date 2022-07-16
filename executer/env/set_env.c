/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:14:15 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 19:03:12 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_prmtrs_exist(char *prmtrs)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (g_shell.envp[i] && i < g_shell.len)
	{
		tmp = ft_substr(g_shell.envp[i], 0, ft_strchr(g_shell.envp[i], '=')
				- g_shell.envp[i] + 1);
		if (ft_strncmp(tmp, prmtrs, ft_strlen(prmtrs)) == 0)
			return (1);
		free(tmp);
		i++;
	}
	return (0);
}

int	new_env(char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (g_shell.len + 2));
	while (i < g_shell.len)
	{
		tmp[i] = g_shell.envp[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	g_shell.envp = tmp;
	return (0);
}

void	rewrite_env_prmtrs(char *prmtrs, char *join)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (i < g_shell.len)
	{
		if (g_shell.envp[i])
		{
			tmp = ft_substr(g_shell.envp[i], 0, \
				ft_strchr(g_shell.envp[i], '=') - g_shell.envp[i] + 1);
			if (ft_strncmp(tmp, prmtrs, ft_strlen(prmtrs)) == 0)
				g_shell.envp[i] = join;
			free(tmp);
		}
		i++;
	}
	if (*prmtrs)
		free(prmtrs);
}

int	set_env(char *prmtrs, char *value)
{
	char	*result_1st_join;
	char	*result_2nd_join;

	result_1st_join = ft_strjoin(prmtrs, "=");
	result_2nd_join = ft_strjoin(result_1st_join, value);
	if (*result_1st_join)
		free(result_1st_join);
	if (env_prmtrs_exist(prmtrs))
		rewrite_env_prmtrs(prmtrs, result_2nd_join);
	else
	{
		new_env(result_2nd_join);
		g_shell.len++;
	}
	return (0);
}
