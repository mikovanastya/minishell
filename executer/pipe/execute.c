/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:52 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 18:47:05 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nofork(char *cmd)
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

int	start_cmd_nofork(void)
{
	int	status;

	if (!(g_shell.cmd_start->argv))
		return (1);
	status = 0;
	if (ft_strncmp(*(g_shell.cmd_start->argv), "cd", 2) == 0)
		status = builtin_cd();
	else if (ft_strncmp(*g_shell.cmd_start->argv, "unset", 5) == 0)
		status = builtin_unset();
	else if (ft_strncmp(*g_shell.cmd_start->argv, "export", 6) == 0)
		status = builtin_export();
	set_env("_", *g_shell.cmd_start->argv);
	set_env("?", ft_itoa(status));
	return (status);
}

int	execute_execve_without_path(char **path_arr)
{
	char	*tmp;
	char	*final;

	while (*path_arr != NULL)
	{
		tmp = ft_strjoin(*path_arr, "/");
		final = ft_strjoin(tmp, g_shell.cmd_start->argv[0]);
		if (access(final, F_OK) == 0)
			break ;
		path_arr++;
		if (*tmp)
			free(tmp);
	}
	if (*path_arr == NULL)
		return (0);
	else
		execve(final, g_shell.cmd_start->argv, g_shell.envp);
	if (*final)
			free(final);
	return (0);
}

void	set_last_status(int status)
{
	char	*stat;

	stat = NULL;
	if (WIFEXITED(status))
		stat = ft_itoa(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		stat = ft_itoa(WTERMSIG(status) + 128);
	set_env("?", stat);
	// if (*stat)
	// 	free(stat);
	// set_env("_", g_shell.cmd_start->argv[0]);
}
