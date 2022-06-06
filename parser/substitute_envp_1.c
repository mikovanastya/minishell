/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_envp_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:14:39 by eward             #+#    #+#             */
/*   Updated: 2022/06/02 15:14:43 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	repl_equal(char *to_change, char *repl, int i)
{
	int	j;

	j = 0;
	while (*(repl + j))
	{
		*(to_change + i + j) = *(repl + j);
		j++;
	}
	return(0);
}

int	repl_more(char *to_change, char *repl, int i, int a)
{
	// char	*t;
	int		j;
	int		b;

	b = ft_strlen(repl);
	j = 0;
	while(*(to_change + i + j + a - b))
	{
		*(to_change + i + j) = *(to_change + i + j + a - b);
		j++;
	}
	*(to_change + i + j) = '\0';
	//  t = ft_strdup(to_change);
	// free(to_change);
	// to_change = (char *)malloc(sizeof(char) * (ft_strlen(t) - (a - ft_strlen(repl))));
	// to_change = ft_strdup(t);
	repl_equal(to_change, repl, i);
	//free(t);
	return(0);
}
int	delete_var()
{
	return (0);
}
/*возвращает на сколько надо двинуться вперед*/
int	replace(char *to_change, int i)
{
	char	*repl;
	int		a;
	char	*var_name;
	int		rez;

	rez = 0;
	a = 0;
	a++;
	var_name = NULL;
	// if (*(to_change + i) == '$') //тут надо сделать замену $$ на pid

	while (ft_isalpha(*(to_change + i + a )) || *(to_change + i + a) == '_' || (ft_isdigit(*(to_change + i + a)) && *(to_change + i + a) != 1))
		a++;
	var_name = (char *)malloc(sizeof(char) * (a + 1));
	ft_memmove(var_name, to_change + i + 1, a - 1);
	repl = find_var(var_name);
	printf("repl %s", repl);
	if (repl == 0)
	{
		delete_var();
		rez = i + 1;
	}
	else if (a == (int)ft_strlen(repl))
	{
		repl_equal(to_change, repl, i);
		rez = i + ft_strlen(repl);
	}
	else if (a > (int)ft_strlen(repl))
	{
	 	repl_more(to_change, repl, i, a);
		rez = i + ft_strlen(repl);
	}
	free(repl);
	free(var_name);
	return (rez);
}