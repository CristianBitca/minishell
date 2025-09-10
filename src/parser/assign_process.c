/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:23:23 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/10 12:20:57 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "minishell.h"
#include "parser.h"

int	assign_prcs_error(t_data *data)
{
	(cleanup_tokens(data), cleanup_processes(data));
	data->exit_status = 1;
	return (-1);
}

int	assign_prcs(t_data *data, t_token *first, int token_count, int i)
{
	t_prcs	*process;

	data->processes[i] = malloc(sizeof(*(data->processes[i])));
	process = data->processes[i];
	if (convert_here_docs(first, token_count, i) == -1)
		return (assign_prcs_error(data));
	process->infilefd = handle_infiles(first, token_count);
	if (process->infilefd == -1)
		return (assign_prcs_error(data));
	process->outfilefd = handle_outfiles(first, token_count);
	if (process->outfilefd == -1)
		return (assign_prcs_error(data));
	process->argv = make_process_argv(data, first, token_count);
	return (0);
}
