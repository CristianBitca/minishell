/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:28 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 15:51:29 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(t_tokentype type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (0);
	token->type = type;
	token->value = ft_strdup("");
	return (token);
}

void	append_token(t_token **tokens, t_token *new)
{
	t_token	*temp;

	if (tokens)
	{
		if (*tokens)
		{
			temp = tokens_last(*tokens);
			temp->next = new;
			new->prev = temp;
		}
		else
			*tokens = new;
	}
}

t_token	*tokens_last(t_token *first)
{
	t_token	*token;

	token = first;
	if (!token)
		return (0);
	while (token->next != NULL)
		token = token->next;
	return (token);
}