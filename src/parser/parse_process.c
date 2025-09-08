/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:23:23 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/28 15:24:45 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	assign_prcs(t_data *data, t_token *first, int token_count, int prcs_index)
{
	t_prcs	*process;
	int		pipe_in;
	// int		pipe_out;

	pipe_in = 0;
	data->processes[prcs_index] = malloc(sizeof(*data->processes[prcs_index]));
	process = data->processes[prcs_index];
	if (first->prev != NULL && first->prev->type == PIPE)
		pipe_in = 1;
	convert_here_docs(data, token_count, prcs_index);
	process->infilefd = handle_infiles(first, token_count, pipe_in);
}
