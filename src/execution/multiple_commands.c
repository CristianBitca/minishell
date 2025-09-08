/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:56:04 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/08 16:42:15 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// After all the child processes are created, then we wait on each one with
// waitpid (not waiting for each one to die and then forking the 
// following process). We hold the exit status of each successive child
// process in wstatus, which is changed by waitpid but we only save the final
// exit status in our struct.
void	wait_on_processes(t_data *data, int *cpids, int prcs_count)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i < prcs_count)
	{
		waitpid(cpids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus) == 1)
		data->exit_status = WEXITSTATUS(wstatus);
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
		{
			if (data->processes[prcs]->infilefd == STDIN_FILENO)
				data->processes[prcs]->infilefd = dup(pipedes[0]);
			close(pipedes[0]);
		}
		if (prcs + 1 < prcs_count)
		{
			if (pipe(pipedes) == -1)
			{
				perror(NULL);
				return (-1);
			}
			if (data->processes[prcs]->outfilefd == STDOUT_FILENO)
				data->processes[prcs]->outfilefd = dup(pipedes[1]);
			close(pipedes[1]);
		}
		cpids[prcs] = fork();
		if (cpids[prcs] == 0)
		{
			close(pipedes[0]);
			execute_in_child(data, data->processes[prcs]);
		}
		close(pipedes[1]);
		if (data->processes[prcs]->infilefd != STDIN_FILENO)
			close(data->processes[prcs]->infilefd);
		if (data->processes[prcs]->outfilefd != STDOUT_FILENO)
			close(data->processes[prcs]->outfilefd);
		free(data->processes[prcs]->argv);
		prcs++;
	}
	(wait_on_processes(data, cpids, prcs_count), free(cpids));
	return (0);
}
