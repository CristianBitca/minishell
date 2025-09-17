/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:23:23 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/17 14:15:52 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// When there has been an error in assigning (e.g bad infile/outfile) this
// function will essentially give a blank process. NULL argv will mean nothing
// will be executed. And intialising infile/outfilefds to stdin/out ensures
// that our pipe handling in execute_all_processes will still run smoothly.
// Nothing will be written into the pipe for the following process, and
// whatever is in the read end of the pipe from the previous process will be
// lost after the pipe is closed.
void	assign_prcs_error(t_data *data, t_prcs *process)
{
	process->argv = NULL;
	process->infilefd = STDIN_FILENO;
	process->outfilefd = STDOUT_FILENO;
	data->exit_status = 1;
	return ;
}

int	assign_prcs(t_data *data, t_token *first, int token_count, int i)
{
	t_prcs	*process;

	data->processes[i] = malloc(sizeof(*(data->processes[i])));
	process = data->processes[i];
	if (convert_here_docs(first, token_count, i) == -1)
	{
		//heredoc will return -1 when interrupted by signal
		//return out of loop completely 
		assign_prcs_error(data, process);
		return (-1);
	}
	process->infilefd = handle_infiles(first, token_count);
	if (process->infilefd == -1)
	{
		assign_prcs_error(data, process);
		return (0);
	}
	process->outfilefd = handle_outfiles(first, token_count);
	if (process->outfilefd == -1)
	{
		assign_prcs_error(data, process);
		return (0);
	}
	process->argv = make_process_argv(data, first, token_count);
	return (0);
}
