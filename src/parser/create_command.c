/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 09:57:29 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/12 11:57:36 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "minishell.h"
#include "parser.h"

int	check_valid_file(char *cmd)
{
	struct stat	file_status;

	if (access(cmd, F_OK) == 0)
	{
		if (stat(cmd, &file_status) == -1)
		{
			perror(cmd);
			return (-1);
		}
		if (file_status.st_mode & S_IFDIR)
		{
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": Is a directory\n", 18);
			return (-1);
		}
		if (access(cmd, X_OK) == 0)
			return (0);
		write (STDERR_FILENO, cmd, ft_strlen(cmd));
		write (STDERR_FILENO, ": Permission denied\n", 21);
		return (-1);
	}
	return (0);
}

int	check_exe_creation(t_data *data, char *cmd)
{
	char	**paths;
	char	*path;

	if (access(cmd, F_OK | X_OK) == 0 || is_built_in(cmd) == 1)
		return (0);
	path = find_env(data->env, "PATH");
	if (path == NULL)
		return (0);
	paths = ft_split(path, ':');
	if (is_cmd_in_path(paths, cmd) == 0)
	{
		free_paths(&paths);
		return (0);
	}
	free_paths(&paths);
	return (1);
}

char	*create_command(t_data *data, char *cmd)
{
	char	**paths;
	char	*path;
	char	*exe;

	path = find_env(data->env, "PATH");
	paths = ft_split(path, ':');
	exe = create_exe_in_path(paths, cmd);
	free_paths(&paths);
	return (exe);
}
