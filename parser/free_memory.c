/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eward <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:23:45 by eward             #+#    #+#             */
/*   Updated: 2022/06/22 16:23:46 by eward            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **arr)
{
	if (!arr)
		return ;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	// if (arr)
	// 	free(arr);
}

void	free_list(t_cmd *cmd)
{
	t_cmd	*t;

	while(cmd)
	{
		free_array(cmd->argv);
		t = cmd->next;
		free(cmd);
		cmd = t;
	}
}