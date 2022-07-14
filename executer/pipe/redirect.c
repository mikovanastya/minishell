/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:07:32 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 18:16:43 by rtwitch          ###   ########.fr       */
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
	// else if (i == 3)
	// 	file = open(name, O_RDONLY |
	if (file == -1)
	{
		if (access(name, F_OK) == 0)
			printf("minishell: %s Is a directory\n", name);
		else
			printf("minishell: : %s\n", name);
		if (quit == 0)
			exit(1);
	}
	// printf("name = %s", name);
	return (file);
}

int	check_redirection(int quit)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	// if (!(*(g_shell.cmd_start))->redir)
	// 	return (0);
	// printf("haha %s\n", (*(g_shell.cmd_start))->file_name[i]);
	if (g_shell.cmd_start->file_name)
	while (g_shell.cmd_start->file_name[i])
	{
		if (ft_strcmp(g_shell.cmd_start->redir, "<") == 0)
			fd[0] = open_file(g_shell.cmd_start->file_name[i], 2, quit);
		else if (ft_strcmp(g_shell.cmd_start->redir, ">") == 0)
			fd[1] = open_file(g_shell.cmd_start->file_name[i], 1, quit);
		else if (ft_strcmp(g_shell.cmd_start->redir, ">>") == 0)
			fd[1] = open_file(g_shell.cmd_start->file_name[i], 0, quit);
		// else if (ft_strcmp(((*(g_shell.cmd_start))->redir[i]), "<<") == 0)
		// 	dup2((*(g_shell.cmd_start))->fd[0], STDIN_FILENO);
		// printf("haha %s, %d, %d", *((*(g_shell.cmd_start))->redir), fd[1], fd[0]);
		i++;
	}
	// printf("AFTER OPENING FILE [%d][%d]\n", fd[0], fd[1]);
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}
