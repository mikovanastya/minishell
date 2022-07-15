/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:45:31 by eward             #+#    #+#             */
/*   Updated: 2022/07/15 20:50:45 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*тут читаем строку и склеиваем в одну огромнную*/

int	quote_actions(char c)
{
	if ((!g_shell.quote || g_shell.quote == '|') && (c == '\'' || c == '\"'))
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
		g_shell.console_name = "> ";
	}
	return (1);
}

void	resume_input_if_pipe_or_slash(char **str, int *go_to_next_str)
{
	if (g_shell.quote == '|' && **str != '|'
		&&!sp(**str) && **str && **str != '\n')
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

int	decision_about_quotes(char **str, int *go_to_next_str)
{
	while (**str)
	{
		if (is_a(*str) && !g_shell.quote)
			g_shell.arrow = is_a(*str);
		if ((**str == '\'' || **str == '\"' || **str == '|'))
		{
			if (**str == '|' && g_shell.arrow)
			{
				(*str)--;
				while (!is_a(*str) && sp(**str))
					(*str)--;
				if (is_a(*str))
					// return (2 * print_token_err('|'));
					return (2 * print_token_err('6'));
				while (**str && **str != '|')
					(*str)++;
			}
			if (quote_actions(**str) == -1)
				return (-1);
		}
		resume_input_if_pipe_or_slash(str, go_to_next_str);
	}
	return (0);
}

int	go_on(char *str)
{
	int	go_to_next_str;
	int	decision;

	go_to_next_str = 0;
	decision = decision_about_quotes(&str, &go_to_next_str);
	if (decision < 0)
		return (decision);
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler);
		inpt = readline(g_shell.console_name);
		if (!inpt)
			ft_exit2();
		if (inpt == NULL)
			exit(1);
		add_history(inpt);
		cycle_rez = check_input(str, &inpt, &may_continue);
		free(inpt);
	}
	return (may_continue);
}
