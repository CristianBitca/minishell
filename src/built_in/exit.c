/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:09:46 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/10 12:03:59 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "minishell.h"
#include <readline/readline.h>

// Completely exits the shell, freeing all allocated memory. We save
// the exit status in an int on the stack because we need to free
// the data structure itself before we can exit.
// We pass an exit status as a parameter to save lines of code in other
// functions (for norm), but if we want to exit with the exit_status saved
// in our data structure already, we just pass -1 as the exit_status.
void	full_exit(t_data *data, int exit_status)
{

	if (exit_status == -1)
		exit_status = data->exit_status;
	cleanup_tokens(data);
	cleanup_processes(data);
	cleanup_env(data);
	free(data);
	rl_clear_history();
	exit(exit_status);
}
