/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:57:52 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 17:35:45 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	split_env(t_data *data, char *envp_str)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp_str[i] != '=')
		i++;
	key = ft_substr(envp_str, 0, i);
	value = ft_strdup(&envp_str[i + 1]);
	append_stack(&data->env, new_node(key, value));
}

void	parse_env(t_data *data, char **envp)
{
	while (*envp)
	{
		split_env(data, *envp);
		envp++;
	}
}
