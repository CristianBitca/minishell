/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:20:51 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/04 10:29:53 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "built_in.h"

// On success execve does not return, so we must get the exit_status of the last
// command in the waitpid command rather than through a return value.
// If execve fails or if the cmd to pass is NULL, we must free all allocated memory
// and exit, because we are in the child process which copies all memory at the time
// of forking.
int	execute_in_child(t_data *data, t_prcs *process)
{
	int		execve_status;
	char	**envp;

	envp = make_envp(data);
	if (dup2(process->outfilefd, STDOUT_FILENO) < 0
		|| dup2(process->infilefd, STDIN_FILENO < 0)
		|| process->argv[0] == NULL)
	{
		perror(NULL);
		free_envp(envp);
		// free all mallocs and exit
		exit (1);
	}
	if (is_built_in(process) == 1)
	{
		execute_built_in(data, process);
		exit(data->exit_status);
	}
	execve_status = execve(process->argv[0], process->argv, envp);
	if (execve_status < 0)
	{
		free_envp(envp);
		// free all mallocs and exit;
	}
	exit(1);
}
