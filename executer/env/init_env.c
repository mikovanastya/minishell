/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/24 18:34:36 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_shlvl(t_shell *shell)
{
	t_cmd	*cmd;
	int		nb_shlvl;
	char	*str_shlvlv;
	char	*final_str;
	char	**cmnd_words;

	while (cmd != NULL)
	{
		if (strcmp("SHLVL", cmd->argv[0]) == 0)
		{
			if (cmd->argv[1] != NULL)
				nb_shlvl = ft_atoi(cmd->argv[1]) + 1;
			else
				nb_shlvl = 1;
		}
		cmd = cmd->next;
	}
	str_shlvlv = ft_itoa(nb_shlvl);
	final_str = ft_strjoin("export SHLVL=", str_shlvlv);
	cmnd_words = ft_split(final_str, ' ');
	builtin_export(cmnd_words, shell);
	ft_free_str(&str_shlvlv);
	ft_free_str(&final_str);
	ft_free_str_arr(&cmnd_words);
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
	//check_shlvl(shell);
	return ;
}

///int	new_envp_set(t_env *env, char *str, char **tmp) перезаписывает нашт  env
//set установить добавлять и редактировать 