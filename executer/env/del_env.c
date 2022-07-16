/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:47:24 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 16:23:29 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_new_env(char **tmp, char *prmtrs)
{
	int		i;
	int		j;
	char	*t;

	i = 0;
	j = 0;
	t = NULL;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (j < g_shell.len)
	{
		t = ft_substr(g_shell.envp[j], 0, ft_strchr(g_shell.envp[j], '=')
				- g_shell.envp[j] + 1);
		if (ft_strncmp(t, prmtrs, ft_strlen(prmtrs)) != 0)
		{
			tmp[i] = g_shell.envp[j];
			i++;
			j++;
		}
		else
			j++;
		free(t);
	}
}

int	del_env(char *prmtrs)
{
	char	**tmp;

	if (env_prmtrs_exist(prmtrs))
	{
		tmp = malloc(sizeof(char *) * (g_shell.len));
		del_new_env(tmp, prmtrs);
		g_shell.len--;
		g_shell.envp = tmp;
	}
	return (0);
}
