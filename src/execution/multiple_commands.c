/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:56:04 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/25 15:14:56 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "ms_signals.h"

// If we have multiple processes we use a pipe to transfer data between
// them. If we already have a file redirection input/output does not
// go through the pipe. We know this because the prcs in/outfilefds
// will not match the stdin/out.
// When we are in a prcs other than the first, we dup stdin to come
// from the pipe, and in a prcs other than the last we dup stdout
// into the pipe. We always close the pipefd after duping because we
// now have a fd copy in our process structure, which we always close
// after executing anyway.
// Passed an int either 0 or 1 for duping either in/out so we don't have
// to write separate functions for both.
void	dup_to_pipe(t_prcs *process, int *pipedes, int in_or_out)
{
	if (in_or_out == 0)
	{
		if (process->infilefd == STDIN_FILENO)
			process->infilefd = dup(pipedes[0]);
		close(pipedes[0]);
	}
	if (in_or_out == 1)
	{
		if (process->outfilefd == STDOUT_FILENO)
			process->outfilefd = dup(pipedes[1]);
		close(pipedes[1]);
	}
}

int	create_pipe(t_prcs *process, int *pipedes)
{
	if (pipe(pipedes) == -1)
	{
		perror(NULL);
		return (-1);
	}
	dup_to_pipe(process, pipedes, 1);
	return (0);
}

void	close_fds_post_exe(t_prcs *process, int *pipedes)
{
	close(pipedes[1]);
	if (process->infilefd != STDIN_FILENO)
		close(process->infilefd);
	if (process->outfilefd != STDOUT_FILENO)
		close(process->outfilefd);
}

// Takes the number of processes we need to execute, forks for each process
// and executes the commands in the child.
int	execute_all_processes(t_data *data, int prcs_count)
{
	int	pipedes[2];
	int	*cpids;
	int	prcs;

	cpids = malloc(prcs_count * sizeof(*cpids));
	prcs = 0;
	while (prcs < prcs_count)
	{
		if (prcs != 0)
			dup_to_pipe(data->processes[prcs], pipedes, 0);
		if (prcs + 1 < prcs_count
			&& create_pipe(data->processes[prcs], pipedes) == -1)
			return (-1);
		parent_sigactions_pre_fork();
		cpids[prcs] = fork();
		if (cpids[prcs] == 0)
		{
			close(pipedes[0]);
			execute_in_child(data, data->processes[prcs]);
		}
		close_fds_post_exe(data->processes[prcs], pipedes);
		prcs++;
	}
	(wait_on_processes(data, cpids, prcs_count), free(cpids));
	return (0);
}
