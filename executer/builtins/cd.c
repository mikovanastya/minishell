/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:08:53 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 17:44:45 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_cd(void)
{
	char	*home;

	home = NULL;
	if (!env_prmtrs_exist(home))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	else
		home = get_env_value("HOME");
	return (0);
}

int	builtin_cd(void)
{
	char	cwd[PATH_MAX];

	if (!g_shell.cmd_start->argv[1])
		if (check_cd() == 1)
			return (1);
	getcwd(cwd, sizeof(cwd));
	if (chdir(g_shell.cmd_start->argv[1]) == -1)
	{
		if (g_shell.cmd_start->argv[0] == '\0')
			return (1);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(*g_shell.cmd_start->argv, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	set_env("OLDPWD", cwd);
	getcwd(cwd, sizeof(cwd));
	set_env("PWD", cwd);
	return (0);
}
