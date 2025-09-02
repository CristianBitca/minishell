/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:23:23 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/02 11:53:16 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	assign_prcs(t_data *data, t_token *first, int token_count, int prcs_index)
{
	t_prcs	*process;

	data->processes[prcs_index] = malloc(sizeof(*data->processes[prcs_index]));
	process = data->processes[prcs_index];
	if (convert_here_docs(first, token_count, prcs_index) == -1)
		(void)data; // TODO cleanup and return to prompt
	process->infilefd = handle_infiles(first, token_count);
	if (process->infilefd == -1)
		(void)data; // TODO cleanup and return to prompt
	process->outfilefd = handle_outfiles(first, token_count);
	if (process->outfilefd == -1)
		(void)data; // TODO cleanup and return to prompt
	process->argv = make_process_argv(first, token_count);
}
