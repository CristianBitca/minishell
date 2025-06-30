/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:40:36 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/30 14:34:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execution.h"

int	evar_size(t_env_var *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->value != NULL)
			i++;
		env = env->next;
	}
	return (i);
}

char	**join_key_val(char	**envp, t_env_var *env)
{
	int	env_var_size;
	int	env_var;
	int	i;

	env_var = 0;
	while (env != NULL)
	{
		env_var_size = ft_strlen(env->key) + ft_strlen(env->value) + 3;
		ft_strlcpy(envp[env_var], env->key, env_var_size);
		i = ft_strlen(env->key);
		envp[env_var][i] = '=';
		i++;
		env_var_size -= i;
		ft_strlcpy(&envp[env_var][i], env->value, env_var_size);
		i += ft_strlen(env->value);
		envp[env_var][i] = '\n';
		envp[env_var][i + 1] = '\0';
		env_var++;
		env = env->next;
	}
	return (envp);
}

char	**make_envp(t_data *data)
{
	t_env_var	*env;
	char		**envp;
	int			env_var_size;
	int			i;

	envp = malloc(sizeof(*envp) * (evar_size(data->env) + 1));
	i = 0;
	env = data->env;
	while (env != NULL)
	{
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		env_var_size = ft_strlen(env->key) + ft_strlen(env->value) + 3;
		envp[i] = malloc(sizeof(*envp[i]) * env_var_size);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	join_key_val(envp, data->env);
	return (envp);
}

void	free_envp(char	**envp)
{
	char	*env_var;
	int		i;

	i = 0;
	env_var = envp[i];
	while (env_var != NULL)
	{
		free(env_var);
		i++;
		env_var = envp[i];
	}
	free(envp);
}

void	print_envp(t_data *data)
{
	char	**envp;
	int		i;

	envp = make_envp(data);
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s", envp[i]);
		i++;
	}
	free_envp(envp);
}
