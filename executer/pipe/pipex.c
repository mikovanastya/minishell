/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:17:01 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 17:49:13 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_execve(void)
{
	char	*paths;
	char	**path_arr;

	paths = get_env_value("PATH");
	path_arr = ft_split(paths, ':');
	if ((ft_strlen(g_shell.cmd_start->argv[0]) > 2)
		&& (g_shell.cmd_start->argv[0][0] == '/'
		|| g_shell.cmd_start->argv[0][0] == '.'))
		execve(g_shell.cmd_start->argv[0],
			g_shell.cmd_start->argv, g_shell.envp);
	else
		execute_execve_without_path(path_arr);
	printf("minishell: %s: command not found\n", g_shell.cmd_start->argv[0]);
	g_shell.cmd_start->exit_status = 127;
	exit(g_shell.cmd_start->exit_status);
	return (0);
}

int	child_process(void)
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
	return (2);
}

int	create_pipe(void)
{
	int	child;

	if (!ft_strncmp(g_shell.cmd_start->argv[0], "exit", 4))
		ft_exit();
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
		child = child_process();
		if (child == 0 || child == 1)
			return (child);
	}
	return (0);
}

void	pipex(void)
{
	if (nofork(g_shell.cmd_start->argv[0]))
	{
		start_cmd_nofork();
		return ;
	}
	if (g_shell.cmd_start && g_shell.cmd_start->argv)
	{
		while (g_shell.cmd_start)
		{
			create_pipe();
			waitpid(g_shell.cmd_start->pid, &g_shell.cmd_start->exit_status, 0);
			set_last_status(g_shell.cmd_start->exit_status);
			if (g_shell.cmd_start->prev || g_shell.cmd_start->next)
			{
				close(g_shell.cmd_start->fd[1]);
				if (!g_shell.cmd_start->next)
					close(g_shell.cmd_start->fd[0]);
			}
			if (g_shell.cmd_start->prev)
				close(g_shell.cmd_start->prev->fd[0]);
			g_shell.cmd_start = g_shell.cmd_start->next;
		}
	}
}
