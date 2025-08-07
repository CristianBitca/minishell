/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:45:53 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/07 15:34:43 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_token	*create_token(char *value, t_tokentype type)
{
	t_token	*new_token;

	new_token = ft_calloc(sizeof(*new_token), 1);
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

t_token	*last_token(t_token *first_token)
{
	t_token	*list_node;

	list_node = first_token;
	if (list_node == NULL)
		return (NULL);
	while (list_node->next != NULL)
		list_node = list_node->next;
	return (list_node);
}

void	add_token_back(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (token_list)
	{
		if (*token_list)
		{
			temp = last_token(*token_list);
			temp->next = new_token;
			new_token->prev = temp;
		}
	}
}
