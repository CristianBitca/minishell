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

// when cd is called with no args, directory is changed to home directory
// if HOME is not present in the env, find_env returns NULL and 'cd' throws and error
void	cd_home(t_data *data)
{
	char	*home_dir;

	home_dir = find_env(data->env, "HOME");
	if (home_dir == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
		return ;
	}
	if (access(home_dir, F_OK) == 0)
	{
		if (chdir(home_dir) != 0)
		{
			perror(NULL);
			data->exit_status = 1;
		}
	}
	else
	{
		write(2, "cd: ", 4);
		write(2, home_dir, ft_strlen(home_dir));
		write(2, ": No such file or directory\n", 28);
	}
}

// chdir called on path to cd, if chdir unsuccessful errno is set to corresponding
// error and perror errmsg
void	cd(t_data *data, char *path)
{
	if (path == NULL)
		cd_home(data);
	else
	{
		if (chdir(path) != 0)
		{
			perror(NULL);
			data->exit_status = 1;
		}
	}
}
