/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:14:15 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/23 19:23:24 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_prmtrs_exist(t_shell *shell, char *prmtrs)//проверяем существует ли после = 
{
	int	i;

	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (shell->envp[i] && i < shell->len)
	{
		if (ft_strncmp(ft_substr(shell->envp[i], 0, ft_strchr(shell->envp[i], '=')
					- shell->envp[i] + 1), prmtrs, ft_strlen(prmtrs)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	new_env(t_shell *shell, char *str, char **tmp)//записывваем  еще чтобы расширить место памяти
{
	int	i;

	i = 0;
	shell->envp = malloc(sizeof(char *) * (shell->len + 2));// \0 и еще место под новую строчку(место в машине)
	while (i < shell->len)
	{
		shell->envp[i] = tmp[i];
		i++;
	}
	shell->envp[i] = str;
	return (0);
}

void	rewrite_env_prmtrs(t_shell *shell, char *prmtrs, char *join)// все перезаписывем чтобы изменить указатель на массив и добавить в новую  tmp
{
	int	i;

	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (i < shell->len)
	{
		if (shell->envp[i])
		{
			if (ft_strncmp(ft_substr(shell->envp[i], 0,
					ft_strchr(shell->envp[i], '=') - shell->envp[i] + 1),
					prmtrs, ft_strlen(prmtrs) == 0))
			{
				shell->envp[i] = join;
			}
		}
		i++;
	}
}

int	set_env(t_shell *shell, char *prmtrs, char *value)// обЪединяет параметр и значение
{
	char	**tmp;
	char	*result_1st_join;
	char	*result_2nd_join;

	
	result_1st_join = ft_strjoin(prmtrs, "=");
	result_2nd_join = ft_strjoin(result_1st_join, value);
	if (env_prmtrs_exist(shell, prmtrs))//проверяем существует ли такой prmtrs
	{
		rewrite_env_prmtrs(shell, prmtrs, result_2nd_join);// все перезаписывем чтобы изменить указатель на строчку
	}
	else
	{
		tmp = shell->envp;
		new_env(shell, result_2nd_join, tmp);
		shell->len++;
	}
	return (0);
}
