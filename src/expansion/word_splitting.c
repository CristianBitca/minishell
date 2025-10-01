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

char	*split_word(t_data *data, t_token *token, t_expand *exp, char *input)
{
	t_token	*buffer;
	char	**split_tokens;
	char	*new_word;
	int		i;

	split_tokens = ft_split(input, ' ');
	buffer = NULL;
	i = 0;
	while (split_tokens[i])
	{
		add_token_back(&buffer, create_token(split_tokens[i], WORD));
		i++;
	}
	new_word = buffer->value;
	exp->pos = 0;
	token->type = DELETE;
	free(token->value);
	insert_tokens(data, token, buffer);
	free(split_tokens);
	free(input);
	if (exp->after)
		(free(exp->after), exp->l_after = 0);
	if (exp->before)
		(free(exp->before), exp->l_before = 0);
	return (new_word);
}
