/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:00:22 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/16 12:02:50 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handler_signal(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
	if (signal == SIGQUIT)
		write(1, "exit\n", 5);
}

void	ft_exit2(void)
{
	printf("exit\n");
	exit(0);
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
