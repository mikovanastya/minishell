/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:10:29 by eward             #+#    #+#             */
/*   Updated: 2022/06/06 17:10:30 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *argv, int exit_code)
{
	printf("%s: ", strerror(exit_code));
	printf("%s\n", argv);
    (void)(exit_code);
	exit(EXIT_FAILURE);
}

void	free_memory(char *inpt, char *help, char *rez)
{
	if (help)
		free(help);
	if (inpt)
		free(inpt);
	if (rez)
		free(rez);
}

int	is_a(char *str)
{
	if (*str == '>' && *(str + 1) == '>')
		return (2);
	if (*str == '>')
		return (1);
	if (*str == '<' && *(str + 1) == '<')
		return (4);
	if (*str == '<')
		return (3);
	return (0);
}