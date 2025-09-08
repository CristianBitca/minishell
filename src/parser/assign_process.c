/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:23:23 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/03 12:38:15 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	assign_prcs(t_data *data, t_token *first, int token_count, int i)
{
	t_prcs	*process;

<<<<<<< HEAD:src/parser/parse_process.c
	pipe_in = 0;
	data->processes[prcs_index] = malloc(sizeof(*data->processes[prcs_index]));
	process = data->processes[prcs_index];
	if (first->prev != NULL && first->prev->type == PIPE)
		pipe_in = 1;
	convert_here_docs(data, token_count, prcs_index);
	process->infilefd = handle_infiles(first, token_count, pipe_in);
=======
	data->processes[i] = malloc(sizeof(*(data->processes[i])));
	process = data->processes[i];
	if (convert_here_docs(first, token_count, i) == -1)
		(void)data; // TODO cleanup and return to prompt
	process->infilefd = handle_infiles(first, token_count);
	if (process->infilefd == -1)
		(void)data; // TODO cleanup and return to prompt
	process->outfilefd = handle_outfiles(first, token_count);
	if (process->outfilefd == -1)
		(void)data; // TODO cleanup and return to prompt
	process->argv = make_process_argv(data, first, token_count);
>>>>>>> skirwan:src/parser/assign_process.c
}
