/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/24 16:58:13 by rtwitch          ###   ########.fr       */
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
	char	**rez;
	t_shell	shell;
	t_cmd	*cmd;

	if (argc != 1)
	 	ft_error(argv[0], EINVAL);
	while (1)
	{
		init_env(env, &shell);
		cmd = malloc(sizeof(t_cmd));
		shell.cmd_start = &cmd;
		cmd->argv = get_str(env); // !!
		int i = 0;
		while (cmd->argv[i])
		{
			printf("Cmd %d:[%s]\n",i, cmd->argv[i]);
			i++;
		}
		// signal(SIGINT, handler_signal);
		// signal(SIGQUIT, handler_signal);
		//execute_execve(cmd, &shell);
		pipex(&shell);
		//builtins(cmd->argv, &shell);
		free_array(cmd->argv);
	}
	return (0);
}








// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;

	// t_cmd *cmd1 = malloc(sizeof(t_cmd));
	// cmd1->argv = malloc(sizeof(char *) * 3);
	// cmd1->argv[0] = ft_strdup("cat");//если подавать ошибочный файл выведет код ошибки 
	// cmd1->argv[1] = ft_strdup("file1");
	// cmd1->argv[2] = NULL;
	// cmd1->exit_status = 0;
	// t_cmd *cmd2 = malloc(sizeof(t_cmd));
	// shell.cmd_start = &cmd1;
	// cmd2->argv = malloc(sizeof(char *) * 3);
	// cmd2->argv[0] = ft_strdup("grep");
	// cmd2->argv[1] = ft_strdup("a");
	// cmd2->argv[2] = NULL;
	// cmd1->next = cmd2;
	// cmd2->prev = cmd1;
	// cmd2->exit_status = 0;
	// t_cmd *cmd3 = malloc(sizeof(t_cmd));
	// cmd3->argv = malloc(sizeof(char *) * 3);
	// cmd3->argv[0] = ft_strdup("wc");
	// cmd3->argv[1] = ft_strdup("-l");
	// cmd3->argv[2] = NULL;
	// cmd2->next = cmd3;
	// cmd3->prev = cmd2;
	// cmd3->next = NULL;
//---------------------------------------------------
	// t_cmd *cmd1 = malloc(sizeof(t_cmd));
	// cmd1->argv = malloc(sizeof(char *) * 3);
	// cmd1->argv[0] = ft_strdup("grep");
	// cmd1->argv[1] = ft_strdup("cmd");
	// cmd1->argv[2] = NULL;
	// cmd1->exit_status = 0;
	// cmd1->redir = malloc(sizeof(char *) * 3);
	// cmd1->redir[0] = ft_strdup("<");
	// cmd1->redir[1] = ft_strdup(">>");
	// cmd1->redir[2] = NULL;
	// cmd1->file_name = malloc(sizeof(char *) * 3);
	// cmd1->file_name[0] = ft_strdup("1.txt");
	// cmd1->file_name[1] = ft_strdup("335.txt");
	// cmd1->file_name[2] = NULL;


	// init_env(env, &shell);
	// shell.cmd_start = &cmd1;

	// printf("%s\n", (*shell.cmd_start)->argv[0]);

	//---------------
	// printf("%s\n", (*shell.cmd_start)->argv[1]);
	// printf("%s\n", (*shell.cmd_start)->argv[2]);
	// printf("%s\n", (*shell.cmd_start)->argv[3]);
	// printf("%s\n", (*shell.cmd_start)->next->argv[0]);
	// printf("%s\n", (*shell.cmd_start)->next->argv[1]);
	// printf("%s\n", (*shell.cmd_start)->next->next->argv[0]);
	// printf("%s\n", (*shell.cmd_start)->next->next->argv[1]);
// 	printf("END OF PARSING\n\n");

// 	pipex(&shell);
// 	// printf("__%s__\n", get_env_value(&shell, "z23"));
// }
