/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:46:36 by skirwan           #+#    #+#             */
/*   Updated: 2025/07/29 16:57:39 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "built_in.h"
#include "execution.h"

int	is_built_in(t_data *data, t_prcs *process)
{
	if (ft_strncmp(process->argv[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "cd", 2) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "unset", 5) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "env", 3) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "exit", 4) == 0)
		return (1);
	return (0);
}

int	execute_built_in(t_data *data, t_prcs *process)
{
	if (ft_strncmp(process->argv[0], "echo", 4) == 0)
		echo(process->argv);
	if (ft_strncmp(process->argv[0], "cd", 2) == 0)
		cd(data, process->argv);
	if (ft_strncmp(process->argv[0], "pwd", 3) == 0)
		pwd();
	if (ft_strncmp(process->argv[0], "export", 6) == 0)
		export(data, process->argv);
	if (ft_strncmp(process->argv[0], "unset", 5) == 0)
		unset(data, process->argv);
	if (ft_strncmp(process->argv[0], "env", 3) == 0)
		print_envp(data);
	if (ft_strncmp(process->argv[0], "exit", 4) == 0)
		print_envp(data); // should be exit
	return (0);
}

void	single_cmd(t_data *data, t_prcs *process)
{
	int	stdin_placeholder;
	int	stdout_placeholder;

	stdin_placeholder = dup(0);
	stdout_placeholder = dup(1);
	if (dup2(process->infilefd, 0) == -1
		|| dup2(process->outfilefd, 1) == -1
		|| stdin_placeholder == -1
		|| stdout_placeholder == -1)
	{
		perror(NULL);
		data->exit_status = 1;
	}
	if (is_built_in(data, process) == 1)
		return ;
	else
		;
}
