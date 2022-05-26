/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:02:04 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/17 16:29:51 by rtwitch          ###   ########.fr       */
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
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell
{	
	char	**envp;
	int		len;
	char	*console_name;
	int		quote;	
}	t_shell;

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
/*
** PARSER:
*/

void	free_memory(char *inpt, char *help, char *rez);
int		read_str(char **str);
int		resize_rez(char **inpt, char **rez);
int		init_rez(char **inpt, char **rez);
int		in_cycle(char **inpt, int *may_continue, char **rez);
int		go_on(char *str);

#endif
