/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:19:15 by eward             #+#    #+#             */
/*   Updated: 2022/06/18 17:19:19 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_allowed(char c)
{
	if (c == '|' || c == '&' || c ==';')
		return (1);
	return (-1);
}

//проверка < << > >>
int	double_check_inpt(char *inpt)
{
	while (*inpt)
	{
		if (is_arrow(inpt))
		{
			if (is_arrow(inpt) % 2)
				inpt += 2;
			else
				inpt++;
			while (is_space(*inpt))
				inpt++;
			if (!*inpt || is_arrow(inpt) || not_allowed(*inpt))
			{
				if (!*inpt)
					printf("parse error near `\\n'\n");
				else
					printf("parse error near `%c'\n", *inpt);
				return (-1);
			}
		}
		inpt++;
	}
	return (1);
}

int	delete_quote(char **inpt)
{
	int	i;

	g_shell.quote = 0;
	i = 0;
	while (*(*inpt + i))
	{
		if (g_shell.quote)
		{
			while (*(*inpt + i) != g_shell.quote)
			{
				*(*inpt + i - 1) = *(*inpt + i);
				i++;
			}
			while (*(*inpt + i + 1))
			{
				*(*inpt + i - 1) = *(*inpt + i + 1);
				i++;
			}
			*(*inpt + i - 1) = '\0';
		}
		if ((*(*inpt + i) == '\'' || *(*inpt + i) == '\"') && !g_shell.quote)
			g_shell.quote = *(*inpt + i);
		i++;
	}
	return (0);
}