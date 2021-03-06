/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:10:29 by eward             #+#    #+#             */
/*   Updated: 2022/07/16 17:51:36 by rtwitch          ###   ########.fr       */
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

int	print_token_err(char c)
{
	printf("minishell: syntax error near unexpected token ");
	if (c)
		printf("`%c'\n", c);
	else
		printf("`newline'\n");
	return (-1);
}
