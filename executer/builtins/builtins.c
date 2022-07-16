/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:12 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 16:12:09 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(void)
{
	int	i;

	i = 0;
	if (!(g_shell.cmd_start->argv[1] && g_shell.cmd_start->argv[2]))
		printf("exit\n");
	if (g_shell.cmd_start->argv[1] && g_shell.cmd_start->argv[2])
		printf("error\n");
	if (g_shell.cmd_start->argv[1])
	{
		while (ft_isdigit(g_shell.cmd_start->argv[1][i]))
			i++;
		if ((size_t)i != ft_strlen(g_shell.cmd_start->argv[1]))
			printf("error\n");
	}
	if (!(g_shell.cmd_start->argv[1] && g_shell.cmd_start->argv[2]))
	{
		if (!g_shell.cmd_start->argv[1])
			exit(0);
		else if ((size_t)i != ft_strlen(g_shell.cmd_start->argv[1]))
			exit(255);
		else
			exit(ft_atoi(g_shell.cmd_start->argv[1]) % 256);
	}
}

int	builtins(void)
{
	int	i;

	i = 1;
	if (!ft_strncmp(g_shell.cmd_start->argv[0], "echo", 4))
		exit(builtin_echo(1));
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "pwd", 3))
		exit(builtin_pwd());
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "env", 3))
		exit(builtin_env());
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "export", 6))
		exit(builtin_export());
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "unset", 5))
		exit(builtin_unset());
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "cd", 2))
		exit(builtin_cd());
	else
		i = 0;
	return (i);
}
