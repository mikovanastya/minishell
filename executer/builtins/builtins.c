/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:12 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 17:48:49 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins()
{
	int	i;

	i = 1;
	if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "exit", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		i = 1;
	if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "echo", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		builtin_echo(1);
	else if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "pwd", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		builtin_pwd();
	else if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "env", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		builtin_env();
	else if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "export", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		builtin_export();
	else if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "unset", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		builtin_unset();
	else if (!ft_strncmp((*(g_shell.cmd_start))->argv[0], "cd", ft_strlen((*(g_shell.cmd_start))->argv[0])))
		builtin_cd();
	else
		i = 0;
	return (i);
}
