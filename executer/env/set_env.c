/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:14:15 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 15:46:55 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_prmtrs_exist(char *prmtrs)//проверяем существует ли после = 
{
	int	i;

	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (g_shell.envp[i] && i < g_shell.len)
	{
		// if (g_shell.envp[i])
		// 	printf("g_shell.envp[i] %s\n", g_shell.envp[i]);
		if (ft_strncmp(ft_substr(g_shell.envp[i], 0, ft_strchr(g_shell.envp[i], '=')
					- g_shell.envp[i] + 1), prmtrs, ft_strlen(prmtrs)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	new_env(char *str)//записывваем  еще чтобы расширить место памяти
{
	int	i;

	i = 0;
	char **tmp;
	tmp = malloc(sizeof(char *) * (g_shell.len + 2));// \0 и еще место под новую строчку
	while (i < g_shell.len)
	{
		tmp[i] = g_shell.envp[i];
		i++;
	}
	tmp[i] = str;
	g_shell.envp = tmp;
	return (0);
}

void	rewrite_env_prmtrs(char *prmtrs, char *join)// все перезаписывем чтобы изменить указатель на массив и добавить в новую  tmp
{
	int	i;

	i = 0;
	prmtrs = ft_strjoin(prmtrs, "=");
	while (i < g_shell.len)
	{
		if (g_shell.envp[i])
		{		
			if (ft_strncmp(ft_substr(g_shell.envp[i], 0, \
				ft_strchr(g_shell.envp[i], '=') - g_shell.envp[i] + 1), \
				prmtrs, ft_strlen(prmtrs)) == 0)
			{
				g_shell.envp[i] = join;
			}
		}
		i++;
	}
}

// void	rewrite_env_prmtrs(char *prmtrs, char *join)
// {
// 	int		j;

// 	j = 0;
// 	// new_mass = malloc(sizeof(char *) * (size_mass() + 1));
// 	if (!prmtrs)
// 		return (NULL);
// 	while (g_shell.envp[j])
// 	{
// 		if (ft_strncmp(g_shell.envp[j], join, max(ft_strlen(join),
// 					ft_sym_export(g_shell.envp[j]))))
// 			prmtrs[j] = ft_strdup(g_shell.envp[j]);
// 		else
// 			prmtrs[j] = ft_strdup(g_shell.argv);
// 		j++;
// 	}
// 	prmtrs[j] = NULL;
// 	ft_free(g_shell.envp);
// 	return (prmtrs);
// }

int	set_env(char *prmtrs, char *value)// обЪединяет параметр и значение
{
	char	*result_1st_join;
	char	*result_2nd_join;

	result_1st_join = ft_strjoin(prmtrs, "=");
	result_2nd_join = ft_strjoin(result_1st_join, value);
	if (env_prmtrs_exist(prmtrs))//проверяем существует ли такой prmtrs
	{
		// *g_shell.envp = ft_strdup(result_2nd_join);
		rewrite_env_prmtrs(prmtrs, result_2nd_join);// все перезаписывем чтобы изменить указатель на строчку
	}
	else
	{
		new_env(result_2nd_join);
		g_shell.len++;
	}
	return (0);
}

