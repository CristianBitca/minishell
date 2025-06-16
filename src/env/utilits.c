/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:41:40 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/09 19:41:41 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*stack_last(t_env_var *first)
{
	t_env_var	*node;

	node = first;
	if (!node)
		return (0);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_env_var	*new_node(char *key, char *value)
{
	t_env_var	*node;

	node = ft_calloc(sizeof(t_env_var), 1);
	if (!node)
		return (0);
	node->key = key;
	node->value = value;
	return (node);
}

void	append_stack(t_env_var **node_lst, t_env_var *new)
{
	t_env_var	*temp;

	if (node_lst)
	{
		if (*node_lst)
		{
			temp = stack_last(*node_lst);
			temp->next = new;
		}
		else
			*node_lst = new;
	}
}

char	*find_env(t_env_var *node, char *find)
{
	while (node)
	{
		if (!ft_strncmp(node->key, find, ft_strlen(node->key)))
			return (node->value);
		node = node->next;
	}
	return (0);
}