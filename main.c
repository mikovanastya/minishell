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

int	main(int argc, char **argv, char **env)
{
	t_shell shell;


	init_env(env, &shell);
	//builtin_cd(env, &shell);
	// builtin_env(&shell);
	//printf("%s\n", get_env_value(&shell, "OLDPWD"));
	//printf("%d\n", del_env(&shell, "OLDPWD"));
	// del_env(&shell, "OLDPWD");
	// if (strcmp(argv[1], "pwd") == 0)
	// 	builtin_pwd();
	if (strcmp(argv[1], "cd") == 0)
		builtin_cd(&argv[1], &shell);
	// set_env(&shell, "USER", "m,kk");
	// printf("%s\n", get_env_value(&shell, "USER"));
	// set_env(&shell, "USdER", "123123123");
	// printf("%s\n", get_env_value(&shell, "USdER"));
}
// int	main(int argc, char **argv)
// {
// 	if (strcmp(argv[1], "cd") == 0)
// 		builtin_cd(&argv[1], 1);
// }

/*s\n

1 скопировать весь env в новый созданный envp
*/