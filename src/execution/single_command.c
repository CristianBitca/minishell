/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:21:51 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/08 16:54:44 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// If we only have one cmd to execute, a built-in command does not fork.
// We get the exit status from passing the &wstatus pointer to waitpid
// which receives the return value of the command passed to execve.
// Then we set the error code (e.g for 'echo $?') from the wstatus variable
int	single_cmd(t_data *data, t_prcs *process)
{
	int	cpid;
	int	wstatus;

	if (is_built_in(process->argv[0]) == 1)
		return (execute_built_in(data, process));
	else
	{
		cpid = fork();
		if (cpid == 0)
			execute_in_child(data, process);
		else
			waitpid(cpid, &wstatus, 0);
	}
	free(process->argv);
	if (process->infilefd != STDIN_FILENO)
		close(process->infilefd);
	if (process->outfilefd != STDOUT_FILENO)
		close(process->outfilefd);
	if (WIFEXITED(wstatus) == 1)
		data->exit_status = WEXITSTATUS(wstatus);
	return (0);
}
