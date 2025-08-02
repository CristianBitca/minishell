/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:33:13 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/02 16:35:56 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// check_built_in.c
int		is_built_in(t_prcs *process);
int		execute_built_in(t_data *data, t_prcs *process);

// child_process.c
void	execute_in_child(t_data *data, t_prcs *process);

// single_command.c
void	single_cmd(t_data *data, t_prcs *process);

#endif
