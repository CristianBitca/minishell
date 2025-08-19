/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:56:04 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/04 10:35:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// Takes the number of processes we need to execute, forks for each process
// and executes the commands in the child. After all the child processes are
// created, then we wait on each one with waitpid (not waiting for each one
// to die and then forking the following process). We hold the exit status
// of each successive child process in wstatus, which is changed by waitpid
// but we only save the final exit status in our struct.
void	execute_all_processes(t_data *data, int prcs_count)
{
	int	wstatus;
	int	*cpids;
	int	i;

	cpids = malloc(prcs_count * sizeof(*cpids));
	i = 0;
	while (i < prcs_count)
	{
		cpids[i] = fork();
		if (cpids[i] == 0)
			execute_in_child(data, data->processes[i]);
		i++;
	}
	i = 0;
	while (i < prcs_count)
	{
		waitpid(cpids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus) == 1)
		data->exit_status = WEXITSTATUS(wstatus);
}
