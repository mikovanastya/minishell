/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/01 16:12:04 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> 
#include <readline/readline.h> 
#include <readline/history.h>
#include <readline/readline.h>



int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	t_cmd	cmd;

	using_history();
	while(1)
	{
		init_env(env, &shell);
		char *str = readline("minishell🦚 "); 
		add_history(str);
		printf("read this string ->|%s|<-\n", str);
		pipex(&shell);
		signal(SIGINT, handler_signal);
		signal(SIGQUIT, handler_signal);
		free (str);
	}
	init_env(env, &shell);
}
