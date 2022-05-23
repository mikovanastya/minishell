/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:02:04 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/23 18:55:22 by rtwitch          ###   ########.fr       */
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
//#include <sys/cdefs.h>
# include <readline/readline.h>
# include "string.h" // !! УДАЛИТЬ !!!*

typedef struct s_shell
{	
	char	**envp;
	char	**export;
	int	len;
}	t_shell;



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

// int	builtin_export(char **args, t_shell *shell);
//int	builtin_cd(char **arg, t_shell *shell);


int	size_mass(char **envp);
int	max(int a, int b);
char	**replace_envp_el(t_shell *shell, char *args, char *new);
void	change_envp(char *new, char **args, int i, t_shell *shell);
int	ft_sym_export(char *str);
char	*check_double(char *args, char **envp);
void	ft_free(char **mass);
char	**after_quotes(char **tmpmass, t_shell *shell);
char	**before_quotes(char **tmpmass,	t_shell *shell);
void	sort_tmp_env(char	**tmp, int len);
void	no_args(char **envp, t_shell *shell);
char    **new_envp(char **envp, t_shell *shell);
int builtin_export(char **args, t_shell *shell);
char	**export_envp(char **envp, char *str, int free);

#endif
