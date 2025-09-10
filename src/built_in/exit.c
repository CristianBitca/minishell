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
#include <stdlib.h>

void	full_exit(t_data *data)
{
	int	exit_status;

	exit_status = data->exit_status;
	cleanup_tokens(data);
	cleanup_processes(data);
	cleanup_env(data);
	free(data);
	exit(exit_status);
}
