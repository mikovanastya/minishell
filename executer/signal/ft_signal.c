/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:00:22 by rtwitch           #+#    #+#             */
/*   Updated: 2022/07/15 21:24:46 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ms_check_exit_arg(char *arg)
{
	int			i;
	long long	exit_code;

	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", arg);
		g_shell.cmd_start->exit_status = 255;
		return (1);
	}
	exit_code = ft_atoll(arg);
	g_shell.cmd_start->exit_status = exit_code % 256;
	if (g_shell.cmd_start->exit_status < 0 ||g_shell.cmd_start->exit_status > 255)
		g_shell.cmd_start->exit_status = 255;
	return (0);
}

void	handler_signal(int signal)
{
	if (signal == SIGINT)//(sigint)interrupt-прерывать c
		write(1, "\n", 1);
	if (signal == SIGQUIT)//выход d
		write(1, "exit\n", 5);
}

void ft_exit2(){
	printf("exit\n");
	exit(0);
}

void	sig_sig_signal(void)
{
	signal(SIGINT, SIG_IGN);//игнорируем сигнал
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handler(int signum)//запускается когда нажимаем enter lib readline
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

