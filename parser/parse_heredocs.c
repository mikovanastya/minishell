/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:23:35 by eward             #+#    #+#             */
/*   Updated: 2022/07/16 16:46:18 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_to_heredoc(char *delim, int file)
{
	char	*inpt;

	inpt = readline(">");
	if (inpt == NULL)
		exit(1);
	add_history(inpt);
	if (!*inpt)
		inpt = ft_strdup("\n");
	if (ft_strncmp(inpt, delim, ft_strlen(inpt)) != 0)
		write(file, inpt, ft_strlen(inpt));
	while (ft_strncmp(inpt, delim, ft_strlen(inpt)) != 0)
	{
		if (inpt)
			free(inpt);
		inpt = readline(">");
		if (ft_strncmp(inpt, delim, ft_strlen(inpt)) != 0)
			write(file, "\n", 1);
		add_history(inpt);
		if (!*inpt)
			inpt = ft_strdup("\n");
		if (ft_strncmp(inpt, delim, ft_strlen(inpt)) != 0)
			write(file, inpt, ft_strlen(inpt));
	}
	if (inpt)
		free(inpt);
}

int	parse_heredoc(char *delim)
{
	int		file;

	file = 0;
	if (!delim)
	{
		printf("minishell: syntax error near unexpected token1 `newline'\n");
		return (-1);
	}
	file = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		printf("minishell: no space left on device\n");
		return (-1);
	}
	read_to_heredoc(delim, file);
	close(file);
	return (0);
}
