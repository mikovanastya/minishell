/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:07:32 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/20 22:05:27 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_file(char *argv, int i, int quit)
{
	int	file;

	printf("RED < 1\n");
	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		if (access(argv, F_OK) == 0)
			printf("minishell: %s Is a directory\n", argv);
		else
			printf("minishell: no such file or directory: %s\n", argv);
		if (quit == 0)
			exit(1);
	}
	return (file);
}

int	check_redirection(t_cmd *cmd, int quit)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	printf("TYOPE = %s\n", cmd->file[0]);
	while (cmd->file && cmd->file[i])
	{
		if (ft_strcmp(cmd->file[i], "<") == 0)
			fd[0] = open_file(cmd->file[++i], 2, quit);
		else if (ft_strcmp(cmd->file[i], ">") == 0)
			fd[1] = open_file(cmd->file[++i], 1, quit);
		else if (ft_strcmp(cmd->file[i], ">>") == 0)
			fd[1] = open_file(cmd->file[++i], 0, quit);
		else if (ft_strcmp(cmd->file[i], "<<") == 0)
			dup2(cmd->fd[0], STDIN_FILENO);
		i++;
	}
	printf("AFTER OPENING FILE [%d][%d]\n", fd[0], fd[1]);
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}
