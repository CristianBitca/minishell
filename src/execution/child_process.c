/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:20:51 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/04 11:44:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "built_in.h"

// On success execve does not return, so we must get the exit_status of the last
// command in the waitpid command rather than through a return value.
// If our command is a built in, we do not call execve and exit with the status
// our built in changes in the data struct.
// If our dup2 of infile/outfile is unsuccessful, or we cannot find/execute
// the command to be executed (it was not found in the PATH during parsing)
// we must free all allocated memory and exit, because we are in the
// child process which copies all memory at the time of forking.
// If successful execve will commandeer the whole process with the command
// passed to execute, and will exit with the status of that command. If execve
// returns it has failed, so we will free and exit again with EXIT_FAILURE
int	execute_in_child(t_data *data, t_prcs *process)
{
	int		execve_status;
	char	**envp;

	if (dup2(process->outfilefd, STDOUT_FILENO) < 0
		|| dup2(process->infilefd, STDIN_FILENO < 0))
	{
		perror(NULL);
		// free all mallocs, close all fds and exit
		exit (EXIT_FAILURE);
	}
	if (is_built_in(process) == 1)
	{
		execute_built_in(data, process);
		// free all mallocs, close all fds and exit
		exit(data->exit_status);
	}
	if (access(process->argv[0], F_OK | X_OK) != 0)
	{
		write (2, process->argv[0], ft_strlen(process->argv[0]));
		write (2, ": command not found\n", 21);
		// free all mallocs, close all fds and exit
		exit (127);
	}
	envp = make_envp(data);
	execve_status = execve(process->argv[0], process->argv, envp);
	if (execve_status < 0)
	{
		free_envp(envp);
		// free all mallocs, close all fds and exit;
	}
	exit (EXIT_FAILURE);
}
