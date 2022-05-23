/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/23 16:01:44 by rtwitch          ###   ########.fr       */
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

	init_env(env, &shell);
	if (strcmp(argv[1], "env") == 0)
		builtin_env(&shell);
	printf("now %s\n", get_env_value(&shell, "PWD"));
	if (strcmp(argv[1], "export") == 0)
	{
		printf("nastya\n");
		builtin_export(&argv[1], &shell);
	}
	printf("old %s\n", get_env_value(&shell, "USER"));
}

// int	main(int argc, char **argv)
// {
// 	if (strcmp(argv[1], "cd") == 0)
// 		builtin_cd(&argv[1], 1);
// }

/*s\n
1 скопировать весь env в новый созданный envp
	// using_history();
	// while(1)
	// {
	// 	char *str = readline("minishellllll");
	// 	add_history(str);
	// 	free (str);
	// }
	//builtin_cd(env, &shell);

	//printf("%s\n", get_env_value(&shell, "OLDPWD"));
	//printf("%d\n", del_env(&shell, "OLDPWD"));
	// del_env(&shell, "OLDPWD");
		// if (strcmp(argv[1], "pwd") == 0)
	// 	builtin_pwd();
	// int i = 0;
	// 	while (argv[i])
	// {
	// 	printf ("%s\n", argv[i]);
	// 	i++;
	// }
		// set_env(&shell, "USER", "m,kk");

	// set_env(&shell, "USdER", "123123123");
	// printf("%s\n", get_env_value(&shell, "USdER"));
*/