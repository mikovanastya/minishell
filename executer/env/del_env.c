/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:47:24 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/27 18:36:00 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_new_env(t_shell *shell, char **tmp, char *prmtrs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (j < shell->len)
	{
		if (ft_strncmp(ft_substr(shell->envp[j], 0, ft_strchr(shell->envp[j], '=')
					- shell->envp[j] + 1), prmtrs, ft_strlen(prmtrs)) != 0)
		{
			tmp[i] = shell->envp[j];
			i++;
			j++;
		}
		else
			j++;
	}
}

int	del_env(t_shell *shell, char *prmtrs)
{
	char	**tmp;

	if (env_prmtrs_exist(shell, prmtrs))// если параметр существует 
	{
		tmp = malloc(sizeof(char *) * (shell->len));
		del_new_env(shell, tmp, prmtrs);
		shell->len--;
		shell->envp = tmp;
	}
	return (0);
}
