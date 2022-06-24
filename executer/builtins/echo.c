/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:24:43 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/24 17:44:23 by rtwitch          ###   ########.fr       */
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

int	builtin_echo(char **argv, int fd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (argv[i] != NULL && check_n_flag(argv[i], &flag) == true)
		i++;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[++i] != NULL)
			ft_putstr_fd(" ", fd);
	}
	if (flag != 1)
		ft_putstr_fd("\n", fd);
	return (0);
}
