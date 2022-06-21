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

int	main(int argc, char **argv, char **envp)
{	
	char	*input;
	int		i;

	i = 0;
	if (argc != 1)
	 	ft_error(argv[0], EINVAL);
	g_shell.console_name = "minishell> ";
	g_shell.quote = 0;
	g_shell.len = 0;
	g_shell.pid = getpid();
	g_shell.pipe = 0;
	g_shell.arrow = '\0';
	while (i < 3)
	{
		g_shell.quote = 0;
		if (read_str(&input) == 0)
		{
			substitute_envp(input, envp);
			double_check_inpt(input); // if -1 error
			printf("\n answ %s\n", input);
			//delete_quote(&input); // if -1 error
			//printf("\n answ with no qoutes %s\n", input);
			put_str_to_tree(&input);
		}
		else
			printf("parse error near `|'\n");
		if (*input || input)
				ft_bzero(input, ft_strlen(input));
		i++;
	}
}
