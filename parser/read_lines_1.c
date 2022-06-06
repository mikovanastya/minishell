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

int	change_help_and_rez(char **help0, char **rez, char **inpt)
{
	char	*help;
	char	*rez_f;
	char	*inpt_f;

	rez_f = *rez;
	inpt_f = *inpt;
	help = *help0;
	rez_f = ((char *)malloc(sizeof(char *) * (ft_strlen(inpt_f)
					+ ft_strlen(help) + 1)));
	if (!rez_f)
	{
		free_memory(inpt_f, help, rez_f);
		return (-1);
	}
	if (ft_strlcpy(rez_f, help, ft_strlen(help) + 1) < 0)
	{
		free_memory(inpt_f, help, rez_f);
		return (-2);
	}
	free(rez_f);
	*rez = rez_f;
	*inpt = inpt_f;
	*help0 = help;
	return (1);
}

int	resize_rez(char **rez, char **inpt)
{
	char	*help;
	char	*rez_f;
	char	*inpt_f;
	int		from_func;

	rez_f = *rez;
	inpt_f = *inpt;
	help = (char *)malloc(sizeof(char *) * (ft_strlen(rez_f) + 1));
	if (!help)
	{
		free_memory(inpt_f, help, rez_f);
		return (-1);
	}
	rez_f[ft_strlen(rez_f)] = '\0';
	if (ft_strlcpy(help, rez_f, ft_strlen(rez_f) + 1) < 0)
	{
		free_memory(inpt_f, help, rez_f);
		return (-2);
	}
	from_func = change_help_and_rez(&help, &rez_f, &inpt_f);
	if (from_func != 1)
		return (from_func);
	*rez = rez_f;
	free(help);
	return (1);
}

int	init_rez(char **rez, char **inpt)
{
	char	*rez_f;
	char	*inpt_f;

	rez_f = *rez;
	inpt_f = *inpt;
	rez_f = (char *)malloc(sizeof(char *) * (ft_strlen(inpt_f) + 1));
	if (!rez_f)
	{
		if (inpt_f)
			free(inpt_f);
		if (rez_f)
			free(rez_f);
		return (-1);
	}
	ft_bzero(rez_f, ft_strlen(inpt_f));
	*rez = rez_f;
	return (1);
}

int	in_cycle(char **rez, char **inpt, int *may_continue)
{
	char	*rez_f;
	char	*inpt_f;
	int		resize;

	rez_f = *rez;
	inpt_f = *inpt;
	if (!rez_f)
	{
		if (init_rez(&rez_f, &inpt_f) == -1)
			return (-1);
	}
	else
	{
		resize = resize_rez(&rez_f, &inpt_f);
		if (!resize)
			return (resize);
	}
	*may_continue = go_on(inpt_f);
	if (ft_strlcat(rez_f, inpt_f, ft_strlen(inpt_f) + ft_strlen(rez_f) + 1) < 0)
	{
		free_memory(inpt_f, inpt_f, rez_f);
		return (-2);
	}
	*rez = rez_f;
	return (1);
}
