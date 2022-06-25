/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:50:18 by eward             #+#    #+#             */
/*   Updated: 2022/05/26 17:50:20 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_help_and_rez(char **help, char **rez, char **inpt)
{
	if (!*rez)
		free(*rez);
	*rez = ((char *)malloc(sizeof(char *) * (ft_strlen(g_shell.line)
					+ ft_strlen(*help) + 1)));
	if (!*rez)
	{
		free_memory(g_shell.line, *help, *rez);
		return (-1);
	}
	if (ft_strlcpy(*rez, *help, ft_strlen(*help) + 1) < 0)
	{
		free_memory(g_shell.line, *help, *rez);
		return (-2);
	}
	return (1);
}

int	resize_rez(char **rez, char **inpt)
{
	char	*help;
	int		from_func;

	help = (char *)malloc(sizeof(char *) * (ft_strlen(*rez) + 1));
	if (!help)
	{
		free_memory(g_shell.line, help, *rez);
		return (-1);
	}
	(*rez)[ft_strlen(*rez)] = '\0';
	if (ft_strlcpy(help, *rez, ft_strlen(*rez) + 1) < 0)
	{
		free_memory(g_shell.line, help, *rez);
		return (-2);
	}
	from_func = change_help_and_rez(&help, rez, inpt);
	if (from_func != 1)
		return (from_func);
	free(help);
	return (1);
}

int	init_rez(char **rez, char **inpt)
{
	if (!*rez)
		free(*rez);
	*rez = (char *)malloc(sizeof(char *) * (ft_strlen(g_shell.line) + 1));
	if (!*rez)
	{
		if (g_shell.line)
			free(g_shell.line);
		if (*rez)
			free(*rez);
		return (-1);
	}
	ft_bzero(*rez, ft_strlen(g_shell.line));
	return (1);
}

int	in_cycle(char **rez, char **inpt, int *may_continue)
{
	int		resize;

	if (!*rez || !**rez)
	{
		if (init_rez(rez, inpt) == -1)
			return (-1);
	}
	else
	{
		resize = resize_rez(rez, inpt);
		if (!resize)
			return (resize);
	}
	*may_continue = go_on(*inpt);
	if (ft_strlcat(*rez, g_shell.line, ft_strlen(*inpt) + ft_strlen(*rez) + 1) < 0)
	{
		free_memory(g_shell.line, g_shell.line, *rez);
		return (-2);
	}
	return (1);
}
