/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:02:53 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/30 18:34:41 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "execution.h"

void	change_directory(t_data *data, char *dest)
{
	t_env_var	*old_pwd_var;
	char		*current_wd;

	if (access(dest, F_OK) == 0)
	{
		if (find_env(data->env, "OLDPWD") != NULL)
			current_wd = getcwd(NULL, 0);
		if (chdir(dest) != 0)
		{
			(perror(NULL), free(current_wd));
			data->exit_status = 1;
			return ;
		}
		if (current_wd != NULL)
		{
			old_pwd_var = find_env_node(data->env, "OLDPWD");
			free(old_pwd_var->value);
			old_pwd_var->value = current_wd;
		}
	}
	else
	{
		write(2, "cd: ", 4);
		write(2, dest, ft_strlen(dest));
		write(2, ": No such file or directory\n", 28);
	}
}

// when cd is called with no args, directory is changed to home directory
// if HOME is not present in the env, find_env returns NULL and 'cd' throws an error
void	cd_home(t_data *data)
{
	char		*home_dir;

	home_dir = find_env(data->env, "HOME");
	if (home_dir == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
		return ;
	}
	change_directory(data, home_dir);
}

// when cd is called with '-', directory is changed to the last directory
// which is stored in the OLDPWD env variable, if OLDPWD is not present,
// the env_node is not found and 'cd -' thorws an error
void	cd_oldpwd(t_data *data)
{
	t_env_var	*old_pwd_var;
	char		*current_wd;

	old_pwd_var = find_env_node(data->env, "OLDPWD");
	if (old_pwd_var == NULL)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		return ;
	}
	change_directory(data, old_pwd_var->value);
	current_wd = getcwd(NULL, 0);
	write(1, current_wd, ft_strlen(current_wd));
	write(1, "\n", 1);
}

// chdir called on path to cd
void	cd(t_data *data, char *path)
{
	if (path == NULL)
		cd_home(data);
	else if (ft_strncmp(path, "-", 2) == 0)
		cd_oldpwd(data);
	else
		change_directory(data, path);
}
