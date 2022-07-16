/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 19:17:19 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> 
#include <readline/readline.h> 
#include <readline/history.h>
#include <readline/readline.h>

/*
**	всё вместе:
*/

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*t;

	if (cmd)
		t = cmd->next;
	while (cmd)
	{
		ft_free(cmd->argv);
		ft_free(cmd->file_name);
		if (cmd->redir)	
			free(cmd->redir);
		if (cmd)
			free(cmd);
		cmd = t;
		if (cmd)
			t = cmd->next;
	}
}

void	ft_list(char	*rez, t_cmd	**cmd)
{
	if (rez)
	{
		if (fill_list(rez) == -1)
			*cmd = NULL;
		else
			*cmd = g_shell.cmd_start;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*rez;
	t_cmd	*cmd;

	if (argc != 1)
		ft_error(argv[0], EINVAL);
	cmd = NULL;
	init_env(env);
	while (1)
	{
		rez = get_str();
		ft_list(rez, &cmd);
		signal(SIGINT, handler_signal);
		signal(SIGQUIT, handler_signal);
		if (cmd)
			if (*(cmd->argv))
				pipex();
		free_cmd(cmd);
		free(rez);
	}
	return (0);
}
