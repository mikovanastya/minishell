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
int	repl_equal(char **to_change, char *repl, int i)
{
	int	j;

	j = 0;
	while (*(repl + j))
	{
		*(*to_change + i + j) = *(repl  + j);
		j++;
	}
	return(0);
}

int	repl_more(char **to_change, char *repl, int i, int a)
{
	int		j;
	int		b;

	printf("repl more\n");
	b = ft_strlen(repl);
	j = 0;
	while(*(*to_change + i + j + a - b))
	{
		*(*to_change + i + j) = *(*to_change + i + j + a - b);
		j++;
	}
	*(*to_change + i + j) = '\0';
	repl_equal(to_change, repl, i);
	return(0);
}

int	delete_var(char **to_change, int i, int a)
{
	while (*(*to_change + i + a))
	{
		*(*to_change + i) = *(*to_change + i + a);
		i++;
	}
	*(*to_change + i) = '\0';
	return (0);
}

int	repl_less(char **to_change, char *repl, int i, int a)
{
	char	*t;
	int		b;
	int		j;

	b = ft_strlen(repl);
	t = ft_strdup(*to_change);
	// free(*to_change);
	// *to_change = (char *)malloc(sizeof(char *) * (ft_strlen(t) + b - a + 1));
	ft_strlcpy(*to_change, t, ft_strlen(t));
	ft_memset(*to_change + ft_strlen(t), 'g', ft_strlen(t) + b - a + 1);
	j = ft_strlen(t) + b - a;
	while (j - (b - a) > i)
	{
		printf("from %c to %c\n", *to_change[j - b], *to_change[j]);
		*to_change[j - b] = *to_change[j];
		j--;
	}
	repl_equal(to_change, repl, i);
	*(*to_change + ft_strlen(t) + b - a) = '\0';
	//printf("to_change %s\n", *to_change);
	return (0);
}

// 	char	*t;
// 	int		j;
// 	int		b;
// 	char	*h;

// 	h = *to_change;
// 	printf("repl less\n");
// 	b = ft_strlen(repl);
// 	t = ft_strdup(h);
// 	ft_bzero(h, ft_strlen(h));
// 	free(h);
// 	h = (char *)malloc(sizeof(char *) * (ft_strlen(t) + b - a + 1));
// 	if (!h)
// 	{
// 		free(h);
// 		return(0);
// 	}
// 	ft_bzero(h, ft_strlen(t) + b - a - 1);
// 	ft_strlcpy(h, t, ft_strlen(t) + 1);
// 	j = ft_strlen(t) + b - a;
// 	//printf("\n j is %d | b is %d | a is %d | ft_strlen(t) is %zu\n", j, b, a, ft_strlen(t));
// 	free(t);
// 	*(h + j) = '\0';
// 	j--;
// 	while(j - (b - a) > i + a - 1)
// 	{
// 		//printf("%c ", *(*to_change + j - (b - a)));
// 		*(h + j) = *(*to_change + j - (b - a));
// 		j--;
// 	}
// 	*(h + i + j) = '\0';
// 	//repl_equal(&h, repl, i);
// 	j = 0;
// 	while (*(repl + j))
// 	{
// 		*(h + j + i) = *(repl + j);
// 		j++;
// 	}
// 	*to_change = h;
// 	return(0);
// }
/*возвращает на сколько надо двинуться вперед*/
int	replace(char **to_change, int i)
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
	while (ft_isalpha(*(*to_change + i + a)) || *(*to_change + i + a) == '_' || (ft_isdigit(*(*to_change + i + a)) && *(*to_change + i + a) != 1))
		a++;
	var_name = (char *)malloc(sizeof(char) * (a + 1));
	ft_memmove(var_name, *to_change + i + 1, a - 1);
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
	printf("repl %s\n", repl);
	if (repl)
		free(repl);
	if (var_name)
		free(var_name);
	return (rez);
}