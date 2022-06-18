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
/*тут читаем строку и склеиваем в одну огромнную*/
int	quote_actions(char c)
{
	if (!g_shell.quote && (c == '\'' || c == '\"'))
	{
		g_shell.quote = c;
		g_shell.console_name = "dquote> ";
	}
	else if (g_shell.quote == c)
	{
		g_shell.quote = '\0';
		g_shell.console_name = "minishell> ";
		if (c == '|')
			return (-1);
	}
	else if (!g_shell.quote && c == '|')
	{
		g_shell.pipe = 1;
		g_shell.quote = c;
		g_shell.console_name = "pipe> ";
	}
	return (1);
}

int	go_on(char *str)
{
	int	go_to_next_str;

	go_to_next_str = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"' || *str == '|'))
			if (quote_actions(*str) == -1)
				return (-1);
		if (g_shell.quote == '|' && *str != '|' && !is_space(*str) && *str && *str != '\n')
			g_shell.pipe = 0;
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
	if ((g_shell.quote == '|' && go_to_next_str == 0) && g_shell.pipe == 0)
	{
		g_shell.quote = '\0';
		g_shell.console_name = "minishell> ";
		g_shell.pipe = 0;
	}
	if (!(*str) && !g_shell.quote && go_to_next_str == 0)
		return (0);
	else
		return (1);
}

void	free_memory(char *inpt, char *help, char *rez)
{
	if (help)
		free(help);
	if (inpt)
		free(inpt);
	if (rez)
		free(rez);
}

int	read_str(char **str)
{
	char	*inpt;
	int		may_continue;
	int		cycle_rez;

	may_continue = 1;
	while (may_continue == 1)
	{
		inpt = readline(g_shell.console_name);
		add_history(inpt);
		cycle_rez = in_cycle(str, &inpt, &may_continue);
		free(inpt);
	}
	return (may_continue);
}
