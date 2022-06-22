/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:07:52 by eward             #+#    #+#             */
/*   Updated: 2022/06/22 16:03:40 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// &
// | +
// > 1
// >> 2
// < 3
// << 4

// int	service_symbol(char **str)
// {

// }

int	count_elements(char **str)
{
	int	n;
	int	i;

	n = 1;
	i = 0;
	g_shell.quote = 0;
	while (*(*str + i))
	{
		if ((*(*str + i) == '\'' || *(*str + i) == '\"') && !g_shell.quote)
		{
			g_shell.quote = *(*str + i);
			n++;
			i++;
			while (*(*str + i) != g_shell.quote && *(*str + i))
				i++;
			i++;
			g_shell.quote = 0;
		}
		while (is_space(*(*str + i)))
			i++;
		if (*(*str + i))
			n++;
		while (!is_space(*(*str + i)) && *(*str + i) && !is_arrow(*str + i) && !not_allowed(*(*str + i)))
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
char	**put_str_to_tree(char **str)
{
	char	**rez;
	int		num;
	int		i;
	int		j;
	int		k;

	num = count_elements(str);
	rez = (char **)malloc(sizeof(char *) * num);
	if (!rez)
		return (0);
	rez[num - 1] = NULL;
	i = 0;
	k = 0;
	g_shell.quote = 0;
	while (i < num - 1)
	{
		while (is_space(*(*str + k)))
			k++;
		rez[i] = (char *)malloc(sizeof(char) * count_until_spaces(*str + k));
		j = 0;
		while (*(*str + k) != ' ' && *(*str + k))
		{
			if ((*(*str + k) == '\"' || *(*str + k) == '\'') && !g_shell.quote)
			{
				g_shell.quote = *(*str + k);
				k++;
				while (*(*str + k) != g_shell.quote && *(*str + k))
				{
					rez[i][j] = *(*str + k);
					j++;
					k++;
				}
				g_shell.quote = 0;
			}
			else
			{
				rez[i][j] = *(*str + k);
				j++;
			}
			
			k++;
		}
		rez[i][j] = '\0';
		i++;
	}
	return (rez);
}

char	**get_str(char **envp)
{
	char	*input;
	int		i;
	char	**rez;

	rez  = NULL;
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
		double_check_inpt(input); // if -1 error
		//printf("\n answ %s\n", input);
		rez = put_str_to_tree(&input);
	}
	else
		printf("parse error near `|'\n");
	if (*input || input)
		ft_bzero(input, ft_strlen(input));
	return (rez);
}
