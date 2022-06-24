/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/24 18:40:47 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	create_pipe(t_shell *shell, t_cmd *cmd)
{
	if (cmd->prev || cmd->next)
	{
		if (pipe(cmd->fd) == -1)//проверяем вывод
			printf("error"); //exit ulimit -f
		// printf("fd [%d][%d]\n", cmd->fd[0], cmd->fd[1]);
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
			if (dup2(cmd->prev->fd[0], 0) < 0 )//скопировать один fd в другой
				return (1);// если не создался все плохо если не скопировался
		}
		check_redirection(cmd, 0);
		//make_heredocs(cmd, shell);
		if (builtins(cmd->argv, shell))
			return (0);
		execute_execve(cmd, shell);
		free(shell);
		//exit(0);
	}
	else
	{
		waitpid(cmd->pid, &cmd->exit_status, 0);//жду дочерний процесс
		//write(1, "Mama\n", 5);
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

// void	check_shlvl(t_shell *shell)
// {
// 	char	*tmp;
// 	int		num;
// 	char	*digit;

// 	tmp = get_env_value("SHLVL=", shell);
// 	num = ft_atoi(tmp) + 1;
// 	free(tmp);
// 	digit = ft_itoa(num);
// 	tmp = ft_strjoin("export SHELVL=", digit);
// 	free(digit);
// 	export(tmp, shell);
// 	free(tmp);
// }