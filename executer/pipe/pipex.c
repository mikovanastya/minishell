/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:17:01 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/15 18:05:58 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_free_str(char **s)
{
	if (*s != NULL)
	{
		free(*s);
	}
	*s = NULL;
	return (0);
}

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

void	*ft_free_str_arr(char ***arr)
{
	int	i;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	i = 0;
	if ((*arr) != NULL)
	{
		while ((*arr)[i] != NULL)
		{
			if ((*arr)[i] != NULL)
			{
				free((*arr)[i]);
				(*arr)[i] = NULL;
			}
			i++;
		}
		if (*arr != NULL)
			free(*arr);
		*arr = NULL;
	}
	return (NULL);
}

int execute_execve(t_cmd *cmd, t_shell *shell)
{
	char	**env;
	char	*paths;
	char	**path_arr;

	paths = get_env_value(shell, "PATH");
	path_arr = ft_split(paths, ':');
	printf ("[%d][%d]_%s_%s_\n", cmd->fd[0], cmd->fd[1], cmd->argv[0], cmd->argv[1]);
	if ((ft_strlen(cmd->argv[0]) > 2)
		&& (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.'))
	{
		execve(cmd->argv[0], cmd->argv, shell->envp);//весь путь
		return (0);
	}
	else
	{
		execute_execve_without_path(cmd, shell->envp, path_arr);// без пути
	}
	ft_free_str(&paths);
	ft_free_str_arr(&path_arr);
	printf("my_shell: %s: command not found\n", cmd->argv[0]);
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

int	start_cmd_fork(t_cmd *cmd, t_shell *shell)// выполнение некоторых команд
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

void	pipex(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = *shell->cmd_start;
	if (nofork(cmd->argv[0]))
	{
		printf("NOFORK");
		start_cmd_fork(cmd, shell);
		return ;
	}
	else
	{
		printf ("pipex\n");
		while (cmd)
		{
			// printf("%s\n", cmd->argv[0]);
			create_pipe(shell, cmd);
			cmd = cmd->next;
		}
	}
}

void	set_last_status(t_shell *shell, t_cmd *cmd, int status)
{
	// printf("__%d___", status);
	if (WIFEXITED(status))
		set_env(shell, "?", ft_itoa(WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
		set_env(shell, "?", ft_itoa(WTERMSIG(status) + 128));
	set_env(shell, "_", cmd->argv[0]);// argv[0] ?????
}
