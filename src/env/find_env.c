/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:46:18 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/11 13:47:26 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_env_var *env_list, char *key_to_find)
{
	t_env_var	*env_node;

	env_node = env_list;
	while (env_node)
	{
		if (!ft_strncmp(env_node->key, key_to_find, ft_strlen(env_node->key) + 1))
			return (env_node->value);
		env_node = env_node->next;
	}
	return (NULL);
}

t_env_var	*find_env_node(t_env_var *env_list, char *key_to_find)
{
	t_env_var	*env_node;

	env_node = env_list;
	while (env_node)
	{
		if (!ft_strncmp(env_node->key, key_to_find, ft_strlen(env_node->key) + 1))
			return (env_node);
		env_node = env_node->next;
	}
	return (NULL);
}
