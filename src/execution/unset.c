/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:52:56 by skirwan           #+#    #+#             */
/*   Updated: 2025/06/30 12:58:33 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execution.h"
#include "env.h"

void	unset_search(t_env_var *node, char *find)
{
	t_env_var	*temp;

	while (node->next != NULL)
	{
		if (!ft_strncmp(node->next->key, find, ft_strlen(node->next->key)))
		{
			temp = node->next;
			free(temp->key), free(temp->value);
			node->next = temp->next;
			free(temp);
			return ;
		}
		node = node->next;
	}
	return ;
}

void	unset(t_data *data, char **args)
{
	t_env_var	*env_node;

	env_node = data->env;
	if (*args == NULL)
		return ;
	while (*args)
	{
		if (!ft_strncmp(env_node->key, *args, ft_strlen(env_node->key)))
		{
			(free(env_node->key), free(env_node->value));
			data->env = env_node->next;
			free(env_node);
		}
		else
			unset_search(data->env, *args);
		args++;
	}
}
