/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:02:53 by skirwan           #+#    #+#             */
/*   Updated: 2025/07/29 15:26:50 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env.h"
#include "built_in.h"

// checks if the given dest exists in the file system using access
// if not found throws an error, file not found.
// If file exists, check if OLDPWD exists in environment to update
// it to the directory which we left from. If chdir returns != 0
// the dest was not a valid directory, so we throw an error.
// exit status is set to 1, mimicing bash, rather than a specific error code.
void	change_directory(t_data *data, char *dest)
{
	t_env_var	*old_pwd_var;
	char		*current_wd;

	current_wd = NULL;
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
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, dest, ft_strlen(dest));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
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
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
		return ;
	}
	change_directory(data, home_dir);
}

// when cd is called with '-', directory is changed to the last directory
// which is stored in the OLDPWD env variable, if OLDPWD is not present,
// the env_node is not found and 'cd -' thorws an error. After changing
// the directory, we print the cwd, mimicing bash
void	cd_oldpwd(t_data *data)
{
	t_env_var	*old_pwd_var;
	char		*current_wd;

	old_pwd_var = find_env_node(data->env, "OLDPWD");
	if (old_pwd_var == NULL)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		return ;
	}
	change_directory(data, old_pwd_var->value);
	current_wd = getcwd(NULL, 0);
	write(1, current_wd, ft_strlen(current_wd));
	write(1, "\n", 1);
}

// chdir called on path to cd
void	cd(t_data *data, char **argv)
{
	char	*path;
	int		i;

	i = 0;
	path = argv[1];
	while (argv[i++]);
	if (i > 2)
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
	if (path == NULL)
		cd_home(data);
	else if (ft_strncmp(path, "-", 2) == 0)
		cd_oldpwd(data);
	else
		change_directory(data, path);
}
