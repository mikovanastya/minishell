/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:50:18 by eward             #+#    #+#             */
/*   Updated: 2022/06/28 18:03:39 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_help_and_rez(char **help, char **rez, char **inpt)
{
	if (*rez)
		free(*rez);
	*rez = ((char *)malloc(sizeof(char *) * (ft_strlen(*inpt)
					+ ft_strlen(*help) + 1)));
	if (!*rez)
	{
		free_memory(*inpt, *help, *rez);
		return (-1);
	}
	if (ft_strlcpy(*rez, *help, ft_strlen(*help) + 1) < 0)
	{
		free_memory(*inpt, *help, *rez);
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
		free_memory(*inpt, help, *rez);
		return (-1);
	}
	(*rez)[ft_strlen(*rez)] = '\0';
	if (ft_strlcpy(help, *rez, ft_strlen(*rez) + 1) < 0)
	{
		free_memory(*inpt, help, *rez);
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
	if (*rez)
		free(*rez);
	*rez = (char *)malloc(sizeof(char *) * (ft_strlen(*inpt) + 1));
	if (!*rez)
	{
		if (*inpt)
			free(*inpt);
		if (*rez)
			free(*rez);
		return (-1);
	}
	ft_bzero(*rez, ft_strlen(*inpt));
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
	if (ft_strlcat(*rez, *inpt, ft_strlen(*inpt) + ft_strlen(*rez) + 1) < 0)
	{
		// free_memory(*inpt, *inpt, *rez);
		return (-2);
	}
	return (1);
}
