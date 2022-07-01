/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 18:56:17 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipe()
{
	if ((*(g_shell.cmd_start))->prev || (*(g_shell.cmd_start))->next)
	{
		if (pipe((*(g_shell.cmd_start))->fd) == -1)//проверяем вывод
			printf("error"); //exit ulimit -f
	}
	// write(2, "10", 2);
	(*(g_shell.cmd_start))->pid = fork();
	if ((*(g_shell.cmd_start))->pid < 0)
	{
		printf("error");
		return (1);
	}
	
	// write(2, "11", 2);
	if ((*(g_shell.cmd_start))->pid == 0)
	{
		// write(2, "D4", 2);
		if ((*(g_shell.cmd_start))->next)
		{
			if (dup2((*(g_shell.cmd_start))->fd[1], 1) < 0)
				return (1);
			close((*(g_shell.cmd_start))->fd[1]);
		}
		if ((*(g_shell.cmd_start))->prev)
		{
			if (dup2((*(g_shell.cmd_start))->prev->fd[0], 0) < 0)
				return (1);
			close((*(g_shell.cmd_start))->prev->fd[0]);
		}
		// check_redirection(cmd, 0);
		if (builtins((*(g_shell.cmd_start))->argv))
			return (0);
		execute_execve((*(g_shell.cmd_start)));
		free(*g_shell.cmd_start);
		// exit(0);///////

	}

	return (0);
}
