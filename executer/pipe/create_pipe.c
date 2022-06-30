/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/30 21:38:54 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipe(t_shell *shell, t_cmd *cmd)
{
	printf("create_pipe: cmd: %s\n", cmd->argv[0]);
	if (cmd->prev || cmd->next)
	{
		if (pipe(cmd->fd) == -1)//проверяем вывод
			printf("error"); //exit ulimit -f
		// printf("fd [%d][%d]\n", cmd->fd[0], cmd->fd[1]);
	}
	// write(2, "10", 2);
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		printf("error");
		return (1);
	}
	
	// write(2, "11", 2);
	if (cmd->pid == 0)
	{
		// write(2, "D4", 2);
		if (cmd->next)
		{
			if (dup2(cmd->fd[1], 1) < 0)
				return (1);
			close(cmd->fd[1]);
		}
		if (cmd->prev)
		{
			if (dup2(cmd->prev->fd[0], 0) < 0)
				return (1);
			close(cmd->prev->fd[0]);
		}
		// check_redirection(cmd, 0);
		if (builtins(cmd->argv, shell))
			return (0);
		execute_execve(cmd, shell);
		// free(shell);
		// exit(0);///////

	}

	return (0);
}
