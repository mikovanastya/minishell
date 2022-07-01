/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:47:24 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 17:37:19 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_new_env(char **tmp, char *prmtrs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (j < g_shell.len)
	{
		if (ft_strncmp(ft_substr(g_shell.envp[j], 0, ft_strchr(g_shell.envp[j], '=')
					- g_shell.envp[j] + 1), prmtrs, ft_strlen(prmtrs)) != 0)
		{
			tmp[i] = g_shell.envp[j];
			i++;
			j++;
		}
		else
			j++;
	}
}

int	del_env(char *prmtrs)
{
	char	**tmp;

	if (env_prmtrs_exist(prmtrs))// если параметр существует 
	{
		tmp = malloc(sizeof(char *) * (g_shell.len));
		del_new_env( tmp, prmtrs);
		g_shell.len--;
		g_shell.envp = tmp;
	}
	return (0);
}
