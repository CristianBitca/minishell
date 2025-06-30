/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:54:55 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/30 16:09:09 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// print_env.c
char	**make_envp(t_data *data);
char	**join_key_val(char	**envp, t_env_var *env);
int		evar_size(t_env_var *env);
void	free_envp(char	**envp);
void	print_envp(t_data *data);

//unset.c
void	unset_search(t_env_var *node, char *find);
void	unset(t_data *data, char **args);

//export.c
void	print_export(t_data *data);
int		find_equality(char	*str);
void	export(t_data *data, char **args);

//pwd.c
void	pwd(void);

#endif
