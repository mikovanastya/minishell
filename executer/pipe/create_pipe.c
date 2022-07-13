/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 20:30:34 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipe()
{
	if ((*(g_shell.cmd_start))->prev || (*(g_shell.cmd_start))->next)
	{
		if (pipe((*(g_shell.cmd_start))->fd) == -1)
			printf("error");
	}
	if (make_heredocs(*(g_shell.cmd_start)) == 1 || ft_builtin(*(g_shell.cmd_start)) == 1)
		return (0);
	// if (make_heredocs(*(g_shell.cmd_start)) == 1)
	// 	return (0);
	(*(g_shell.cmd_start))->pid = fork();
	// if ((*(g_shell.cmd_start))->pid)
	// 	sig_sig_signal();
	if ((*(g_shell.cmd_start))->pid < 0)
	{
		printf("error");
		return (1);
	}
	if ((*(g_shell.cmd_start))->pid == 0)
	{
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
		// make_heredocs();
		check_redirection(0);
		close((*(g_shell.cmd_start))->fd[0]);
		close((*(g_shell.cmd_start))->fd[1]);
		if (builtins((*(g_shell.cmd_start))->argv))
			return (0);
		execute_execve((*(g_shell.cmd_start)));
		free(g_shell.cmd_start);
		// exit(0);///////
	}
	return (0);
}
