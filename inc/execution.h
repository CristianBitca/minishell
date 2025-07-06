/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:54:55 by skirwan           #+#    #+#             */
/*   Updated: 2025/07/06 15:43:39 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// print_env.c
int		evar_size(t_env_var *env);
char	**join_key_val(char	**envp, t_env_var *env);
char	**make_envp(t_data *data);
void	free_envp(char	**envp);
void	print_envp(t_data *data);

// cd.c
void	change_directory(t_data *data, char *dest);
void	cd_home(t_data *data);
void	cd_oldpwd(t_data *data);
void	cd(t_data *data, char *path);

//unset.c
void	unset_search(t_env_var *node, char *find);
void	unset(t_data *data, char **args);

//export.c
void	print_export(t_data *data);
int		find_equality(char	*str);
void	export_without_value(t_data *data, char *to_export);
void	export_with_value(t_data *data, char *to_export);
void	export(t_data *data, char **args);

//pwd.c
void	pwd(void);

//echo.c
int		check_n(char *str);
void	echo(char **args);

#endif
