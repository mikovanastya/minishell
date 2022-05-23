/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:28:10 by rtwitch           #+#    #+#             */
/*   Updated: 2022/05/16 13:27:55 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	builtin_env(char **words, t_env *env, int fd)
int	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		printf("%s\n", shell->envp[i++]);
	return (0);
}
