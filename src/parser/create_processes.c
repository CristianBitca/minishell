/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:44:19 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/19 14:07:45 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// Whenever we see a pipe, we know that we have another process to create
// which will have its own argv, infile and outfile. We start at 1 process
// because the first does not require a pipe. We calloc an extra prcs in the
// array for NULL termination.
int	allocate_processes(t_data *data)
{
	t_token	*traverser;
	int		prcs_count;

	traverser = data->tokens;
	prcs_count = 1;
	while (traverser != NULL)
	{
		if (traverser->type == PIPE)
			prcs_count++;
		traverser = traverser->next;
	}
	data->processes = ft_calloc(prcs_count + 1, sizeof(*data->processes));
	return (prcs_count);
}

void	create_processes(t_data *data)
{
	t_token	*first_process_token;
	t_token	*traverser;
	int		process_token_count;
	int		i;

	allocate_processes(data);
	traverser = data->tokens;
	i = 0;
	while (traverser != NULL)
	{
		process_token_count = 0;
		first_process_token = traverser;
		while (traverser != NULL && traverser->type != PIPE)
		{
			process_token_count++;
			traverser = traverser->next;
		}
		if (traverser != NULL && traverser->type == PIPE)
			process_token_count++;
		assign_prcs(data, first_process_token, process_token_count, i);
		i++;
	}
}
