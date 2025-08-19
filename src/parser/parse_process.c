/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:23:23 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/19 14:17:17 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	assign_prcs(t_data *data, t_token *first, int token_count, int prcs_index)
{
	t_prcs	*process;

	data->processes[prcs_index] = malloc(sizeof(*data->processes[prcs_index]));
	process = data->processes[prcs_index];
	
	process->infilefd = open_infiles(first, token_count);
}
