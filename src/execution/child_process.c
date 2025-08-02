/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:20:51 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/02 17:44:48 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "built_in.h"

// On success execve does not return, so we must get the exit_status of the last
// command in the waitpid command rather than through the return value.
// If execve fails or if the cmd to pass is NULL, we must free all allocated memory
// and exit, because we are in the child process which copies all memory at the time
// of forking.
void	execute_in_child(t_data *data, t_prcs *process)
{
	int		execve_status;
	char	**envp;

	envp = make_envp(data);
	if (process->argv[0] == NULL)
	{
		free_envp(envp);
		// free all mallocs and exit;
		return ;
	}
	execve_status = execve(process->argv[0], process->argv, envp);
	if (execve_status < 0)
	{
		free_envp(envp);
		// free all mallocs and exit;
	}
	return ;
}
