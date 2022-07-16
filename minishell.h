/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:02:04 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 17:58:54 by rtwitch          ###   ########.fr       */
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
# include <signal.h>
# include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_cmd	t_cmd;

typedef struct s_shell{	
	pid_t	pid;
	char	**envp;
	int		len;
	char	*console_name;
	int		quote;	
	int		arrow;
	int		pipe;
	char	*inpt;
	t_cmd	*cmd_start;
}t_shell;

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}					t_list;

struct	s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	pid_t			pid;
	int				fd[2];
	char			**file_name;
	int				exit_status;
	char			*redir;
	char			**argv;
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
int		del_env(char *prmtrs);
void	del_new_env(char **tmp, char *prmtrs);
char	*get_env_value(char *prmtrs);
void	init_env(char **prmtrs);
int		env_prmtrs_exist(char *prmtrs);
int		new_env(char *str);
void	rewrite_env_prmtrs(char *prmtrs, char *join);
int		set_env(char *prmtrs, char *value);
/*
**	BUILTINS:
*/

int		builtin_echo(int fd);
int		check_n_flag(char *argv, int *flag);
int		builtin_env(void);
int		builtin_cd(void);
int		builtin_pwd(void);
int		check_name(char *name);
int		size_mass(char **envp);
int		max(int a, int b);
int		builtin_export(void);
int		export_prmtrs(char *str);
int		builtin_unset(void);
int		ft_sym_export(char *str);
void	ft_free(char **mass);
void	sort_tmp_env(char	**tmp);
void	no_args(void);
char	**new_envp(void);
char	**after_quotes(char **tmpmass );
char	**before_quotes(char **tmpmass);
int		builtins(void);
int		create_pipe(void);
int		nofork(char *cmd);
void	pipex(void);
int		start_cmd_nofork(void);
int		execute_execve_without_path(char **path_arr);
int		execute_execve(void);
void	handler_signal(int signal);
int		start_cmd_fork(void);
void	set_last_status(int status);
int		open_file(char *argv, int i, int quit);
int		check_redirection(int quit);
void	sig_sig_signal(void);
void	ft_handler(int signum);
/*
** PARSER:
*/

void	free_memory(char *inpt, char *help, char *rez);
int		read_str(char **str);
int		resize_rez(char **inpt, char **rez);
int		init_rez(char **rez, char **inpt);
void	init_redir(t_cmd **redir_cmd, t_list *tokens,
			char **argv, char **file_name);
int		check_input(char **rez, char **inpt, int *may_continue);
int		go_on(char *str);
int		substitute_envp(char *input);
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
int		is_a(char *str);
int		delete_quote(char **inpt);
int		n_a(char c);
char	*get_str(void);
void	free_array(char **arr);
void	skip_quotes(char *input, int *i);
int		fill_list(char	*str);
int		add_elem(t_cmd **cmd, char **str);
int		word_len(char *str);
int		arrow_action(char **str, t_cmd **cmd);
int		separate_str(char ***arr, char **str, t_cmd	*cmd);
int		go_to_word(char **a, int *j, char **str);
int		print_token_err(char c);
int		parse_heredoc(char *delim);
int		add_filename(t_cmd	*cmd, char **str, char **a);
int		add_more(char **str, t_cmd *cmd, int i);
int		create_element(t_for_array	*pos, char **str, char ***arr,
			t_cmd	*cmd);
int		count_filenames(char *str, char *first);
/*
** STUFF:
*/

void	ft_error(char *argv, int exit_code);
void	free_memory(char *inpt, char *help, char *rez);
void	init_redir(t_cmd **redir_cmd, t_list *tokens,
			char **argv, char **file_name);
void	ft_copy_argv(char **argv, char *tokens, int type);
void	ex_cmd_add_back(t_cmd **ex_cmd, t_cmd *new);
t_cmd	*new_ex_cmd(char **argv, char **file);
void	copy_end(char **argv, char **file, t_cmd **ex_cmd);
void	ft_exit2(void);
void	ft_exit(void);
int		ms_check_exit_arg(char *arg);

#endif
