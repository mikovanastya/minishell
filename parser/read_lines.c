/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:45:31 by eward             #+#    #+#             */
/*   Updated: 2022/06/23 18:39:37 by rtwitch          ###   ########.fr       */
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

int	decision_about_quotes(char **str, int *go_to_next_str)
{
	while (**str)
	{
		if (is_arrow(*str))
			g_shell.arrow = is_arrow(*str);
		if ((**str == '\'' || **str == '"' || **str == '|'))
			if (quote_actions(**str) == -1)
				return (-1);
		if (g_shell.quote == '|' && **str != '|'
			&&!is_space(**str) && **str && **str != '\n')
			g_shell.pipe = 0;
		if (**str == '\\')
		{
			if (!*(*str + 1))
				*go_to_next_str = 1;
			while (*(*str + 1))
			{
				**str = *(*str + 1);
				(*str)++;
			}
			**str = '\0';
		}
		(*str)++;
	}
	return (0);
}

int	go_on(char *str)
{
	int	go_to_next_str;

	go_to_next_str = 0;
	if (decision_about_quotes(&str, &go_to_next_str) == -1)
		return (-1);
	if (g_shell.quote == '|' && go_to_next_str == 0 && g_shell.pipe == 0)
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
