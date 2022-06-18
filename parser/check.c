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
					printf("parse error near `\n'\n");
				else
					printf("parse error near `%c'\n", *inpt);
				return (-1);
			}
		}
		inpt++;
	}
	return (1);
}