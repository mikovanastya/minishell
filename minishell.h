/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:02:04 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 20:39:06 by rtwitch          ###   ########.fr       */
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
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
// # include "readline/tilde.h"
// # include "readline/rlconf.h"
// # include "readline/rlstdc.h"
# include "readline/history.h"
// # include "readline/keymaps.h"
# include "readline/readline.h"
// # include "readline/chardefs.h"
// # include "readline/rltypedefs.h"
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
	char	*inpt;
	t_cmd	**cmd_start; // *
}t_shell;

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}					t_list;

struct	s_cmd
{
	pid_t		pid;
	char		**bin_path;
	int			fd[2];
	char		**file_name;
	int			exit_status;
	char		**redir;//
	char		**argv;//аргументы, которые нам подаются команды
	struct s_cmd *prev;
	struct s_cmd *next;
	
};

typedef struct s_for_array
{
	char	**rez;
	int		num;
	int		i;
	int		j;
	int		k;
}t_for_array;

t_shell	g_shell;

/*
**	ENV:
*/
void	init_env(char **prmtrs);
char	*get_env_value(char *prmtrs);
int		env_prmtrs_exist(char *prmtrs);
int		new_env(char *str);
void	rewrite_env_prmtrs(char *prmtrs, char *join);
int		set_env(char *prmtrs, char *value);
void	del_new_env(char **tmp, char *prmtrs);
int		del_env(char *prmtrs);
/*
**	BUILTINS:
*/

int		builtin_echo(char **argv, int fd);
int		check_n_flag(char *argv, int *flag);
int		builtin_env(void);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		check_name(char *name);
int		size_mass(char **envp);
int		max(int a, int b);
int		builtin_export(char **args);
int		export_prmtrs(char *str);
int		builtin_unset(char **args);
int		ft_sym_export(char *str);

void	ft_free(char **mass);
void	sort_tmp_env(char	**tmp);
void	no_args(void);

char	**new_envp(void);
char	**after_quotes(char **tmpmass );
char	**before_quotes(char **tmpmass);


int		builtins(char **argv);
int		create_pipe();
int		nofork(char *cmd);
void	pipex();
int execute_execve();
void	handler_signal(int signal);
int		start_cmd_fork();
int		redir_heredoc();
void	heredoc();
int		check_heredoc();
int		make_heredocs();
void	set_last_status(int status);
int		open_file(char *argv, int i, int quit);
int		check_redirection(int quit);
int		ft_free_str(char **s);
void	*ft_free_str_arr(char ***arr);
int	ft_builtin(t_cmd *cmd);
void	sig_sig_signal(void);
void	r_in();
// void	handler(int signum);
/*
** PARSER:
*/

void	free_memory(char *inpt, char *help, char *rez);
int		read_str(char **str);
int		resize_rez(char **inpt, char **rez);
//int		init_rez(char **inpt, char **rez);
int		init_rez(char **rez, char **inpt);
void	init_redir(t_cmd **redir_cmd, t_list *tokens,
		char **argv, char **file_name);
int		in_cycle(char **rez, char **inpt, int *may_continue);
int		go_on(char *str);
int		substitute_envp(char *input, char **envp);
int		sp(char c);
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
int		is_a(char *str);
int		delete_quote(char **inpt);
int		n_a(char c);
char	*get_str(char **envp);
void	free_array(char **arr);
void	skip_quotes(char *input, int *i);
void	fill_list(char	*str);
int		add_elem(t_cmd **cmd, char **str);
int		word_len(char *str);
int     arrow_action(char **str, t_cmd  **cmd);
int	separate_str(char ***arr, char **str, t_cmd	*cmd);
int	go_to_word(char **a, int *j, char **str);
/*
** STUFF:
*/

void	ft_error(char *argv, int exit_code);
void	free_memory(char *inpt, char *help, char *rez);

int	type_check(int type);
// static int	ft_count_argv(t_list *tokens);
// static int	ft_count_file(t_list *tokens);
void	init_redir(t_cmd **redir_cmd, t_list *tokens,
		char **argv, char **file_name);
// void	ft_copy_file(char **file, char *tokens, int type);
void	ft_copy_argv(char **argv, char *tokens, int type);
void	ex_cmd_add_back(t_cmd **ex_cmd, t_cmd *new);
t_cmd	*new_ex_cmd(char **argv, char **file);
void	copy_end(char **argv, char **file, t_cmd **ex_cmd);

#endif
