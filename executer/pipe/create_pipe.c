/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/28 16:58:09 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipe(t_shell *shell, t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("error");
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		if (cmd->next)
		{
			if (dup2(cmd->fd[1], 1) < 0)
				return (1);
		}
		if (cmd->prev)
		{
			if (dup2(cmd->prev->fd[0], 0) < 0)
				return (1);
		}
		// check_redirection(cmd, 0);
		// close(cmd->fd[0]);
		// close(cmd->fd[1]);
		if (builtins(cmd->argv, shell))
			return (0);
		execute_execve(cmd, shell);
		free(shell);
	}
	else
	{
		//printf("AFTER OPENING FILE [%d][%d]\n", cmd->fd[0], cmd->fd[1]);
		waitpid(cmd->pid, &cmd->exit_status, 0);
		set_last_status(shell, cmd, cmd->exit_status);
		if (cmd->prev || cmd->next)
			close(cmd->fd[1]);
		if (!cmd->next)
			close(cmd->fd[0]);
		if (cmd->prev)
			close(cmd->prev->fd[0]);
	}
	return (0);
}
