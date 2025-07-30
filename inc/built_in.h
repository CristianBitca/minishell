/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:54:55 by skirwan           #+#    #+#             */
/*   Updated: 2025/07/29 15:27:03 by skirwan          ###   ########.fr       */
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
void	change_directory(t_data *data, char *dest);
void	cd_home(t_data *data);
void	cd_oldpwd(t_data *data);
void	cd(t_data *data, char **argv);

//unset.c
void	unset_search(t_env_var *node, char *find);
void	unset(t_data *data, char **args);

//export.c
void	print_export(t_data *data, int out_fd);
void	export_without_value(t_data *data, char *to_export);
void	export_with_value(t_data *data, char *to_export);
int		check_valid_export(char *to_export);
void	export(t_data *data, char **args, int out_fd);

//pwd.c
void	pwd(int out_fd);

//echo.c
int		check_n(char *str);
void	echo(char **args, int out_fd);

#endif
