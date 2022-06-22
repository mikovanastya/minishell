/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:26:43 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/20 16:33:32 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	check_quotes(void)
// {
// 	t_shell	*shell;
// 	int		i;

// 	i = 0;
// 	while (shell->argv[i] != '\0')
// 	{
// 		if (shell->argv[i] == '\'')
// 		{
// 			i++;
// 			while (shell->argv[i] != '\0' && shell->argv[i] != '\'')
// 				i++;
// 			if (shell->argv[i] == '\0')
// 				return (0);
// 		}
// 		if (shell->argv[i] == '"')
// 		{
// 			i++;
// 			while (shell->argv[i] != '\0' && shell->argv[i] != '"')
// 				i++;
// 			if (shell->argv[i] == '\0')
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	check_first_pipe(void)
// {
// 	t_shell	*shell;
// 	int		i;

// 	i = 0;
// 	while (shell->argv[i] != '\0' && shell->argv[i] == ' ')
// 		i++;
// 	if (shell->argv[i] == '|')
// 		return (0);
// 	else
// 		return (1);
// }

// int	check_quots_pipe(void)
// {
// 	t_shell	*shell;

// 	if (!check_quotes())
// 	{
// 		errmsg("minishell: ", g_line.line, ": unclosed quotes", -21);
// 		add_history(shell->argv);
// 		free(shell->argv);
// 		return (1);
// 	}
// 	if (!check_first_pipe())
// 	{
// 		errmsg("minishell: syntax error near unexpected token `|'",
// 			NULL, NULL, -258);
// 		free(shell->argv);
// 		return (1);
// 	}
// 	return (0);
// }
