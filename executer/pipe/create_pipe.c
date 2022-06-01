/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/31 20:19:19 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipe(t_shell *shell, t_cmd *cmd)
{
	if (cmd->prev || cmd->next)
	{
		if (pipe(cmd->fd) == -1)//проверяем вывод
			printf("error"); //exit ulimit -f
	}
	cmd->pid = fork();// создаем дочерний процесс
	if (cmd->pid < 0)// если пид меньше нуля, значит процесс не создался
		return (1);//exit printf
	if (cmd->pid == 0)
	{
		if (cmd->next)
		{
			if (dup2(cmd->fd[1], 1) < 0 )//скопировать один fd в другой
				return (1);// если не создался все плохо если не скопировался
		}
		if (cmd->prev)
		{
			if (dup2(cmd->fd[0], 0) < 0 )//скопировать один fd в другой
				return (1);// если не создался все плохо если не скопировался
		}
		execute_execve(cmd, shell);
		//выполнение функций cmd 
		builtins(cmd->argv, shell);//временно
		exit(0);
	}
	else
	{
		waitpid(cmd->pid, cmd->exit_status, 0);
		if (cmd->prev || cmd->next)
			close(cmd->fd[1]);
		if (!cmd->next)
			close(cmd->fd[0]);
		if (cmd->prev)
			close(cmd->prev->fd[0]);
	}
	return (0);
}
