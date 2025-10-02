/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:20:51 by skirwan           #+#    #+#             */
/*   Updated: 2025/10/02 19:56:25 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "built_in.h"
#include "ms_signals.h"
#include <unistd.h>

void	child_prcs_file_handling(t_data *data, t_prcs *process)
{
	if (dup2(process->infilefd, STDIN_FILENO) < 0
		|| dup2(process->outfilefd, STDOUT_FILENO) < 0)
	{
		perror(NULL);
		full_exit(data, 1);
	}
	if (process->infilefd != STDIN_FILENO)
		close(process->infilefd);
	process->infilefd = STDIN_FILENO;
	if (process->outfilefd != STDOUT_FILENO)
		close(process->outfilefd);
	process->outfilefd = STDOUT_FILENO;
	return ;
}

void	current_wd_file_permission_check(t_data *data, char *cmd)
{
	if (access(cmd, X_OK) == -1)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": Permission denied\n", 21);
		full_exit(data, 126);
	}
	return ;
}

void	child_prcs_check_exe(t_data *data, t_prcs *process)
{
	char	*cmd;

	cmd = process->argv[0];
	if (ft_strchr(cmd, '/') == NULL)
	{
		if (access(cmd, F_OK) == -1)
			write (STDERR_FILENO, cmd, ft_strlen(cmd));
		if (find_env(data->env, "PATH") != NULL)
			write(STDERR_FILENO, ": command not found\n", 21);
		else if (access(cmd, F_OK) == 0)
			return (current_wd_file_permission_check(data, cmd));
		else
		   write(STDERR_FILENO, ": No such file or directory\n", 29);
		full_exit(data, 127);
	}
	else if (access(cmd, F_OK) == -1)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		full_exit(data, 127);
	}
}

// On success execve does not return, so we must get the exit_status of the last
// command in the waitpid command rather than through a return value.
// If our command is a built in, we do not call execve and exit with the status
// our built in changes in the data struct.
// If our dup2 of infile/outfile is unsuccessful, or we cannot find/execute
// the command to be executed (it was not found in the PATH during parsing)
// we must free all allocated memory and exit, because we are in the
// child process which copies all memory at the time of forking.
// When a command which is a valid path but is not executable (either is 
// a directory or has insufficient permissions, we return NULL when we 
// create the command. The correct exit code for this scenario is 126)
// If successful execve will commandeer the whole process with the command
// passed to execute, and will exit with the status of that command. If execve
// returns it has failed, so we will free and exit again with EXIT_FAILURE
void	execute_in_child(t_data *data, t_prcs *process)
{
	int		execve_status;
	char	**envp;

	sig_actions_default();
	if (process->argv == NULL)
		full_exit(data, 1);
	if (process->argv[0] == NULL)
		full_exit(data, 126);
	child_prcs_file_handling(data, process);
	if (is_built_in(process->argv[0]) == 1)
	{
		execute_built_in(data, process);
		full_exit(data, -4242);
	}
	child_prcs_check_exe(data, process);
	envp = make_envp(data);
	execve_status = execve(process->argv[0], process->argv, envp);
	if (execve_status < 0)
		(free_envp(envp), full_exit(data, 1));
}
