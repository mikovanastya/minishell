/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:00:22 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/13 19:12:28 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handler_signal(int signal)
{
	if (signal == SIGINT)//(sigint)interrupt-прерывать c
		write(1, "\n", 1);
	if (signal == SIGQUIT)//выход d
		write(1, "exit\n", 5);
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);//игнорируем сигнал
	signal(SIGQUIT, SIG_IGN);
}

void	handler(int signum)//запускается когда нажимаем enter lib readline
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}
