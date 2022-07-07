/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:07:32 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/07 16:14:23 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	type_check(int type)
// {
// 	// if (type == builtins || type == ' ')
// 	// 	return (1);
// 	if (type == ' ' || type == '\t' || type == '\n' || type == '\v'
// 		|| type == '\f' || type == '\r' || type == '<' || type == '>')
// 		return (1);
// 	if (type == '<' || type == '<<'
// 		|| type == '>' || type == '>>'
// 		|| type == '<' || type == '<<'
// 		|| type == '>' || type == '>>')
// 		return (2);
// 	if (type == '|')
// 		return (3);
// 	return (0);
// }

int	type_check(int type)
{
	if (type == BUILTIN || type == ARG)
		return (1);
	if (type == FILE_IN || type == HERE_DOC
		|| type == FILE_OUT || type == FILE_OUT_SUR
		|| type == OPEN_FILE || type == LIMITOR
		|| type == EXIT_FILE || type == EXIT_FILE_RET)
		return (2);
	if (type == PIPE)
		return (3);
	return (0);
}

static int	ft_count_argv(t_list *tokens)
{
	t_list	*step;
	int		count_argv;

	count_argv = 0;
	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == BUILTIN || step->type == ARG)
			count_argv++;
		step = step->next;
	}
	return (count_argv);
}

static int	ft_count_file(t_list *tokens)
{
	t_list	*step;
	int		count_file;

	count_file = 0;
	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == FILE_IN || step->type == HERE_DOC
			|| step->type == FILE_OUT || step->type == FILE_OUT_SUR
			|| step->type == OPEN_FILE || step->type == LIMITOR
			|| step->type == EXIT_FILE || step->type == EXIT_FILE_RET)
			count_file++;
		step = step->next;
	}
	return (count_file);
}
// static int	ft_count_file(t_list *tokens)
// {
// 	t_list	*step;
// 	int		count_file;

// 	count_file = 0;
// 	step = tokens;
// 	while (step && step->type != '|')
// 	{
// 		if (step->type == '<' || step->type == '<<'
// 			|| step->type == '>' || step->type == '>>'
// 			|| step->type == '<' || step->type == '<<'
// 			|| step->type == EXIT_FILE || step->type == EXIT_FILE_RET)
// 			count_file++;
// 		step = step->next;
// 	}
// 	return (count_file);
// }
void	ft_copy_file(char **file, char *tokens, int type)
{
	static int	i = 0;

	if (type != 3)
	{
		file[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		file[i] = NULL;
		i = 0;
	}
}

void	ft_copy_argv(char **argv, char *tokens, int type)
{
	static int	i = 0;

	if (type != 3)
	{
		argv[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		argv[i] = NULL;
		i = 0;
	}
}


void	ex_cmd_add_back(t_cmd **ex_cmd, t_cmd *new)
{
	t_cmd	*step;

	if (ex_cmd != NULL)
	{
		step = *ex_cmd;
		while (step->next != NULL)
			step = step->next;
		new->prev = step;
		step->next = new;
	}
	else
		ex_cmd = &new;
}


static char	**ft_matrix_copy(char **args)
{
	char	**copy;
	int		i;

	i = 0;
	while (args[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_cmd	*new_ex_cmd(char **argv, char **file_name)
{
	t_cmd	*ex_cmd;

	ex_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ex_cmd)
		return (NULL);
	ex_cmd->argv = ft_matrix_copy(argv);
	ex_cmd->file_name = ft_matrix_copy(file_name);
	ex_cmd->next = NULL;
	ex_cmd->prev = NULL;
	return (ex_cmd);
}

void	copy_end(char **argv, char **file, t_cmd **ex_cmd)
{
	ft_copy_argv(argv, NULL, 3);
	ft_copy_file(file, NULL, 3);
	ex_cmd_add_back(ex_cmd, new_ex_cmd(argv, file));
	// ft_matrix_free(argv);
	// ft_matrix_free(file);
}

void	init_redir(t_cmd **redir_cmd, t_list *tokens,
		char **argv, char **file_name)
{
	t_list	*step;

	step = tokens;
	argv = (char **)malloc(sizeof(char *) * (ft_count_argv(step) + 1));
	file_name = (char **)malloc(sizeof(char *) * (ft_count_file(step) + 1));
	while (step)
	{
		if (type_check(step->type) == 1)
			ft_copy_argv(argv, step->content, 1);
		if (type_check(step->type) == 2)
			ft_copy_file(file_name, step->content, 2);
		if (type_check(step->type) == 3)
		{
			copy_end(argv, file_name, redir_cmd);
			step = step->next;
			argv = (char **)malloc(sizeof(char *) * (ft_count_argv(step) + 1));
			file_name = (char **)malloc(sizeof(char *) * (ft_count_file(step) + 1));
			continue ;
		}
			step = step->next;
	}
	copy_end(argv, file_name, redir_cmd);
}

int	open_file(char *name, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(name, O_RDONLY, 0777);
	if (file == -1)
	{
		if (access(name, F_OK) == 0)
			printf("minishell: %s Is a directory\n", name);
		else
			printf("minishell: : %s\n", name);
		if (quit == 0)
			exit(1);
	}
	return (file);
}

int	check_redirection(int quit)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	// if (!(*(g_shell.cmd_start))->redir)
	// 	return (0);
	while ((*(g_shell.cmd_start))->file_name && (*(g_shell.cmd_start))->file_name[i])
	{
	// printf("Redir [%d]_%s%s_\n", i, (*(g_shell.cmd_start))->redir[i], (*(g_shell.cmd_start))->file_name[i]);
		printf("file_name: %s\n redir: %s\n argv: %s\n", (*(g_shell.cmd_start))->file_name[i], (*(g_shell.cmd_start))->redir[i], (*(g_shell.cmd_start))->argv[i]);
		if (ft_strcmp(((*(g_shell.cmd_start))->redir[i]), "<") == 0)
			fd[0] = open_file(((*(g_shell.cmd_start))->file_name[i]), 2, quit);
		else if (ft_strcmp(((*(g_shell.cmd_start))->redir[i]), ">") == 0)
			fd[1] = open_file(((*(g_shell.cmd_start))->file_name[i]), 1, quit);
		else if (ft_strcmp(((*(g_shell.cmd_start))->redir[i]), ">>") == 0)
			fd[1] = open_file(((*(g_shell.cmd_start))->file_name[i]), 0, quit);
		else if (ft_strcmp(((*(g_shell.cmd_start))->redir[i]), "<<") == 0)
			dup2((*(g_shell.cmd_start))->fd[0], STDIN_FILENO);
		i++;
	}
	// printf("AFTER OPENING FILE [%d][%d]\n", fd[0], fd[1]);
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}
