/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:57:52 by cbitca            #+#    #+#             */
/*   Updated: 2025/08/11 13:47:22 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env_var *token)
{
	t_env_var	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

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
	node->next = NULL;
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

void	parse_env(t_data *data, char **envp)
{
	char	*key;
	char	*value;
	int		i;

	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '=')
			i++;
		key = ft_substr(*envp, 0, i);
		value = ft_strdup(&((*envp)[i]));
		append_stack(&data->env, new_node(key, value));
		envp++;
	}
}
