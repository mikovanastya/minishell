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

int	go_on(char *str)
{
	while (*str && *str != '\\' && *str != '\'' &&*str != '"')
		str++;
	if (!(*str))
		return (0);
	else
		return (1);
}
int	read_str(char *rez)
{
	char	*inpt;
	int		may_continue;
	char	quoute;

	may_continue = 1;
	rez = (char *)malloc(sizeof(char *) * 8);
	if (!rez)
		return (-1);
	ft_bzero(rez, sizeof(char *) * sizeof(char));
	while (may_continue == 1)
	{
		inpt = readline("Enter text: "); //readline выделяет память под возвращаемую строку
		add_history(inpt);
		if (!ft_strlcat(rez, inpt, sizeof(char *) * sizeof(char)))
			return (-2);
		may_continue = go_on(inpt);
		free(inpt);
	}
	printf("result %s %d", rez, sizeof(char));
	return (0);
}