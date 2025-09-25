/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:21:51 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/25 15:46:37 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ms_signals.h"

// If we only have one cmd to execute, a built-in command does not fork.
// We get the exit status from passing the &wstatus pointer to waitpid
// which receives the return value of the command passed to execve.
// Then we set the error code (e.g for 'echo $?') from the wstatus variable
int	single_cmd(t_data *data, t_prcs *process)
{
	int	cpid;
	int	wstatus;

	if (process->argv == NULL || process->argv[0] == NULL)
		return (0);
	if (is_built_in(process->argv[0]) == 1)
		return (execute_built_in(data, process));
	else
	{
		parent_sigactions_pre_fork();
		cpid = fork();
		if (cpid == 0)
			execute_in_child(data, process);
		else
			waitpid(cpid, &wstatus, 0);
	}
	if (process->infilefd != STDIN_FILENO)
		close(process->infilefd);
	if (process->outfilefd != STDOUT_FILENO)
		close(process->outfilefd);
	retrieve_child_status(data, wstatus);
	return (0);
}
