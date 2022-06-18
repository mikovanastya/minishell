/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:07:52 by eward             #+#    #+#             */
/*   Updated: 2022/06/18 14:07:54 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// &
// | +
// > 1
// >> 2
// < 3
// << 4

// int	service_symbol(char **str)
// {

// }

int	count_elements(char **str)
{
	int	n;
	int	i;

	n = 1;
	i = 0;
	while (*(*str + i))
	{
		while (is_space(*(*str + i)))
			i++;
		if (*(*str + i))
			n++;
		while (!is_space(*(*str + i)) && *(*str + i))
			i++;
	}
	return (n);
}

int	put_str_to_tree(char **str)
{
	int	num;

	num = count_elements(str);
	printf("num %d\n", num);
	return (0);
}