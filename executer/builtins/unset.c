/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:10:37 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/27 17:20:06 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (!args || !args[0])
	{
		printf ("unset: not enough arguments");
		return (1);
	}
	while (args[i])
	{
		if (check_name(args[i]))
		{
			printf ("unset: invalid parameter name");
			return (1);
		}
		if (env_prmtrs_exist(shell, args[i]))
			del_env(shell, args[i]);
		i++;
	}
	return (0);
}