/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:25:42 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/12 15:15:08 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

char	**make_envp(t_data *data);
char	**join_key_val(char	**envp, t_env_var *env);
int		evar_size(t_env_var *env);
void	free_envp(char	**envp);
void	print_envp(t_data *data);

#endif
