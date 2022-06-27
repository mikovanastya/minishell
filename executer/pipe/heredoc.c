/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:49:46 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/27 20:37:22 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	make_heredocs(t_cmd *cmd, t_shell *shell)
{
	char **redir;
	while (cmd != NULL)
	{
		if (check_heredoc(redir, cmd->fd[0], cmd, shell) == 1)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	check_heredoc(char **redir, int stdin_fd, t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
		{
			if (redir_heredoc(redir[i + 1], stdin_fd, cmd, shell) == 1)
				return (1);
		}
		i++;
	}
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

void	heredoc(char *iter, int *fd, t_cmd *cmd, t_shell *shell)
{
	char	*line;

	// signal(SIGINT, stop_heredoc);
	line = readline("heredoc > ");
	while (line)
	{
		if (ft_strcmp(line, iter) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("heredoc > ");
	}
	free(line);
	exit(EXIT_SUCCESS);
}

int	redir_heredoc(char *iter, int fd, t_cmd *cmd, t_shell *shell)
{
	int		new_fd[2];
	pid_t	pid;
	int		status;

	//signal(SIGINT, nothing);
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(iter, new_fd, cmd, shell);
	wait(&status);
	//signal
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	// if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	// 	return (1);
	return (0);
}
