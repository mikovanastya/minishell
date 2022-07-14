/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:49:46 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 20:57:17 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	make_heredocs()
{
	t_cmd *cmd;
	cmd = *(g_shell.cmd_start);
	while (cmd != NULL)
	{
		if (check_heredoc() == 1)
			return (1);
		(cmd) = cmd->next;
	}
	return (0);
}

int	check_heredoc()
{
	int	i;

	i = 0;
	// if (!(*(g_shell.cmd_start))->redir)
	// 	return (0);
	while ((*(g_shell.cmd_start))->redir && (*(g_shell.cmd_start))->redir[i])
	{
		if (ft_strcmp((*(g_shell.cmd_start))->redir, "<<") == 0)
		{
			if (redir_heredoc())
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_heredoc()
{
	// int		wstatus;

	//signal(SIGINT, nothing);
	pipe((*(g_shell.cmd_start))->fd);
	(*(g_shell.cmd_start))->pid = fork();
	if ((*(g_shell.cmd_start))->pid == 0)
	{
		close((*(g_shell.cmd_start))->fd[0]);
		close((*(g_shell.cmd_start))->fd[1]);
	}
	// wait(&(*(g_shell.cmd_start))->pid);
		// heredoc(iter, new_fd);
	// wait(&status);
	//signal
	dup2((*(g_shell.cmd_start))->fd[0], STDIN_FILENO);
	close((*(g_shell.cmd_start))->fd[1]);
	close((*(g_shell.cmd_start))->fd[0]);
	// if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	// 	return (1);
	return (0);
}

void	nothing(int signal)
{
	(void)signal;
}

void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(130);
}
// void	heredoc(char *iter, int *fd)
// {
// 	char	*line;

// 	// signal(SIGINT, stop_heredoc);
// 	line = readline("heredoc > ");
// 	while (line)
// 	{
// 		if (ft_strcmp(line, iter) == 0)
// 		{
// 			close(fd[0]);
// 			close(fd[1]);
// 			break ;
// 		}
// 		ft_putendl_fd(line, fd[1]);
// 		free(line);
// 		line = readline("heredoc > ");
// 	}
// 	free(line);
// 	exit(EXIT_SUCCESS);
// }
