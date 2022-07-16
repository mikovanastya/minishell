/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:12:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 16:15:11 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char *prmtrs)
{
	int		i;
	char	*value;
	char	*tmp;

	tmp = NULL;
	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (g_shell.envp[i])
	{
		tmp = ft_substr(g_shell.envp[i], 0, ft_strchr(g_shell.envp[i], '=')
				- g_shell.envp[i] + 1);
		if (ft_strncmp(tmp, prmtrs, ft_strlen(prmtrs)) == 0)
		{
			value = ft_strdup(ft_strchr(g_shell.envp[i], '=') + 1);
			return (value);
		}
		free(tmp);
		i++;
	}
	return (ft_strdup(" "));
}
