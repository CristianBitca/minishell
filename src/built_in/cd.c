/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:02:53 by skirwan           #+#    #+#             */
/*   Updated: 2025/10/02 19:11:03 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "built_in.h"

void	invalid_cd(t_data *data, char *dest)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, dest, ft_strlen(dest));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	data->exit_status = EXIT_FAILURE;
}

// checks if the given dest exists in the file system using access
// if not found throws an error, file not found.
// If file exists, check if OLDPWD exists in environment to update
// it to the directory which we left from. If chdir returns != 0
// the dest was not a valid directory, so we throw an error.
// exit status is set to 1, mimicing bash, rather than a specific error code.
void	change_directory(t_data *data, char *dest)
{
	char		*old_wd;

	old_wd = NULL;
	if (access(dest, F_OK) == 0)
	{
		if (find_env(data->env, "OLDPWD") != NULL)
			old_wd = getcwd(NULL, 0);
		if (chdir(dest) != 0)
		{
			(perror(NULL), free(old_wd));
			data->exit_status = EXIT_FAILURE;
			return ;
		}
		update_environment_after_cd(data, old_wd);
		data->exit_status = EXIT_SUCCESS;
	}
	else
		invalid_cd(data, dest);
}

// when cd is called with no args, directory is changed to home directory
// if HOME is not present in the env, find_env returns NULL
// and 'cd' throws an error
void	cd_home(t_data *data)
{
	char		*home_dir;

	home_dir = find_env(data->env, "HOME");
	if (home_dir == NULL)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
		data->exit_status = EXIT_FAILURE;
		return ;
	}
	change_directory(data, home_dir);
}

// when cd is called with '-', directory is changed to the last directory
// which is stored in the OLDPWD env variable, if OLDPWD is not present,
// the env_node is not found and 'cd -' thorws an error. After changing
// the directory, we print the cwd, mimicing bash
void	cd_oldpwd(t_data *data, int out_fd)
{
	t_env_var	*old_pwd_var;
	char		*current_wd;

	old_pwd_var = find_env_node(data->env, "OLDPWD");
	if (old_pwd_var == NULL)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		data->exit_status = EXIT_FAILURE;
		return ;
	}
	change_directory(data, old_pwd_var->value);
	current_wd = getcwd(NULL, 0);
	write(out_fd, current_wd, ft_strlen(current_wd));
	write(out_fd, "\n", 1);
	free(current_wd);
}

// cd can only have one argument, if we dont have a special case
// ("cd -" or just "cd"), chdir called on path given.
void	cd(t_data *data, char **argv, int out_fd)
{
	char	*path;
	int		i;

	i = 0;
	path = argv[1];
	while (argv[i] != NULL)
		i++;
	if (i > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		data->exit_status = EXIT_FAILURE;
		return ;
	}
	if (path == NULL)
		cd_home(data);
	else if (ft_strncmp(path, "-", 2) == 0)
		cd_oldpwd(data, out_fd);
	else
		change_directory(data, path);
}
