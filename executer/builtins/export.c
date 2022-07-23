/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:19 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 19:22:26 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_name(char *args)
{
	int	i;

	if ((!ft_isalpha(args[0])) && args[0] != '_' )
		return (1);
	i = 1;
	while (args[i])
	{
		if ((!ft_isalnum(args[i])) && args[i] != '_' && args[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

char	**new_envp(void)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (g_shell.envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (g_shell.envp[i])
	{
		new_envp[i] = ft_strdup(g_shell.envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	no_args(void)
{
	int		i;
	char	**tmp;
	char	**before;
	char	**after;

	i = 0;
	tmp = new_envp();
	sort_tmp_env(tmp);
	before = before_quotes(tmp);
	after = after_quotes(tmp);
	while (tmp[i])
	{
		if (!ft_strchr(tmp[i], '='))
			printf("declare -x %s\n", before[i]);
		else
			printf("declare -x %s=\"%s\"\n", before[i], after[i]);
		i++;
	}
}

int	export_prmtrs(char *str)
{
	char	*par;
	char	*val;

	if (!strchr(str, '='))
	{
		par = ft_strtrim(str, " ");
		val = ft_strdup("");
	}
	else
	{
		par = ft_substr(str, 0, ft_strchr(str, '=') - str);
		val = ft_strtrim(ft_strchr(str, '=') + 1, " ");
	}
	return (set_env(par, val));
}

int	builtin_export(void)
{
	int		i;

	if (!g_shell.cmd_start->argv[1])
		no_args();
	i = 1;
	while (g_shell.cmd_start->argv[i])
	{
		if (check_name(g_shell.cmd_start->argv[i]))
		{
			printf("export: not a valid identifier\n");
			return (1);
		}
		export_prmtrs(g_shell.cmd_start->argv[i]);
		i++;
	}
	return (0);
}
