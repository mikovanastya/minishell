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

void	replace(char *to_change)
{
	int	i;

	i = 0;
	i++;
	if (*(to_change + i) == '$')
		
	while (*(to_change + i) && !is_space(*(to_change + i)))
	{

		i++;
	}
}