/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:08:53 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/24 17:44:04 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_cd(char **args, t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	*home;

	if (!args[1])// параметр помле cd
	{
		if (!env_prmtrs_exist(shell, home))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		else
			home = get_env_value(shell, "HOME");
	}
	getcwd(cwd, sizeof(cwd));//копируем то что в HOME путь в строку куда указывает cwd
	if (chdir(*args) == -1)
	{
		if (args[0] == '\0')
			return (1);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(*args, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	set_env(shell, "OLDPWD", cwd);//предыдущий каталог
	getcwd(cwd, sizeof(cwd));
	set_env(shell, "PWD", cwd);//текущий
	return (0);
}
