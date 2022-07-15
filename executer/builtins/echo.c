/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:24:43 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/15 21:13:58 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_n_flag(char *argv, int *flag)
{
	if (*argv++ == '-')
	{
		if (*argv == 'n')
		{
			while (*argv != '\0')
			{
				if (*argv != 'n')
					return (false);
				argv++;
			}
			*flag = 1;
			return (true);
		}
	}
	return (false);
}

int	builtin_echo(int fd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (ft_strcmp("$?", g_shell.cmd_start->argv[i]))
		printf("%d\n", g_shell.cmd_start->exit_status);
	while (g_shell.cmd_start->argv[i] != NULL && check_n_flag(g_shell.cmd_start->argv[i], &flag) == true)
		i++;
	while (g_shell.cmd_start->argv[i] != NULL)
	{
		ft_putstr_fd(g_shell.cmd_start->argv[i], fd);
		if (g_shell.cmd_start->argv[++i] != NULL)
			ft_putstr_fd(" ", fd);
	}
	if (flag != 1)
		ft_putstr_fd("\n", fd);
	return (0);
}
