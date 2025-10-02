/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:09:46 by skirwan           #+#    #+#             */
/*   Updated: 2025/10/02 19:30:05 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "minishell.h"
#include <unistd.h>

void	check_numeric_argument(t_data *data, char *argument)
{
	int	i;
	
	i = 0;
	if (argument[i] == '+' || argument[i] == '-')
		i++;
	while (ft_isdigit(argument[i]))
		i++;
	if (argument[i] != '\0' || (argument[i] == '\0' && i == 0))
	{
		write(STDERR_FILENO, "exit: ", 6);
		write(STDERR_FILENO, argument, ft_strlen(argument));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
		full_exit(data, 2);
	}
}

void	execute_exit(t_data *data, t_prcs *process)
{
	int	i;

	i = 0;
	while (process->argv[i] != NULL)
		i++;
	if (i == 1)
		full_exit(data, -4242);
	check_numeric_argument(data, process->argv[1]);
	if (i > 2)
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 26);
		data->exit_status = 1;
	}
	else
		full_exit(data, (ft_atoi(process->argv[1]) % 256));
}

// Completely exits the shell, freeing all allocated memory. We save
// the exit status in an int on the stack because we need to free
// the data structure itself before we can exit.
// We pass an exit status as a parameter to save lines of code in other
// functions (for norm), but if we want to exit with the exit_status saved
// in our data structure already, we just pass -1 as the exit_status.
void	full_exit(t_data *data, int exit_status)
{
	if (exit_status == -4242)
		exit_status = data->exit_status;
	cleanup_tokens(data);
	cleanup_processes(data);
	cleanup_env(data);
	free(data);
	rl_clear_history();
	exit(exit_status);
}
