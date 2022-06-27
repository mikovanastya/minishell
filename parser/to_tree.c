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

char	*get_str(char **envp)
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
	}
	else
		printf("\n");
	printf("input: \n%s\n", input);
	return (input);
}
