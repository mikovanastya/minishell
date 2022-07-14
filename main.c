/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 19:53:58 by rtwitch          ###   ########.fr       */
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
	while (1)
	{
		// signal(SIGQUIT, SIG_IGN);//command c игнор приходит сигнал
		// signal(SIGINT, handler);//флаг который хотим
		rez = get_str(env); // !! parser
		if (rez)
		{
			if (fill_list(rez) == -1) // !! parser
				cmd = NULL; // !! parser
			else
				cmd = (*(g_shell.cmd_start)); // это вообще очень важеая хреня не дуалять
		}
		
		// signal(SIGINT, handler_signal);
		// signal(SIGQUIT, handler_signal);	
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
