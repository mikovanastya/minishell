/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:50:18 by eward             #+#    #+#             */
/*   Updated: 2022/07/12 21:01:13 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_help_and_rez(char **help, char **rez, char **inpt)
{
	if (!*rez)
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
	if (!*rez)
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

int	init_and_resize_rez(char **rez, char **inpt)
{
	int	resize;

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
	return (0);
}

int	check_input(char **rez, char **inpt, int *may_continue)
{
	int		j;

	j = init_and_resize_rez(rez, inpt);
	if (j != 0)
		return (j);
	while (*(*inpt + j + 1))
	{
		if (is_a(*inpt + j) == 4)
		{
			if (parse_heredoc(*inpt + j + 2) == -1)
				return (-1);
			else
				return (0);
		}
		j++;
	}
	*may_continue = go_on(*inpt);
	if (*may_continue == -2)
		return (-2);
	if (ft_strlcat(*rez, *inpt, ft_strlen(*inpt) + ft_strlen(*rez) + 1) < 0)
	{
		free_memory(*inpt, *inpt, *rez);
		return (-2);
	}
	return (1);
}
