/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:45 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 12:14:47 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_env(char **prmtrs)
{
	int	i;

	i = 0;
	while (prmtrs[i])
		i++;
	g_shell.envp = malloc(sizeof(char *) * (i + 1));
	g_shell.len = i;
	i = 0;
	while (prmtrs[i])
	{
		g_shell.envp[i] = ft_strdup(prmtrs[i]);
		i++;
	}
	g_shell.envp[i] = NULL;
	return ;
}
