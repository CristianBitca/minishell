/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:46:36 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/08 17:56:36 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "built_in.h"
#include "execution.h"

int	is_built_in(t_prcs *process)
{
	if (ft_strncmp(process->argv[0], "echo\0", 5) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "cd\0", 3) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "pwd\0", 4) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "export\0", 7) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "unset\0", 6) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "env\0", 4) == 0)
		return (1);
	if (ft_strncmp(process->argv[0], "exit\0", 5) == 0)
		return (1);
	return (0);
}

int	execute_built_in(t_data *data, t_prcs *process)
{
	if (ft_strncmp(process->argv[0], "echo\0", 5) == 0)
		echo(process->argv, process->outfilefd);
	if (ft_strncmp(process->argv[0], "cd\0", 3) == 0)
		cd(data, process->argv);
	if (ft_strncmp(process->argv[0], "pwd\0", 4) == 0)
		pwd(process->outfilefd);
	if (ft_strncmp(process->argv[0], "export\0", 7) == 0)
		export(data, process->argv, process->outfilefd);
	if (ft_strncmp(process->argv[0], "unset\0", 6) == 0)
		unset(data, process->argv);
	if (ft_strncmp(process->argv[0], "env\0", 4) == 0)
		print_envp(data, process->outfilefd);
	if (ft_strncmp(process->argv[0], "exit\0", 5) == 0)
		print_envp(data, process->outfilefd); // should be exit
	return (0);
}
