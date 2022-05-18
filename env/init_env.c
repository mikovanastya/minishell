/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/16 15:39:03 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	init_env(char **prmtrs, t_shell *shell)// инициализация env, скопировать весь env терминал в новый созданный envp
{
	int	i;

	i = 0;
	while (prmtrs[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (prmtrs[i])
	{
		shell->envp[i] = ft_strdup(prmtrs[i]);
		i++;
	}
	shell->envp[i] = NULL;
}

///int	new_envp_set(t_env *env, char *str, char **tmp) перезаписывает нашт  env
//set установить добавлять и редактировать 