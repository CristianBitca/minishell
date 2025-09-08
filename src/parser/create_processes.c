/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:44:19 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/28 13:53:34 by skirwan          ###   ########.fr       */
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

int	count_processes(t_data *data)
{
	int	prcs_count;

	prcs_count = 0;
	while (data->processes[prcs_count] != NULL)
		prcs_count++;
	return (prcs_count);
}

void	create_processes(t_data *data)
{
	t_token	*first_process_token;
	t_token	*traverser;
	int		token_count;
	int		i;

	allocate_processes(data);
	traverser = data->tokens;
	i = 0;
	while (traverser != NULL)
	{
		token_count = 0;
		first_process_token = traverser;
		while (traverser != NULL && traverser->type != PIPE)
		{
			token_count++;
			traverser = traverser->next;
		}
		if (traverser != NULL && traverser->type == PIPE)
		{
			token_count++;
			traverser = traverser->next;
		}
		assign_prcs(data, first_process_token, token_count, i);
		i++;
	}
}
