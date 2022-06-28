/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:17:01 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/28 19:04:04 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_count_cmd(char ***cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	return (count);
}

int	execute_execve_without_path(t_cmd *cmd,
										char **env, char **path_arr)
{
	char	*tmp;
	char	*final;

	while (*path_arr != NULL)
	{
		tmp = ft_strjoin(*path_arr, "/");
		final = ft_strjoin(tmp, cmd->argv[0]);
		execve(final, cmd->argv, env);
		path_arr++;
		ft_free_str(&tmp);
		ft_free_str(&final);
	}
	return (0);
}

int execute_execve(t_cmd *cmd, t_shell *shell)// выполняет команды из bin///
{
	char	**env;
	char	*paths;
	char	**path_arr;

	//printf ("[%d][%d]_%s_%s_\n", cmd->fd[0], cmd->fd[1], cmd->argv[0], cmd->argv[1]);
	paths = get_env_value(shell, "PATH");
	path_arr = ft_split(paths, ':');
	if ((ft_strlen(cmd->argv[0]) > 2)
		&& (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.'))
	{
		execve(cmd->argv[0], cmd->argv, shell->envp);//весь путь
	}
	else
	{
		execute_execve_without_path(cmd, shell->envp, path_arr);// без пути
	}
	ft_free_str(&paths);
	// ft_free_str_arr(&env);
	ft_free_str_arr(&path_arr);
	printf("minishell: %s: command not found\n", cmd->argv[0]);
	cmd->exit_status = 127;
	exit(cmd->exit_status);
	return (0);
}

int	nofork(char *cmd)// эти команды не могут выполняться в пайпе тем самым с форк
{
	if (!cmd)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (1);
	return (0);
}

int	start_cmd_nofork(t_cmd *cmd, t_shell *shell)// выполнение некоторых команд
{
	int	status;//статус выхода

	if (!cmd->argv)
		return (1);
	status = 0;
	if (ft_strncmp(*cmd->argv, "cd", ft_strlen("cd")) == 0)
		status = builtin_cd(cmd->argv, shell);
	else if (ft_strncmp(*cmd->argv, "unset", ft_strlen("unset")) == 0)
		status = builtin_unset(cmd->argv, shell);
	else if (ft_strncmp(*cmd->argv, "export", ft_strlen("export")) == 0)
		status = builtin_export(cmd->argv, shell);//
	set_env(shell, "_", *cmd->argv);// я пока хз, но так нужно;
	set_env(shell, "?", ft_itoa(status));// статус выхода самого последнего пайпа, вроде так, хз
	return (status);
}

int	check_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0
		||ft_strcmp(arg[0], "cd") == 0
		||ft_strcmp(arg[0], "pwd") == 0
		||ft_strcmp(arg[0], "export") == 0
		||ft_strcmp(arg[0], "unset") == 0
		||ft_strcmp(arg[0], "env") == 0
		||ft_strcmp(arg[0], "exit") == 0)
		return (0);
	else
		return (1);
}


int	ft_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (cmd && cmd->next == NULL && cmd->argv[0] != NULL)
	{
		if (cmd->argv && check_builtins(cmd->argv) == 1)
			return (0);
		if (check_redirection(cmd, 1) == 1)
			return (1);
		if (builtins(cmd->argv, shell) == 0)
		{
			dup2(saved_stdin, 0);
			close(saved_stdin);
			dup2(saved_stdout, 1);
			close(saved_stdout);
			return (1);
		}
	}
	return (0);
}

void	init_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		pipe(cmd->fd);
		cmd = cmd->next;
	}
}

void	pipex(t_cmd *cmd, t_shell *shell)
{
	// cmd = *shell->cmd_start;
	//init_pipe(first);
	if (nofork(cmd->argv[0]))
	{
		start_cmd_nofork(cmd, shell);
		return ;
	}
	// if (make_heredocs(cmd, shell) == 1 || ft_builtin(cmd, shell) == 1)
	// 	return ;
	if (cmd && cmd->argv)
	{
		while (cmd)
		{
			create_pipe(shell, cmd);
			cmd = cmd->next;
		}
	}
}

void	set_last_status(t_shell *shell, t_cmd *cmd, int status)
{
	if (WIFEXITED(status))
		set_env(shell, "?", ft_itoa(WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
		set_env(shell, "?", ft_itoa(WTERMSIG(status) + 128));
	set_env(shell, "_", cmd->argv[0]);
}
		// printf("fd [%d][%d]\n", cmd->fd[0], cmd->fd[1]);