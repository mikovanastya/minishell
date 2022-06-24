/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/23 19:36:42 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> 
#include <readline/readline.h> 
#include <readline/history.h>
#include <readline/readline.h>

static void	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("Myshell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**rez;
	t_shell	shell;
	t_cmd	*cmd;

	if (argc != 1)
	 	ft_error(argv[0], EINVAL);
	while (1)
	{
		init_env(env, &shell);
		cmd = malloc(sizeof(t_cmd));
		shell.cmd_start = &cmd;
		cmd->argv = get_str(env); // !!
		int i = 0;
		while (cmd->argv[i])
		{
			printf("Cmd %d:[%s]\n",i, cmd->argv[i]);
			i++;
		}
		signal(SIGINT, handler_signal);
		signal(SIGQUIT, handler_signal);
		// pipex(&shell);
		builtins(cmd->argv, &shell);
		free_array(cmd->argv);
	}
	return (0);
}
