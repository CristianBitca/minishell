/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaping_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:14:12 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/25 15:56:20 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	retrieve_child_status(data, wstatus);
}

void	retrieve_child_status(t_data *data, int wstatus)
{
	int	terminating_signal;

	if (WIFEXITED(wstatus) == 1)
		data->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus) == 1)
	{
		terminating_signal = WTERMSIG(wstatus);
		if (terminating_signal == 2)
		{
			write(1, "\n", 1);
			data->exit_status = 130;
		}
		else if (terminating_signal == 3)
		{
			write(2, "Quit (core dumped)\n", 20);
			data->exit_status = 131;
		}
	}
}
