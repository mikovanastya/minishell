/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:12 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/15 21:06:10 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit()
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

int	builtins()
{
	int	i;

	i = 1;
	// if (ft_strncmp(g_shell.cmd_start->argv[0], "exit", ft_strlen(g_shell.cmd_start->argv[0])))
	// 	ft_exit();
	if (!ft_strncmp(g_shell.cmd_start->argv[0], "echo", ft_strlen(g_shell.cmd_start->argv[0])))
	{
		builtin_echo(1);
		exit(0);
	}
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "pwd", ft_strlen(g_shell.cmd_start->argv[0]))){
		builtin_pwd();
		exit(0);
	}
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "env", ft_strlen(g_shell.cmd_start->argv[0])))
	{
		builtin_env();
		exit(0);
	}
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "export", ft_strlen(g_shell.cmd_start->argv[0])))
	{
		builtin_export();
		exit(0);
	}
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "unset", ft_strlen(g_shell.cmd_start->argv[0])))
	{
		builtin_unset();
		exit(0);
	}
	else if (!ft_strncmp(g_shell.cmd_start->argv[0], "cd", ft_strlen(g_shell.cmd_start->argv[0])))
	{
		builtin_cd();
		exit(0);
	}
	else
		i = 0;
	return (i);
}
