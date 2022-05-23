/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:17:19 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/23 19:31:17 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**replace_envp_el(t_shell *shell, char *args, char *new)//перезаписывает параметр 
{
	char	**new_mass;
	int		j;

	j = 0;
	new_mass = malloc(sizeof(char *) * (shell->len + 1));
	if (!new_mass)
		return (NULL);
	while (shell->envp[j])
	{
		if (ft_strncmp(shell->envp[j], new, max(ft_strlen(new),
					ft_sym_export(shell->envp[j]))))
			new_mass[j] = ft_strdup(shell->envp[j]);
		else
			new_mass[j] = ft_strdup(args);
		j++;
	}
	new_mass[j] = NULL;
	free(shell->envp);
	return (new_mass);
}

char	**export_envp(char **envp, char *str, int free)//создаем  новую строку в env
{
	char	**new_mass;
	int		j;

	new_mass = malloc(sizeof(char *) * (sizeof(envp) + 2));
	if (!new_mass)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		new_mass[j] = ft_strdup(envp[j]);
		j++;
	}
	new_mass[j] = ft_strdup(str);
	j++;
	new_mass[j] = NULL;
	if (free)
		ft_free(envp);
	return (new_mass);
}

void	change_envp(char *new, char **args, int i, t_shell *shell)
{
	
	if (new && ft_strrchr(args[i], '='))
	{
		shell->envp = replace_envp_el(shell, args[i], new);
	}
	else if (!new)
	{
		shell->envp = export_envp(shell->envp, args[i], 1);
	}
}
