/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:07:52 by eward             #+#    #+#             */
/*   Updated: 2022/07/16 13:08:18 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_str(void)
{
	char	*input;
	int		i;
	char	**rez;

	rez = NULL;
	i = 0;
	input = NULL;
	g_shell.console_name = "minishell> ";
	g_shell.pid = getpid();
	g_shell.pipe = 0;
	g_shell.arrow = '\0';
	g_shell.quote = 0;
	if (read_str(&input) == 0)
		substitute_envp(input);
	else
		return (0);
	return (input);
}

int	fill_list(char	*str)
{
	g_shell.cmd_start = NULL;
	while (*str)
		if (add_elem(&g_shell.cmd_start, &str) == -1)
			return (-1);
	return (0);
}

int	go_to_word(char **a, int *j, char **str)
{
	*j = 0;
	*a = (char *)malloc(sizeof(char) * (word_len(*str) + 1));
	if (!a)
		return (-1);
	while (**str && sp(**str))
		(*str)++;
	return (0);
}
