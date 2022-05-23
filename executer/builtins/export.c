/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:13:19 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/23 19:27:03 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_double(char *args, char **envp)// проверка на повторный параметр в export
{
	int		i;
	char	*str_tmp;

	i = 0;
	str_tmp = malloc(sizeof(char) * (ft_sym_export(args) + 1));
	if (!str_tmp)
		return (NULL);
	while (args[i] != '\0' && args[i] != '=')
	{
		str_tmp[i] = args[i];
		i++;
	}
	str_tmp[i] = '\0';
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(str_tmp, envp[i], max(ft_strlen(str_tmp),
					ft_sym_export(envp[i]))))
			return (str_tmp);
		i++;
	}
	//ft_free(&str_tmp);
	return (NULL);
}

char	**after_quotes(char **tmpmass, 	t_shell *shell)
{
	int		i;
	int		j;
	int		k;
	char	**after;


	after = malloc(sizeof(char *) * (shell->len + 1));
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

char	**before_quotes(char **tmpmass,	t_shell *shell)
{
	int		i;
	int		j;
	char	**before;

	before = malloc(sizeof(char *) * (shell->len + 1));
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

char	**new_envp(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	shell->len = i;
	if (!shell->envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	return (shell->envp);
}

void	no_args(char **envp, t_shell *shell)
{
	int		i;
	char	**tmp;
	char	**before;
	char	**after;

	i = 0;
	tmp = new_envp(envp, shell);
	sort_tmp_env(tmp, shell->len);
	before = before_quotes(tmp, shell);//до ""
	after = after_quotes(tmp, shell);//после ""
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

int builtin_export(char **args, t_shell *shell)
{
	int		i;
	int		j;
	char	*new;

	if (!args[1])
		no_args(shell->envp, shell);
	i = 0;
	while (args[++i])
	{
		j = -1;
		new = check_double(args[i], shell->envp);
		while (args[i][++j])
		{
			if (!ft_isalpha(args[i][0]) || args[i][0] == '=')
				printf("export: not a valid identifier\n");
				// errmsg("minishell: export: `", args[i],
				// 	"': not a valid identifier", -1);
			else
			{
				change_envp(new, args, i, shell);
			}
			break ;
		}
		if (new)
			free(new);
	}
	return (0);
}

// int		check_name(char *name)
// {
// 	int j;

// 	j = 0;
// 	while (name[j])
// 	{
// 		if (!ft_isalnum((int)name[j]) && name[j] != '_')
// 		{
// 			ft_putstr_fd("export: not a valid identifier\n", 1);
// 			return (1);
// 		}
// 		j++;
// 	}
// 	return (0);
// }

// int	export_par(t_shell *env, char *str)
// {
// 	char	*par;
// 	char	*val;

// 	if (str[0] == '=')
// 	{
// 		ft_putstr_fd("export: not a valid identifier\n", 1);
// 		return (1);
// 	}
// 	if (!strchr(str, '='))
// 	{
// 		par = ft_strtrim(str, " ");
// 		val = ft_strdup("");
// 	}
// 	else
// 	{
// 		par = ft_substr(str, 0, ft_strchr(str, '=') - str);
// 		val = ft_strtrim(ft_strchr(str, '=') + 1, " ");
// 	}
// 	if (check_name(par))
// 	{
// 		ft_putstr_fd("export: not a valid identifier\n", 1);
// 		return (1);
// 	}
// 	return (set_env(env, par, val));
// }

// void	sort_tmp_env(t_shell *shell)
// {
// 	int		i;
// 	int		j;
// 	int		min;
// 	char	*tmp;

// 	i = 0;
// 	while (i < shell->len - 1)
// 	{
// 		min = i;
// 		j = i + 1;
// 		while (j < shell->len)
// 		{
// 			if (ft_strncmp(shell->envp[j], shell->envp[min], \
// 			ft_strlen(shell->envp[min])) < 0)
// 				min = j;
// 			j++;
// 		}
// 		tmp = shell->envp[i];
// 		shell->envp[i] = shell->envp[min];
// 		shell->envp[min] = tmp;
// 		i++;
// 	}
// }


// void	export(t_shell *shell)
// {
// 	int		i;
// 	char	*name;
// 	char 	**args;


// 	i = 0;
// 	shell->envp = malloc(sizeof(char **) * (shell->len + 1));
// 	while (++i < shell->len)
// 		shell->envp[i] = ft_strdup(shell->envp[i]);
// 	while (args[1][i] && args[1][i] != '=')
// 		i++;
// 	name = ft_substr(args[1], 0, i);
// 	i++;
// 	sort_tmp_env(shell);
// 	while (i < shell->len)
// 	{
// 		if (!ft_strnstr(shell->export[i], "_=", 2)
// 			&& !ft_strnstr(shell->export[i], "?=", 2))
// 			printf("declare -x %s\n", shell->export[i]);
// 		i++;
// 	}
// }

// int	builtin_export(char **args, t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	if (args && !args[0])
// 		export(shell);
// 	while (args && args[i])
// 	{
// 		export_par(shell, args[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int	builtin_export(char **args, t_shell *shell)
// {
// 	int		i;
// 	char 	*name;
// 	char 	*value;

// 	i = 0;
// 	if (!args[1] || !ft_strrchr(args[1], (int)'='))
// 		return (1);

// 	printf("da\n");
// 	i++;
// 	sort_tmp_env(shell);
// 	value = ft_strdup(args[1] + i);
// 	set_env(shell, name, value);
// 	free(name);
// 	free(value);
// 	return (0);
// }