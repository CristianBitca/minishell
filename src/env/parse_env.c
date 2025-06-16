/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:57:52 by cbitca            #+#    #+#             */
/*   Updated: 2025/05/20 18:57:53 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	split_env(t_env_var *env, char *env_value)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env_value[i] != '=')
		i++;
	key = ft_substr(env_value, 0, i);
	value = ft_strdup(&env_value[i + 1]);
	append_stack(&env, new_node(key, value));
}

t_env_var	*parse_env(t_env_var *env, char **env_var)
{
	env = ft_calloc(sizeof(t_env_var), 1);
	if (!env)
		perror("Error:");
	while (*env_var)
	{
		split_env(env, *env_var);
		env_var++;
	}
	return (env);
}
