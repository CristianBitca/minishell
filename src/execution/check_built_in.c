/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:46:36 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/10 12:04:57 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"
#include "execution.h"
#include <unistd.h>

int	is_built_in(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp(cmd, "echo\0", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd\0", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export\0", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset\0", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit\0", 5) == 0)
		return (1);
	return (0);
}

int	execute_built_in(t_data *data, t_prcs *process)
{
	if (ft_strncmp(process->argv[0], "echo\0", 5) == 0)
		echo(data, process->argv, process->outfilefd);
	if (ft_strncmp(process->argv[0], "cd\0", 3) == 0)
		cd(data, process->argv, process->outfilefd);
	if (ft_strncmp(process->argv[0], "pwd\0", 4) == 0)
		pwd(data, process->outfilefd);
	if (ft_strncmp(process->argv[0], "export\0", 7) == 0)
		export(data, process->argv, process->outfilefd);
	if (ft_strncmp(process->argv[0], "unset\0", 6) == 0)
		unset(data, process->argv);
	if (ft_strncmp(process->argv[0], "env\0", 4) == 0)
		print_envp(data, process->outfilefd);
	if (process->infilefd != STDIN_FILENO)
		close(process->infilefd);
	if (process->outfilefd != STDOUT_FILENO)
		close(process->outfilefd);
	if (ft_strncmp(process->argv[0], "exit\0", 5) == 0)
		full_exit(data, -1);
	return (0);
}
