/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:08:53 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 17:47:54 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_cd(char **args)
{
	char	cwd[PATH_MAX];
	char	*home;

	home = NULL;
	if (!args[1])// параметр помле cd
	{
		if (!env_prmtrs_exist(home))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		else
			home = get_env_value("HOME");
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
	set_env("OLDPWD", cwd);//предыдущий каталог
	getcwd(cwd, sizeof(cwd));
	set_env("PWD", cwd);//текущий
	return (0);
}
