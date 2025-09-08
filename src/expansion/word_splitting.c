/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:37:05 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/11 15:58:44 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "minishell.h"
#include "expansion.h"

void	insert_tokens(t_data *data, t_token *node, t_token *tokens)
{
	if (node->prev)
	{
		tokens->prev = node->prev;
		node->prev->next = tokens;
	}
	else
		data->tokens = tokens;
	if (node->next)
	{
		tokens = last_token(tokens);
		node->next->prev = tokens;
		tokens->next = node->next;
	}
}

void	split_word(t_data *data, t_token *token, char *input)
{
	t_token	*buffer;
	char	**split_tokens;

	buffer = ft_calloc(sizeof(*buffer), 1);
	split_tokens = ft_split(input, ' ');
	while (*split_tokens)
	{
		add_token_back(&buffer, create_token(*split_tokens, WORD));
		split_tokens++;
	}
	insert_tokens(data, token, buffer->next);
	expand(data);
}
