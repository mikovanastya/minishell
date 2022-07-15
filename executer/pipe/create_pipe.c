/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/15 21:26:02 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipe()
{
	if (!ft_strncmp(g_shell.cmd_start->argv[0], "exit", ft_strlen(g_shell.cmd_start->argv[0])))
	{
		ms_check_exit_arg(g_shell.cmd_start->argv);
		ft_exit2();
	}
	if (pipe(g_shell.cmd_start->fd) == -1)
		printf("error");
	g_shell.cmd_start->pid = fork();
	if (g_shell.cmd_start->pid)
		sig_sig_signal();
	if (g_shell.cmd_start->pid < 0)
	{
		printf("error");
		return (1);
	}
	if (g_shell.cmd_start->pid == 0)
	{
		if (g_shell.cmd_start->next)
		{
			if (dup2(g_shell.cmd_start->fd[1], 1) < 0)
				return (1);
			close(g_shell.cmd_start->fd[1]);
		}
		if (g_shell.cmd_start->prev)
		{
			if (dup2(g_shell.cmd_start->prev->fd[0], 0) < 0)
				return (1);
			close(g_shell.cmd_start->prev->fd[0]);
		}
		check_redirection(0);
		close(g_shell.cmd_start->fd[0]);
		close(g_shell.cmd_start->fd[1]);
		if (builtins())
			return (0);
		execute_execve();
	}
	return (0);
}
