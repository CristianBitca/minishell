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

#include "libft.h"
#include "minishell.h"
#include "built_in.h"
#include "execution.h"

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

void	execute_env(t_data *data, t_prcs *process)
{
	if (process->argv[1])
	{
		write(2, "env: '", 6);
		write(2, process->argv[1], ft_strlen(process->argv[1]));
		write(2, "': No such file or directory\n", 30);
		data->exit_status = 127;
	}
	else
		print_envp(data, process->outfilefd);
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
		execute_env(data, process);
	if (process->infilefd != STDIN_FILENO)
		close(process->infilefd);
	if (process->outfilefd != STDOUT_FILENO)
		close(process->outfilefd);
	if (ft_strncmp(process->argv[0], "exit\0", 5) == 0)
		execute_exit(data, process);
	return (0);
}
