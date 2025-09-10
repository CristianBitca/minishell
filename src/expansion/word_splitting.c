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
		tokens->prev = node;
		node->next = tokens;
	}
	else
		data->tokens = tokens;
	if (node->next)
	{
		tokens = last_token(tokens);
		node->prev = tokens;
		tokens->next = node;
	}
}

char	*split_word(t_data *data, t_token *token, char *input)
{
	t_token	*buffer;
	char	**split_tokens;
	char	*new_word;
	int	i;

	buffer = ft_calloc(sizeof(*buffer), 1);
	split_tokens = ft_split(input, ' ');
	i = 0;
	while (split_tokens[i])
	{
		add_token_back(&buffer, create_token(split_tokens[i], WORD));
		i++;
	}
	buffer = buffer->next;
	new_word = buffer->value;
	token->type = DELETE;
	insert_tokens(data, token, buffer);
	free(input);
	return(new_word);
}
