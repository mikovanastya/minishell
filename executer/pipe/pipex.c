/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:17:01 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 18:59:18 by rtwitch          ###   ########.fr       */
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

int	execute_execve_without_path(char **env, char **path_arr)
{
	char	*tmp;
	char	*final;

	while (*path_arr != NULL)
	{
		tmp = ft_strjoin(*path_arr, "/");
		final = ft_strjoin(tmp, (*(g_shell.cmd_start))->argv[0]);
		if (access(final, F_OK) == 0)
		{
			break;
		}
		path_arr++;
		ft_free_str(&tmp);
		ft_free_str(&final);
	}
	if (*path_arr == NULL)
	{
		// not found
	}
	else
	{
		execve(final, (*(g_shell.cmd_start))->argv, env);
	}
	return (0);
}


int execute_execve()// выполняет команды из bin///
{
	char	*paths;
	char	**path_arr;

	paths = get_env_value("PATH");
	path_arr = ft_split(paths, ':');
	if ((ft_strlen((*(g_shell.cmd_start))->argv[0]) > 2)
		&& ((*(g_shell.cmd_start))->argv[0][0] == '/' || (*(g_shell.cmd_start))->argv[0][0] == '.'))
	{
		execve((*(g_shell.cmd_start))->argv[0], (*(g_shell.cmd_start))->argv, g_shell.envp);//весь путь
	}
	else
	{
		// ft_exec_without_path((*(g_shell.cmd_start)), shell->en->p, path_arr);
		execute_execve_without_path(g_shell.envp, path_arr);// без пути
	}
	// ft_free_str(&paths);
	// ft_free_str_arr(&(g_shell.envp));
	// ft_free_str_arr(&path_arr);
	printf("minishell: %s: command not found\n", (*(g_shell.cmd_start))->argv[0]);
	(*(g_shell.cmd_start))->exit_status = 127;
	exit((*(g_shell.cmd_start))->exit_status);
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

int	start_cmd_nofork()// выполнение некоторых команд
{
	int	status;//статус выхода

	if (!((*(g_shell.cmd_start))->argv))
		return (1);
	status = 0;
	if (ft_strncmp(*((*(g_shell.cmd_start))->argv), "cd", ft_strlen("cd")) == 0)
		status = builtin_cd((*(g_shell.cmd_start))->argv );
	else if (ft_strncmp(*(*(g_shell.cmd_start))->argv, "unset", ft_strlen("unset")) == 0)
		status = builtin_unset((*(g_shell.cmd_start))->argv);
	else if (ft_strncmp(*(*(g_shell.cmd_start))->argv, "export", ft_strlen("export")) == 0)
		status = builtin_export((*(g_shell.cmd_start))->argv);//
	set_env("_", *(*(g_shell.cmd_start))->argv);// я пока хз, но так нужно;
	set_env( "?", ft_itoa(status));// статус выхода самого последнего пайпа, вроде так, хз
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


int	ft_builtin(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (cmd && (*(g_shell.cmd_start))->next == NULL && (*(g_shell.cmd_start))->argv[0] != NULL)
	{
		if ((*(g_shell.cmd_start))->argv && check_builtins((*(g_shell.cmd_start))->argv) == 1)
			return (0);
		if (check_redirection( 1) == 1)
			return (1);
		if (builtins((*(g_shell.cmd_start))->argv) == 0)
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


void	pipex()
{
	t_cmd	*head;

	head = (*(g_shell.cmd_start));
	// cmd = *shell->cmd_start;
	if (nofork((*(g_shell.cmd_start))->argv[0]))
	{
		start_cmd_nofork();
		return ;
	}
	// if (make_heredocs((*(g_shell.cmd_start)), shell) == 1 || ft_builtin((*(g_shell.cmd_start)), shell) == 1)
	// 	return ;
	if ((*(g_shell.cmd_start)) && (*(g_shell.cmd_start))->argv)
	{
		while ((*(g_shell.cmd_start)))
		{
			create_pipe((*(g_shell.cmd_start)));
			waitpid((*(g_shell.cmd_start))->pid, &(*(g_shell.cmd_start))->exit_status, 0);
			set_last_status((*(g_shell.cmd_start))->exit_status);
			if ((*(g_shell.cmd_start))->prev || (*(g_shell.cmd_start))->next) {
				close((*(g_shell.cmd_start))->fd[1]);
				if (!(*(g_shell.cmd_start))->next)
					close((*(g_shell.cmd_start))->fd[0]);
			}
			if ((*(g_shell.cmd_start))->prev)
				close((*(g_shell.cmd_start))->prev->fd[0]);
			(*(g_shell.cmd_start)) = (*(g_shell.cmd_start))->next;
		}
	}

}

void	set_last_status(int status)
{
	if (WIFEXITED(status))
		set_env("?", ft_itoa(WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
		set_env("?", ft_itoa(WTERMSIG(status) + 128));
	set_env("_", (*(g_shell.cmd_start))->argv[0]);
}
		// printf("fd [%d][%d]\n", (*(g_shell.cmd_start))->fd[0], (*(g_shell.cmd_start))->fd[1]);