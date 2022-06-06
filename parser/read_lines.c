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
	char	*rez;
	int		cycle_rez;

	may_continue = 1;
	rez = NULL;
	while (may_continue == 1)
	{
		inpt = readline(g_shell.console_name);
		add_history(inpt);
		cycle_rez = in_cycle(&rez, &inpt, &may_continue);
		free(inpt);
		//replace("   $USER skdggk", 3);
	}
	*str = rez;
	return (0);
}
