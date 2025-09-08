/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:33:13 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/03 12:49:51 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// check_built_in.c
int		is_built_in(char *cmd);
int		execute_built_in(t_data *data, t_prcs *process);

// child_process.c
void	child_prcs_file_handling(t_data *data, t_prcs *process);
void	child_prcs_check_exe(t_data *data, t_prcs *process);
int		execute_in_child(t_data *data, t_prcs *process);

// single_command.c
int		single_cmd(t_data *data, t_prcs *process);

// multiple_commands.c
void	wait_on_processes(t_data *data, int *cpids, int prcs_count);
int		execute_all_processes(t_data *data, int prcs_count);


#endif
