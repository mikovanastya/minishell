/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:00:22 by rtwitch           #+#    #+#             */
/*   Updated: 2022/06/27 16:08:58 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handler_signal(int signal)
{
	if (signal == SIGINT)//(sigint)interrupt-прерывать c
		write(1, "\n", 1);
	if (signal == SIGQUIT)//выход d
		write(1, "Quit: 3\n", 8);
}

void	sig_signal(void)
{
	signal(SIGINT, SIG_IGN);//игнорируем сигнал
	signal(SIGQUIT, SIG_IGN);
}
