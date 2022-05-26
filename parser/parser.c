/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:45:31 by eward             #+#    #+#             */
/*   Updated: 2022/05/18 17:45:32 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_actions(char c)
{
	if (!g_shell.quote)
	{
		g_shell.quote = c;
		g_shell.console_name = "dquote> ";
	}
	else if (g_shell.quote == c)
	{
		g_shell.quote = '\0';
		g_shell.console_name = "minishell> ";
	}
}

int	go_on(char *str)
{
	int	go_to_next_str;

	go_to_next_str = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			quote_actions(*str);
		if (*str == '\\')
		{
			if (!*(str + 1))
				go_to_next_str = 1;
			while (*(str + 1))
			{
				*str = *(str + 1);
				str++;
			}
			*str = '\0';
		}
		str++;
	}
	if (!(*str) && !g_shell.quote && go_to_next_str == 0)
		return (0);
	else
		return (1);
}

int	read_str(char *rez)
{
	char	*inpt;
	int		may_continue;
	char	*help;

	may_continue = 1;
	rez = NULL;
	while (may_continue == 1)
	{
		inpt = readline(g_shell.console_name);
		add_history(inpt);
		if (!rez)
		{
			rez = (char *)malloc(sizeof(char *) * (ft_strlen(inpt) + 1));
			if (!rez)
				return (-1);
			ft_bzero(rez, ft_strlen(inpt));
		}
		else
		{
			if (help)
				free(help);
			help = (char *)malloc(sizeof(char *) * (ft_strlen(rez) + 1));
			ft_bzero(help, ft_strlen(rez) + 1);
			rez[ft_strlen(rez)] = '\0';
			if (ft_strlcpy(help, rez, ft_strlen(rez) + 1) < 0)
				return (-2);
			free(rez);
			rez = (char *)malloc(sizeof(char *) * (ft_strlen(inpt)
						+ ft_strlen(help) + 1));
			if (!rez)
				return (-1);
			ft_bzero(rez, ft_strlen(inpt) + ft_strlen(help));
			if (ft_strlcpy(rez, help, ft_strlen(help) + 1) < 0)
				return (-2);
		}
		may_continue = go_on(inpt);
		if (ft_strlcat(rez, inpt, ft_strlen(inpt) + ft_strlen(rez) + 1) < 0)
			return (-2);
		free(inpt);
	}
	printf("!!! result %s \n", rez);
	return (0);
}
