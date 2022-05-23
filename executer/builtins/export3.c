/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:20:53 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/23 18:36:24 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_sym_export(char *str)//символы, идем и пока не дойдем до конца или до =
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
	while (mass[sizemass])
	{
		free(mass[sizemass]);
		sizemass++;
	}
	free(mass);
}

void sort_tmp_env(char **envp, int len)
{
	int		i;
	int		j; 
	int		min;
	char *tmp;

	i = 0;
	printf ("-----------------------------%d\n", len);
	while (i < len - 1)
	{
		min = i;
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(envp[j], envp[min], \
			ft_strlen(envp[min])) < 0)
				min = j;
			j++;
		}
		tmp = envp[i];
		envp[i] = envp[min];
		envp[min] = tmp;
		i++;
	}
}
