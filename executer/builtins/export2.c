/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:20:53 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 16:06:31 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_mass(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	ft_sym_export(char *str)
{
	int	j;

	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	return (j);
}

void	ft_free(char **mass)
{
	int	sizemass;

	sizemass = 0;
	if (!mass)
		return ;
	while (mass[sizemass])
	{
		if (*mass[sizemass])
			free(mass[sizemass]);
		sizemass++;
	}
	if (*mass)
		free(mass);
}

void	sort_tmp_env(char **envp)
{
	int		i;
	int		j;
	int		min;
	char	*tmp;

	i = 0;
	while (i < g_shell.len - 1)
	{
		min = i;
		j = i + 1;
		while (j < g_shell.len)
		{
			if (ft_strncmp(envp[j], envp[min], \
			ft_strlen(g_shell.envp[min])) < 0)
				min = j;
			j++;
		}
		tmp = envp[i];
		envp[i] = envp[min];
		envp[min] = tmp;
		i++;
	}
}
