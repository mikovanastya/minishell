/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/15 20:02:10 by rtwitch          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*rez;
	t_cmd	*cmd;
	t_list	*tokens;
	t_cmd **ex_cmd;

	tokens = NULL;
	ex_cmd = NULL;
	//g_shell = (t_shell)malloc(sizeof(t_shell));
	if (argc != 1)
		ft_error(argv[0], EINVAL);
	cmd = NULL;
	init_env(env);
	while (1)
	{
		rez = get_str();
		if (rez)
		{
			if (fill_list(rez) == -1)
				cmd = NULL;
			else
				cmd = g_shell.cmd_start;
		}
		signal(SIGINT, handler_signal);
		signal(SIGQUIT, handler_signal);
		if (cmd)
			pipex();
		free(rez);
	}
	return (0);
}
