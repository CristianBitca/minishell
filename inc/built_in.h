/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:54:55 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/10 12:03:44 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

// print_env.c
int		evar_size(t_env_var *env);
char	**join_key_val(char	**envp, t_env_var *env);
char	**make_envp(t_data *data);
void	free_envp(char	**envp);
void	print_envp(t_data *data, int out_fd);

// cd.c
void	invalid_cd(t_data *data, char *dest);
void	change_directory(t_data *data, char *dest);
void	cd_home(t_data *data);
void	cd_oldpwd(t_data *data, int out_fd);
void	cd(t_data *data, char **argv, int out_fd);

//unset.c
void	unset_search(t_env_var *node, char *find);
void	unset(t_data *data, char **args);

//export.c
void	print_export(t_data *data, int out_fd);
void	export_without_value(t_data *data, char *to_export);
void	export_with_value(t_data *data, char *to_export);
int		check_valid_export(t_data *data, char *to_export);
void	export(t_data *data, char **args, int out_fd);

//export_utils.c
void	invalid_export_identifier(t_data *data, char *to_export);

//pwd.c
void	pwd(t_data *data, int out_fd);

//echo.c
int		check_n(char *str);
void	echo(t_data *data, char **args, int out_fd);

//cleanup.c
void	cleanup_tokens(t_data *data);
void	cleanup_heredoc(t_data *data, int prcs_index);
void	cleanup_argv(t_prcs *process);
void	cleanup_processes(t_data *data);
void	cleanup_env(t_data *data);

//exit.c
void	full_exit(t_data *data);

#endif
