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
	printf("hehe %s", to_change);
	return(0);
}

int	repl_more(char *to_change, char *repl, int i, int a)
{
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
	repl_equal(to_change, repl, i);
	return(0);
}

int	delete_var(char *to_change, int i, int a)
{
	while (*(to_change + i + a))
	{
		*(to_change + i) = *(to_change + i + a);
		i++;
	}
	*(to_change + i) = '\0';
	return (0);
}

int	repl_less(char *to_change, char *repl, int i, int a)
{
	char	*t;
	int		j;
	int		b;

	b = ft_strlen(repl);
	t = ft_strdup(to_change);
	printf("\n repl is  %s \n", repl);
	printf("\n t is  %s \n", t);
	free(to_change);
	to_change = (char *)malloc(sizeof(char) * (ft_strlen(t) + b - a));
	ft_memmove(to_change, t, ft_strlen(t));
	j = ft_strlen(t) + b - a;
	printf("\n j is %d | b is %d | a is %d | ft_strlen(t) is %zu\n", j, b, a, ft_strlen(t));
	free(t);
	*(to_change + j) = '\0';
	j--;
	while(j - (b - a) > i + a - 1)
	{
		printf("%c ", *(to_change + j - (b - a)));
		*(to_change + j) = *(to_change + j - (b - a));
		j--;
	}
	*(to_change + i + j) = '\0';
	printf("\n str is  %s \n", to_change);
	repl_equal(to_change, repl, i);
	return(0);
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

	while (ft_isalpha(*(to_change + i + a)) || *(to_change + i + a) == '_' || (ft_isdigit(*(to_change + i + a)) && *(to_change + i + a) != 1))
		a++;
	var_name = (char *)malloc(sizeof(char) * (a + 1));
	ft_memmove(var_name, to_change + i + 1, a - 1);
	repl = find_var(var_name);
	if (repl == 0)
	{
		delete_var(to_change, i,  a);
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
	else if (a < (int)ft_strlen(repl))
	{
		repl_less(to_change, repl, i, a);
		rez = i + ft_strlen(repl);
	}
	if (repl)
		free(repl);
	if (var_name)
		free(var_name);
	return (rez);
}