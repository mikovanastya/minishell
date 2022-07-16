/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:07:32 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 16:27:08 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_file(char *name, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(name, O_RDONLY, 0777);
	else if (i == 3)
		file = open(name, O_RDONLY | O_CREAT | O_APPEND, 0777);
	if (file == -1)
	{
		if (access(name, F_OK) == 0)
			printf("minishell: %s Is a directory\n", name);
		else
			printf("minishell: : %s\n", name);
		if (quit == 0)
			exit(1);
	}
	if (i == 3)
		close(file);
	return (file);
}

void	fd_name(int *quit, int *fd_0, int *fd_1, int *i)
{
	if (!g_shell.cmd_start->file_name[(*i) + 1])
	{
		if (ft_strcmp(g_shell.cmd_start->redir, ">>") == 0)
			*fd_1 = open_file(g_shell.cmd_start->file_name[*i], 0, *quit);
		else if (ft_strcmp(g_shell.cmd_start->redir, "<") == 0)
			*fd_0 = open_file(g_shell.cmd_start->file_name[*i], 2, *quit);
		else if (ft_strcmp(g_shell.cmd_start->redir, ">") == 0)
			*fd_1 = open_file(g_shell.cmd_start->file_name[*i], 1, *quit);
	}
	else
		open_file(g_shell.cmd_start->file_name[*i], 3, *quit);
	(*i)++;
}

int	check_redirection(int quit)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	if (g_shell.cmd_start->file_name)
		while (g_shell.cmd_start->file_name[i])
			fd_name(&quit, &(fd[0]), &(fd[1]), &i);
	else if (g_shell.cmd_start->redir)
		if (ft_strcmp(g_shell.cmd_start->redir, "<<") == 0)
			fd[0] = open_file(".heredoc", 2, quit);
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}
