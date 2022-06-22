/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/20 18:58:05 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ms_matrix_add_line(char **matrix, char *new_line)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(new_line);
	i++;
	new_matrix[i] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

void	check_shlvl(t_shell *shell)
{
	char	*var;
	char	*var1;
	int		num;
	char	**arg;

	var = get_env(shell->envp, "SHLVL");
	if (var == NULL)
	{
		shell->envp = ms_matrix_add_line(shell->envp, "SHLVL=1");// переделать функцию
		return ;
	}
	arg = ft_split(var, '=');
	num = ft_atoi(arg[1]);
	num++;
	var = ft_itoa(num);
	var1 = ft_strjoin("SHLVL=", var);
	set_env(shell->envp, var1, shell);
	free (var);
	free (var1);
	//ft_free_tab(arg);
	return ;
}

void	init_env(char **prmtrs, t_shell *shell)// инициализация env, скопировать весь env терминал в новый созданный envp
{
	int	i;

	i = 0;
	while (prmtrs[i])
		i++;
	//printf("HERE %d\n", i);
	shell->envp = malloc(sizeof(char *) * (i + 1));
	shell->len = i;
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