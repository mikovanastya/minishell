/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:23:35 by eward             #+#    #+#             */
/*   Updated: 2022/07/14 12:23:38 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	parse_heredoc(char *delim)
{
	char	*inpt;
	int		file;

	file = 0;
	inpt = NULL;
	if (!delim)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	file = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		printf("minishell: no space left on device\n");
		return (-1);
	}
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
	close(file);
	return (0);
}
