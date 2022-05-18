/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:08:53 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/17 20:09:02 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **args, t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (args == NULL)
	{
		args = get_env_value(shell->envp, "HOME");
		if (args == NULL)
		{
			printf("cd: HOME not set\n", 2);
			return (1);
		}
	}
	getcwd(cwd, sizeof(cwd));//копируем то что в HOME путь в строку куда указывает cwd
	if (chdir(args) == 0)
	{
		if (args[0] == '\0')
			return (1);
		ft_putchar_fd("cd: ", 2);
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	set_env(shell, "OLDPWD", cwd);
	getcwd(cwd, sizeof(cwd));
	set_env(shell, "PWD", cwd);
	return (0);
}


