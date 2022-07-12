/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/12 20:17:36 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> 
#include <readline/readline.h> 
#include <readline/history.h>
#include <readline/readline.h>

/*
**	всё вместе:
*/

int	main(int argc, char **argv, char **env)
{
	char	*rez;
	// t_shell	shell;
	t_cmd	*cmd;
	int		i;
	t_list	*tokens;
	t_cmd **ex_cmd;

	tokens = NULL;
	ex_cmd = NULL;

	(void)i;
	//g_shell = (t_shell)malloc(sizeof(t_shell));
	if (argc != 1)
	 	ft_error(argv[0], EINVAL);
	cmd = NULL;
	init_env(env);
	printf("ENP LEN INIT %d=%d \n", g_shell.len, envp_len_global());
	while (1)
	{
		rez = get_str(env); // !! parser
		fill_list(rez); // !! parser
		cmd = (*(g_shell.cmd_start)); // это вообще очень важеая хреня не дуалять
		// int i  = 0;
		// while (cmd->argv[i])
		// {
		// 	printf("argv %s \n", cmd->argv[i]);
		// 	i++;
		// }
		if (cmd)
			pipex(cmd);
		free(rez);
		//free struct!!!!!
	}
	return (0);
}

int envp_len_global(void) {
		int i = 0;
	while (g_shell.envp[i])
		i++;
	return i;
}


int envp_len_local(char **envp) {
	int i = 0;
	while (envp[i])
		i++;
	return i;
}

void envp_compr() {
	printf("Glob=%d %d=gshell_len", envp_len_global(), g_shell.len);
}