/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 09:57:29 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/03 12:40:20 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "minishell.h"
#include "parser.h"

int		check_valid_file(char *cmd)
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

char	*search_exe_in_path(char **paths, char *cmd)
{
	char	*temp;
	char	*exe;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		exe = ft_strjoin(temp, cmd);
		free(temp);
		if (access(exe, X_OK) == 0)
			return (exe);
		free(exe);
		i++;
	}
	return (cmd);
}

char	*create_command(t_data *data, char *cmd)
{
	char	**paths;
	char	*path;
	char	*exe;

	if (check_valid_file(cmd) == -1)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0 || is_built_in(cmd) == 1)
		return (cmd);
	path = find_env(data->env, "PATH");
	if (path == NULL)
		return (cmd);
	paths = ft_split(path, ':');
	exe = search_exe_in_path(paths, cmd);
	if (ft_strncmp(exe, cmd, ft_strlen(exe) == 0))
	{
		free(exe);
		return (cmd);
	}
	return (exe);
}
