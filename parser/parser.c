/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:45:31 by eward             #+#    #+#             */
/*   Updated: 2022/05/18 17:45:32 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*  -1 Если не удалось выделить память
	-2 Если Слишком длинный список агрументов: больше размера char *. precmd:2:
			argument list too long: /bin/syslog.py  
*/
int parse_str(char *rez)
{
	char	*inpt;
	int		i;
	int		was_quote;
	char	quoute;

	was_quote = 0;
	i = 0;
	rez = (char *)malloc(sizeof(char *) * 8);
	if (!rez)
		return (-1);
	ft_bzero(rez, sizeof(char *) * sizeof(char));
	while ( i < 3 )
	{
		inpt = readline("Enter text: "); //readline выделяет память под возвращаемую строку
		add_history(inpt);
		if (!ft_strlcat(rez, inpt, sizeof(char *) * sizeof(char)))
			return (-2);
		free(inpt);
		++i;
	}
	printf("result %s %d", rez, sizeof(char));
	return (0);
}