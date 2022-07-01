/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:45:35 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 17:48:33 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**after_quotes(char **tmpmass)
{
	int		i;
	int		j;
	int		k;
	char	**after;

	after = malloc(sizeof(char *) * (g_shell.len + 1));
	if (!after)
		return (NULL);
	i = -1;
	while (tmpmass[++i])
	{
		k = 0;
		after[i] = malloc(sizeof(char) * (ft_strlen(tmpmass[i])
					- ft_sym_export(tmpmass[i]) + 1));
		if (!after[i])
			return (NULL);
		j = ft_sym_export(tmpmass[i]);//записываем сколько симыволов кол-во символов 
		while (tmpmass[i][++j] != '\0')// перешагиваем равно ++j
			after[i][k++] = tmpmass[i][j];
		after[i][k] = '\0';
	}
	after[i] = NULL;
	return (after);
}

char	**before_quotes(char **tmpmass)
{
	int		i;
	int		j;
	char	**before;

	before = malloc(sizeof(char *) * (g_shell.len + 1));
	if (!before)
		return (NULL);
	i = -1;
	while (tmpmass[++i])
	{
		j = -1;
		before[i] = malloc(sizeof(char) * (ft_sym_export(tmpmass[i]) + 1));
		if (!before[i])
			return (NULL);
		if (!ft_strchr(tmpmass[i], '='))
			before[i] = ft_strdup(tmpmass[i]);
		else
		{
			while (tmpmass[i][++j] != '=')
				before[i][j] = tmpmass[i][j];
			before[i][j] = '\0';
		}
	}
	before[i] = NULL;
	return (before);
}
