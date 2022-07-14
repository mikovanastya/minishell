/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:10:37 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 20:38:14 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_unset()
{
	int	i;

	i = 0;
	if (!(*(g_shell.cmd_start))->argv || !(*(g_shell.cmd_start))->argv[0])
	{
		printf ("unset: not enough arguments");
		return (1);
	}
	while ((*(g_shell.cmd_start))->argv[i])
	{
		if (check_name((*(g_shell.cmd_start))->argv[i]))
		{
			printf ("unset: invalid parameter name");
			return (1);
		}
		if (env_prmtrs_exist((*(g_shell.cmd_start))->argv[i]))
			del_env((*(g_shell.cmd_start))->argv[i]);
		i++;
	}
	return (0);
}
