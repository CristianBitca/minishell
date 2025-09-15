/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:49:10 by skirwan           #+#    #+#             */
/*   Updated: 2025/09/12 11:54:22 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_cmd_in_path(char **paths, char *cmd)
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
		{
			free(exe);
			return (1);
		}
		free(exe);
		i++;
	}
	return (0);
}

void	free_paths(char ***paths_adr)
{
	char	**paths;
	int		i;

	paths = *paths_adr;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*create_exe_in_path(char **paths, char *cmd)
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
