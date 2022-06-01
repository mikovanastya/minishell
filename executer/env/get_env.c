/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:12:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/27 15:08:36 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(t_shell *shell, char *prmtrs)// получаю значение параметра
{
	int		i;
	char	*value;

	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (shell->envp[i])
	{
		if (ft_strncmp(ft_substr(shell->envp[i], 0, ft_strchr(shell->envp[i], '=')
					- shell->envp[i] + 1), prmtrs, ft_strlen(prmtrs)) == 0)//ищем в строке подстроку prmtrs до =, считая длинну сравниваем 
		{
			value = ft_strdup(ft_strchr(shell->envp[i], '=') + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(" "));
}
