/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:02:04 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/22 14:03:45 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# include <printf.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "string.h" // !! УДАЛИТЬ !!!*


#include <fcntl.h>

typedef struct s_cmd	t_cmd;

typedef struct s_shell{	
	pid_t	pid;
	char	**envp;
	char	**export;
	char	**argv;//
	int		len;
	char	*console_name;
	int		quote;	
	int		arrow;
	int		pipe;
	t_cmd	**cmd_start; // *
}t_shell;

struct	s_cmd
{
	pid_t		pid;
	int			fd[2];
	int			exit_status;
	char		**file;
	char		**argv;//аргументы, которые нам подаются
	struct s_cmd *prev;
	struct s_cmd *next;
	
};

t_shell	g_shell;

/*
**	ENV:
*/
void	init_env(char **prmtrs, t_shell *shell);
char	*get_env_value(t_shell *shell, char *prmtrs);
int		env_prmtrs_exist(t_shell *shell, char *prmtrs);
int		new_env(t_shell *shell, char *str, char **tmp);
void	rewrite_env_prmtrs(t_shell *shell, char *prmtrs, char *join);
int		set_env(t_shell *shell, char *prmtrs, char *value);
void	del_new_env(t_shell *shell, char **tmp, char *prmtrs);
int		del_env(t_shell *shell, char *prmtrs);
/*
**	BUILTINS:
*/

int		builtin_echo(char **argv, int fd);
int		check_n_flag(char *argv, int *flag);
int		builtin_env(t_shell *shell);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(void);
int		check_name(char *name);
int		size_mass(char **envp);
int		max(int a, int b);
int		builtin_export(char **args, t_shell *shell);
int		export_prmtrs(t_shell *shell, char *str);
int		builtin_unset(char **args, t_shell *shell);
int		ft_sym_export(char *str);

void	ft_free(char **mass);
void	sort_tmp_env(char	**tmp, int len);
void	no_args(char **envp, t_shell *shell);

char	**new_envp(char **envp, t_shell *shell);
char	**after_quotes(char **tmpmass, t_shell *shell);
char	**before_quotes(char **tmpmass,	t_shell *shell);


int		builtins(char **argv, t_shell *shell);
int		create_pipe(t_shell *shell, t_cmd *cmd);
int		nofork(char *cmd);
void	pipex(t_shell *shell);
int		execute_execve(t_cmd *cmd, t_shell *shell);
void	handler_signal(int signal);
int		start_cmd_fork(t_cmd *cmd, t_shell *shell);
int		redir_heredoc(char *iter, int fd, t_cmd *cmd, t_shell *shell);
void	heredoc(char *iter, int *fd, t_cmd *cmd, t_shell *shell);
int		check_heredoc(char **redir, int stdin_fd, t_cmd *cmd, t_shell *shell);
int		make_heredocs(t_cmd *cmd, t_shell *shell);
int		redir_heredoc(char *iter, int fd, t_cmd *cmd, t_shell *shell);
void	set_last_status(t_shell *shell, t_cmd *cmd, int status);
int		open_file(char *argv, int i, int quit);
int		check_redirection(t_cmd *cmd, int quit);
/*
** PARSER:
*/

void	free_memory(char *inpt, char *help, char *rez);
int		read_str(char **str);
int		resize_rez(char **inpt, char **rez);
int		init_rez(char **inpt, char **rez);
int		in_cycle(char **rez, char **inpt, int *may_continue);
int		go_on(char *str);
int		substitute_envp(char *input, char **envp);
int		is_space(char c);
int		replace(char **to_change, int i);
char	*find_var(char *what_to_find);
int		set_envp(char **envp);
int		repl_equal(char **to_change, char *repl, int i);
int		repl_more(char **to_change, char *repl, int i, int a);
int		delete_var(char **to_change, int i, int a);
int		repl_less(char **to_change, char *repl, int i, int a);
int		sub_envp(char **to_change, char **repl, int i, int a);
char	**put_str_to_tree(char **str);
int		double_check_inpt(char *inpt);
int		is_arrow(char *str);
int		delete_quote(char **inpt);
int		not_allowed(char c);
char	**get_str(char **envp);

/*
** STUFF:
*/

void	ft_error(char *argv, int exit_code);
void	free_memory(char *inpt, char *help, char *rez);

#endif
