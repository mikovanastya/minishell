/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:12 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/28 16:23:59 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	builtins(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	// if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
	// 	i = 1;
	if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
		builtin_echo(argv, 1);
	else if	(!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		builtin_pwd();
	else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
		builtin_env(shell);
	else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
		builtin_export(&argv[0], shell);
	else if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
		builtin_unset(&argv[0], shell);// вот насчет этого я хз 
	else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
		builtin_cd(&argv[0], shell);
	else
		i = 0;
	return (i);
}
