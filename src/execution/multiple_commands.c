/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:56:04 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/04 10:35:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_all_processes(t_data *data, int prcs_count)
{
	int	wstatus;
	int	*cpids;
	int	i;

	cpids = malloc(prcs_count * sizeof(*cpids));
	i = 0;
	while (i < prcs_count)
	{
		cpids[i] = fork();
		if (cpids[i] == 0)
			execute_in_child(data, data->processes[i]);
		i++;
	}
	i = 0;
	while (i < prcs_count)
	{
		waitpid(cpids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus) == 1)
		data->exit_status = WEXITSTATUS(wstatus);
}
