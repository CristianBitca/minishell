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
	t_token	*cur;

	cur = node;
	if (node->prev)
	{
		tokens->prev = node->prev;
		node->prev->next = tokens;
	}
	else
		data->tokens = tokens;
	if (cur->next)
	{
		tokens = last_token(tokens);
		cur->next->prev = tokens;
		tokens->next = cur->next;
	}
}

char	*remove_quote(char *input)
{
	char *temp;

	if (input[0] == '\'' || input[0] == '"')
	{
		temp = input;
		input = ft_substr(input, 1, ft_strlen(input) - 2);
		free(temp);
	}
	return(input);
}

t_token	*fill_buffer(t_expand *exp, char *input, char **split, t_token *buf)
{
	char	*temp;
	int		i;

	i = 0;
	if (input[0] == ' ' && ft_strlen(exp->before))
		add_token_back(&buf, create_token(ft_strdup(exp->before), WORD));
	else if (ft_strlen(exp->before))
	{
		temp = split[0];
		split[0] = ft_strjoin(exp->before, split[0]);
		free(temp);
	}
	while (split[i])
		add_token_back(&buf, create_token(split[i++], WORD));
	i = 0;
	exp->after = remove_quote(exp->after);	
	if (input[ft_strlen(input) - 1] == ' ' && ft_strlen(exp->after))
		add_token_back(&buf, create_token(ft_strdup(exp->after), WORD));
	else if (ft_strlen(exp->after))
	{
		temp = last_token(buf)->value;
		last_token(buf)->value = ft_strjoin(last_token(buf)->value, exp->after);
		free(temp);
	}
	return (buf);
}

char	*split_word(t_data *data, t_token *token, t_expand *exp, char *input)
{
	t_token	*buffer;
	char	**split_tokens;
	char	*new_word;

	split_tokens = ft_split(input, ' ');
	buffer = NULL;
	buffer = fill_buffer(exp, input, split_tokens, buffer);
	new_word = buffer->value;
	exp->pos = ft_strlen(new_word);
	token->type = DELETE;
	free(token->value);
	insert_tokens(data, token, buffer);
	(free(split_tokens), free(input));
	if (exp->after)
		(free(exp->after), exp->l_after = 0);
	if (exp->before)
		(free(exp->before), exp->l_before = 0);
	return (new_word);
}
