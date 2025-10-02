/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:04:09 by skirwan           #+#    #+#             */
/*   Updated: 2025/10/02 19:09:48 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "built_in.h"

void	update_environment_after_cd(t_data *data, char *old_wd)
{
	t_env_var	*old_pwd_var;
	t_env_var	*pwd_var;
	char		*new_wd;

	if (old_wd != NULL)
	{
		old_pwd_var = find_env_node(data->env, "OLDPWD");
		free(old_pwd_var->value);
		old_pwd_var->value = old_wd;
	}
	pwd_var = find_env_node(data->env, "PWD");
	if (pwd_var != NULL)
	{
		free(pwd_var->value);
		new_wd = getcwd(NULL, 0);
		pwd_var->value = new_wd;
	}
}
