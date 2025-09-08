/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:09:46 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/08 16:33:53 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	cleanup_tokens(t_data *data)
{
	t_token	*traverser;
	t_token	*temp;

	if (data->tokens == NULL)
		return ;
	traverser = data->tokens;
	while (traverser != NULL)
	{
		temp = traverser;
		traverser = traverser->next;
		(free(temp->value), free(temp));
	}
	data->tokens = NULL;
}

void	cleanup_processes(t_data *data)
{
	int	i;

	i = 0;
	while (data->processes[i] != NULL)
	{
		free(data->processes[i]);
		i++;
	}
	free(data->processes);
}
