/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 17:38:18 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_shlvl()
{
	char	*tmp;
	int		num;
	char	*digit;

	tmp = get_env_value("SHLVL=");
	num = ft_atoi(tmp) + 1;
	free(tmp);
	digit = ft_itoa(num);
	tmp = ft_strjoin("export SHLVL=", digit);
	free(digit);
	rewrite_env_prmtrs( tmp, digit);
	free(tmp);
}


void	init_env(char **prmtrs)// инициализация env, скопировать весь env терминал в новый созданный envp
{
	int	i;

	i = 0;
	while (prmtrs[i])
		i++;
	//printf("HERE %d\n", i);
	g_shell.envp = malloc(sizeof(char *) * (i + 1));
	g_shell.len = i;
	i = 0;
	while (prmtrs[i])
	{
		g_shell.envp[i] = ft_strdup(prmtrs[i]);
		i++;
	}
	g_shell.envp[i] = NULL;
	check_shlvl();
	return ;
}

//int	new_envp_set(t_env *env, char *str, char **tmp) перезаписывает нашт  env
//set установить добавлять и редактировать 