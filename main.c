/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:01:07 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/28 18:47:49 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h> 
#include <readline/readline.h> 
#include <readline/history.h>
#include <readline/readline.h>

/*
**	всё вместе:
*/

int	main(int argc, char **argv, char **env)
{
	char	*rez;
	t_shell	shell;
	t_cmd	*cmd;
	int		i;

	//g_shell = (t_shell)malloc(sizeof(t_shell));
	if (argc != 1)
	 	ft_error(argv[0], EINVAL);
	cmd = NULL;
	while (1)
	{
		init_env(env, &shell);
		// shell.cmd_start = g_shell.cmd_start;
		rez = get_str(env); // !!
		printf("inpu1: \n%s\n", rez);
		fill_list(rez);
		// shell.cmd_start = g_shell.cmd_start;
		// while (*(g_shell.cmd_start))
		// {
		// 	i = 0;
		// 	while ((*(g_shell.cmd_start))->argv[i])
		// 	{
		// 		printf("Cmd %d:[%s]\n", i, (*(g_shell.cmd_start))->argv[i]);
		// 		i++;
		// 	}
		// 	if ((*(g_shell.cmd_start))->file_name)
		// 		printf("filename %s\n", *((*(g_shell.cmd_start))->file_name));
		// 	*(g_shell.cmd_start) = (*(g_shell.cmd_start))->next;
		// }
		// signal(SIGINT, handler_signal);
		// signal(SIGQUIT, handler_signal);
		pipex(*(g_shell.cmd_start), &g_shell);
		// builtins(cmd->argv, &shell);
		// while (*(g_shell.cmd_start))
		// {
		// 	i = 0;
		// 	if (g_shell.cmd_start)
		// 	{
		// 		while ((*(g_shell.cmd_start))->argv[i])
		// 	{
		// 		free((*(g_shell.cmd_start))->argv[i]);
		// 		i++;
		// 	}
		// 	if ((*(g_shell.cmd_start))->file_name)
		// 		free(*((*(g_shell.cmd_start))->file_name));
		// 	free((*(g_shell.cmd_start))->argv);
		// 	*(g_shell.cmd_start) = (*(g_shell.cmd_start))->next;
		// 	if (*(g_shell.cmd_start))
		// 	{
		// 		if ((*(g_shell.cmd_start))->prev)
		// 		free((*(g_shell.cmd_start))->prev);
		// 	}
		// 	}
		// }
		free(rez);
		//free struct!!!!!
	}
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	**rez;
// 	t_shell	shell;
// 	t_cmd	*cmd;
// 	int		i;

// 	if (argc != 1)
// 	 	ft_error(argv[0], EINVAL);
// 	cmd = NULL;
// 	while (1)
// 	{
// 		init_env(env, &shell);
// 		shell.cmd_start = cmd;
// 		rez = get_str(env); // !!
// 		fill_list(rez);
// 		shell.cmd_start = g_shell.cmd_start->next;
// 		// while (shell.cmd_start)
// 		// {
// 		// 	i = 0;
// 		// 	while (shell.cmd_start->argv[i])
// 		// 	{
// 		// 		printf("Cmd %d:[%s]\n",i, shell.cmd_start->argv[i]);
// 		// 		i++;
// 		// 	}
// 		// 	shell.cmd_start = shell.cmd_start->next;
// 		// }
// 		signal(SIGINT, handler_signal);
// 		signal(SIGQUIT, handler_signal);
// 		pipex(&shell);
// 		// builtins(cmd->argv, &shell);
// 		free_array(rez);
// 	}
// 	return (0);
// }

/*
**	pipex:
*/

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;

// 	t_cmd *cmd1 = malloc(sizeof(t_cmd));
// 	cmd1->argv = malloc(sizeof(char *) * 3);
// 	cmd1->argv[0] = ft_strdup("cat");//если подавать ошибочный файл выведет код ошибки 
// 	cmd1->argv[1] = ft_strdup("file1");
// 	cmd1->argv[2] = NULL;
// 	cmd1->exit_status = 0;
// 	t_cmd *cmd2 = malloc(sizeof(t_cmd));
// 	shell.cmd_start = &cmd1;
// 	cmd2->argv = malloc(sizeof(char *) * 3);
// 	cmd2->argv[0] = ft_strdup("grep");
// 	cmd2->argv[1] = ft_strdup("a");
// 	cmd2->argv[2] = NULL;
// 	cmd1->next = cmd2;
// 	cmd2->prev = cmd1;
// 	cmd2->exit_status = 0;
// 	t_cmd *cmd3 = malloc(sizeof(t_cmd));
// 	cmd3->argv = malloc(sizeof(char *) * 3);
// 	cmd3->argv[0] = ft_strdup("wc");
// 	cmd3->argv[1] = ft_strdup("-l");
// 	cmd3->argv[2] = NULL;
// 	cmd2->next = cmd3;
// 	cmd3->prev = cmd2;
// 	cmd3->next = NULL;
// 	cmd3->exit_status = 0;
// 	init_env(env, &shell);
// 	shell.cmd_start = &cmd1;
// 	printf("%s\n", (*shell.cmd_start)->argv[0]);
// 	printf("%s\n", (*shell.cmd_start)->argv[1]);
// 	printf("%s\n", (*shell.cmd_start)->next->argv[0]);
// 	printf("%s\n", (*shell.cmd_start)->next->argv[1]);
// 	printf("%s\n", (*shell.cmd_start)->next->next->argv[0]);
// 	printf("%s\n", (*shell.cmd_start)->next->next->argv[1]);
// 	pipex(*(g_shell.cmd_start), &shell);
// }

/*
**	redirect: <file1 grep a >335.txt
*/

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;

// 	t_cmd *cmd1 = malloc(sizeof(t_cmd));
// 	cmd1->argv = malloc(sizeof(char *) * 3);
// 	cmd1->argv[0] = ft_strdup("grep");
// 	cmd1->argv[1] = ft_strdup("a");
// 	cmd1->argv[2] = NULL;
// 	cmd1->exit_status = 0;
// 	cmd1->redir = malloc(sizeof(char *) * 3);
// 	cmd1->redir[0] = ft_strdup("<");
// 	cmd1->redir[1] = ft_strdup(">");
// 	cmd1->redir[2] = NULL;
// 	cmd1->file_name = malloc(sizeof(char *) * 3);
// 	cmd1->file_name[0] = ft_strdup("file1");
// 	cmd1->file_name[1] = ft_strdup("335.txt");
// 	cmd1->file_name[2] = NULL;
// 	init_env(env, &shell);
// 	shell.cmd_start = &cmd1;
// 	printf("%s\n", (*shell.cmd_start)->argv[0]);
// 	printf("%s\n", (*shell.cmd_start)->argv[1]);
// 	pipex(&shell);
// 	printf("__%s__\n", get_env_value(&shell, "z23"));
// }

/*
**	heredoc:
*/

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;

// 	t_cmd *cmd1 = malloc(sizeof(t_cmd));
// 	cmd1->argv = malloc(sizeof(char *) * 3);
// 	cmd1->argv[0] = ft_strdup("echo");
// 	cmd1->argv[1] = ft_strdup("fkzbksile1");
// 	cmd1->argv[2] = NULL;
// 	cmd1->exit_status = 0;
// 	// cmd1->redir = malloc(sizeof(char *) * 2);
// 	// cmd1->redir[0] = ft_strdup("<<");
// 	// cmd1->redir[1] = NULL;
// 	// cmd1->redir[1] = ft_strdup(">");
// 	// cmd1->file_name = malloc(sizeof(char *) * 2);
// 	// cmd1->file_name[0] = ft_strdup("stop_slovo");
// 	// cmd1->file_name[1] = NULL;
// 	// cmd1->file_name[1] = ft_strdup("335.txt");
// 	init_env(env, &shell);
// 	shell.cmd_start = &cmd1;
// 	// printf("__%s__\n", get_env_value(&shell, "z23"));
// 	printf("%s\n", (*shell.cmd_start)->argv[0]);
// 	printf("%s\n", (*shell.cmd_start)->argv[1]);
// 	pipex(&shell);
// }
