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

#include "minishell.h"
#include "built_in.h"

// looks for argument passed to unset in our env linked list,
// has to look for the key in the next node so we can change the '->next'
// pointer to the '->next->next' and preserve the connections of
// the linked list
void	unset_search(t_env_var *node, char *find)
{
	t_env_var	*temp;

	while (node->next != NULL)
	{
		if (!ft_strncmp(node->next->key, find, ft_strlen(node->next->key)))
		{
			temp = node->next;
			(free(temp->key), free(temp->value));
			node->next = temp->next;
			free(temp);
			return ;
		}
		node = node->next;
	}
	return ;
}

// If the argument passed to unset is the very first key in our env list,
// change the head of the list to the next node, and free the node unset
void	unset(t_data *data, char **args)
{
	t_env_var	*env_node;

	env_node = data->env;
	if (*args == NULL)
		return ;
	while (*args)
	{
		if (*args[0] == '-')
		{
			write(2, "unset: minishell does not accept options\n", 42);
			data->exit_status = 2;
			args++;
			continue ;
		}
		if (!ft_strncmp(env_node->key, *args, ft_strlen(env_node->key)))
		{
			(free(env_node->key), free(env_node->value));
			data->env = env_node->next;
			free(env_node);
		}
		else
			unset_search(data->env, *args);
		args++;
		data->exit_status = EXIT_SUCCESS;
	}
}
