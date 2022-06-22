/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/22 13:38:18 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> 
#include <readline/readline.h> 
#include <readline/history.h>
#include <readline/readline.h>

static void	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("Myshell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

int	main(int argc, char **argv, char **env)
{
	// t_shell	shell;
	// t_cmd	*cmd1;
	// t_cmd	*cmd2;

	// check_args(argc, argv);
	// init_env(env, &shell);
	// cmd1 = malloc(sizeof(t_cmd));
	// shell.cmd_start = &cmd1;
	// cmd1->argv = malloc(sizeof(char *) * 3);
	// cmd1->argv[0] = ft_strdup("grep");//если подавать ошибочный файл выведет код ошибки 
	// cmd1->argv[1] = ft_strdup("'4'");
	// cmd1->argv[2] = NULL;
	// cmd1->file = malloc(sizeof(char *) * 3);
	// cmd1->file[0] = ft_strdup("<");
	// cmd1->file[1] = ft_strdup("file1");
	// cmd1->file[2] = NULL;
	// cmd1->exit_status = 0;
	// // cmd2 = malloc(sizeof(t_cmd));
	// // shell.cmd_start = &cmd1;
	// // cmd2->argv = malloc(sizeof(char *) * 3);
	// // cmd2->argv[0] = ft_strdup("wc");
	// // cmd2->argv[1] = ft_strdup("-l");
	// // cmd2->argv[2] = NULL;
	// // cmd1->next = cmd2;
	// // cmd2->prev = cmd1;
	// // cmd2->exit_status = 0;
	// printf("%s\n", (*shell.cmd_start)->argv[0]);
	// printf("%s\n", (*shell.cmd_start)->argv[1]);
	// printf("%s\n", (*shell.cmd_start)->argv[2]);
	// printf("%s\n", (*shell.cmd_start)->argv[3]);
	// printf("%s\n", (*shell.cmd_start)->next->argv[0]);
	// printf("%s\n", (*shell.cmd_start)->next->argv[1]);
	// printf("END OF PARSING\n\n");
	//pipex(&shell)ж
	// printf("__%s__\n", get_env_value(&shell, "_"));
	//cmd1->file = NULL;
	// make_heredocs(cmd1, &shell);
	// signal(SIGINT, handler_signal);
	// signal(SIGQUIT, handler_signal);
	// using_history();
	// while(1)
	// {
	// 	init_env(env, &shell);
	// 	char *str = readline("minishell🦚 "); 
	// 	add_history(str);
	// 	printf("read this string ->|%s|<-\n", str);
	// 	printf("HERE\n");
	// 	free (str);
	// }
	return (0);
}








	// t_shell	shell;
	// t_cmd	*cmd1;
	// t_cmd	*cmd2;

	// check_args(argc, argv);
	// init_env(env, &shell);
	// cmd1 = malloc(sizeof(t_cmd));
	// shell.cmd_start = &cmd1;
	// cmd1->argv = malloc(sizeof(char *) * 2);
	// cmd1->argv[0] = ft_strdup("cat");//если подавать ошибочный файл выведет код ошибки 
	// cmd1->argv[1] = ft_strdup("executer/1.txt");
	// cmd1->argv[1] = NULL;
	// cmd1->exit_status = 0;
	// cmd2 = malloc(sizeof(t_cmd));
	// shell.cmd_start = &cmd1;
	// cmd2->argv = malloc(sizeof(char *) * 3);
	// cmd2->argv[0] = ft_strdup("wc");
	// cmd2->argv[1] = ft_strdup("-l");
	// cmd2->argv[2] = NULL;
	// cmd1->next = cmd2;
	// cmd2->prev = cmd1;
	// cmd2->exit_status = 0;
	// printf("%s\n", (*shell.cmd_start)->argv[0]);
	// printf("%s\n", (*shell.cmd_start)->argv[1]);
	// printf("%s\n", (*shell.cmd_start)->next->argv[0]);
	// printf("%s\n", (*shell.cmd_start)->next->argv[1]);
	//printf("END OF PARSING\n\n");
	// pipex(&shell);
	// //printf("__%s__\n", get_env_value(&shell, "_"));
	// cmd1->file = NULL;
	// make_heredocs(cmd1, &shell);
	// signal(SIGINT, handler_signal);
	// signal(SIGQUIT, handler_signal);
	// using_history();
	// while(1)
	// {
	// 	init_env(env, &shell);
	// 	char *str = readline("minishell🦚 "); 
	// 	add_history(str);
	// 	printf("read this string ->|%s|<-\n", str);
	// 	printf("HERE\n");
	// 	free (str);
	// }
	//return (7);