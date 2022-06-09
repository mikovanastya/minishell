/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/17 19:59:28 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell	g_shell;

int	main(int argc, char **argv, char **envp)
{	
	char	*input;

	(void)argv;
	(void)argc;
	(void)envp;
	//input = NULL;
	if (argc != 1)
	 	ft_error(argv[0], EINVAL);
	g_shell.console_name = "minishell> ";
	g_shell.quote = 0;
	g_shell.len = 0;
	while (1)
	{
		read_str(&input);
		substitute_envp(input, envp);
		printf("\n answ %s\n", input);
		if (*input || input)
			ft_bzero(input, ft_strlen(input));
	}
	// if (input)
	
}
