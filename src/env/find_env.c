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
	t_env_var	*node;

	node = env_list;
	while (node)
	{
		if (!ft_strncmp(node->key, key_to_find, ft_strlen(node->key) + 1))
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

t_env_var	*find_env_node(t_env_var *env_list, char *key_to_find)
{
	t_env_var	*node;

	node = env_list;
	while (node)
	{
		if (!ft_strncmp(node->key, key_to_find, ft_strlen(node->key) + 1))
			return (node);
		node = node->next;
	}
	return (NULL);
}
