/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:19 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/01 17:48:23 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_name(char *args)
{
	int	i;

	//args[0] буква или _
	if ((!ft_isalpha(args[0])) && args[0] != '_' )
		return (1);
	i = 1;
	while (args[i])
	{
		//args[i] буква цифра _ =
		if ((!ft_isalnum(args[i])) && args[i] != '_' && args[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

char	**new_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_shell.envp = malloc(sizeof(char *) * (i + 1));
	g_shell.len = i;
	if (!g_shell.envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		g_shell.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_shell.envp[i] = NULL;
	return (g_shell.envp);
}

void	no_args(char **envp)
{
	int		i;
	char	**tmp;
	char	**before;
	char	**after;

	i = 0;
	tmp = new_envp(envp);
	sort_tmp_env(tmp, g_shell.len);
	before = before_quotes(tmp);//до =""
	after = after_quotes(tmp);//после =""
	while (tmp[i])
	{
		if (!ft_strchr(tmp[i], '='))
			printf("declare -x %s\n", before[i]);
		else
			printf("declare -x %s=\"%s\"\n", before[i], after[i]);
		i++;
	}
	// ft_free(tmp);
	// ft_free(before);
	// ft_free(after);
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

int	builtin_export(char **args)
{
	int		i;
	// char	**do_ravno;
	// char	**posle_ravno;

	if (!args[1])
		no_args(g_shell.envp);
	i = 1;
	while (args[i])
	{

		if (check_name(args[i]))//// !!! Проверка на валидность аргумента ("name=value")
		{
			printf("export: not a valid identifier\n");
			return (1);
		}
		//printf("work please\n");
		export_prmtrs(args[i]);
		i++;
	}
	//printf("!%s!", before_quotes(args, shell));
	return (0);
}
