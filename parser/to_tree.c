/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:07:52 by eward             #+#    #+#             */
/*   Updated: 2022/06/25 15:16:55 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_elements(char **s)
{
	int	n;
	int	i;

	n = 1;
	i = 0;
	while (*(*s + i))
	{
		if ((*(*s + i) == '\'' || *(*s + i) == '\"') && !g_shell.quote)
		{
			g_shell.quote = s[0][i++];
			n++;
			while (*(*s + i) != g_shell.quote && *(*s + i))
				i++;
			i++;
			g_shell.quote = 0;
		}
		while (sp(*(*s + i)))
			i++;
		if (*(*s + i))
			n++;
		while (!sp(*(*s + i)) && *(*s + i) && !is_a(*s + i) && !n_a(*(*s + i)))
			i++;
		i++;
	}
	return (n);
}

int	count_until_spaces(char	*str)
{
	int	i;

	i = 0;
	g_shell.quote = 0;
	while (str[i] != ' ' && str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && !g_shell.quote)
		{
			g_shell.quote = str[i];
			i++;
			while (str[i] != g_shell.quote && str[i])
				i++;
			g_shell.quote = 0;
		}
		i++;
	}
	i++;
	return (i + 1);
}

int	create_and_fill_array(t_for_array	*help, char **str)
{
	while (sp(*(*str + help->k)))
			help->k++;
	help->rez[help->i] = (char *)malloc(sizeof(char)
			* count_until_spaces(*str + help->k));
	help->j = 0;
	while (*(*str + help->k) != ' ' && str[0][help->k])
	{
		if ((*(*str + help->k) == '\"' || *(*str + help->k) == '\'')
			&& !g_shell.quote)
		{
			g_shell.quote = str[0][help->k++];
			while (*(*str + help->k) != g_shell.quote && *(*str + help->k))
				help->rez[help->i][help->j++] = str[0][help->k++];
			g_shell.quote = 0;
		}
		else
			help->rez[help->i][help->j++] = *(*str + help->k);
		help->k++;
	}
	help->rez[help->i++][help->j] = '\0';
}

char	**put_str_to_tree(char **str)
{
	t_for_array	help;

	g_shell.quote = 0;
	help.num = count_elements(str);
	help.rez = (char **)malloc(sizeof(char *) * help.num);
	if (!help.rez)
		return (0);
	help.rez[help.num - 1] = NULL;
	help.i = 0;
	help.k = 0;
	g_shell.quote = 0;
	while (help.i < help.num - 1)
		create_and_fill_array(&help, str);
	return (help.rez);
}

char	**get_str(char **envp)
{
	char	*input;
	int		i;
	char	**rez;

	rez = NULL;
	i = 0;
	input = NULL;
	g_shell.console_name = "minishell> ";
	g_shell.len = 0;
	g_shell.pid = getpid();
	g_shell.pipe = 0;
	g_shell.arrow = '\0';
	g_shell.quote = 0;
	if (read_str(&input) == 0)
	{
		substitute_envp(input, envp);
		double_check_inpt(input);
		rez = put_str_to_tree(&input);
	}
	else
		printf("\n");
	if (*input || input)
		ft_bzero(input, ft_strlen(input));
	return (rez);
}
