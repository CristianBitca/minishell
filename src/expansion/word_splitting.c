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
<<<<<<< HEAD
	if (node->prev)
=======
	t_token	*new_token;

	new_token = create_token(value, WORD);
	node->next = new_token;
	new_token->prev = node;
}

void	split_branch(t_token *node, char **expansion, char *remainder, int rmndr)
{
	t_token	*post_branch;
	char	*temp;

	post_branch = node->next;
	while (*expansion)
>>>>>>> skirwan
	{
		tokens->prev = node->prev;
		node->prev->next = tokens;
	}
<<<<<<< HEAD
=======
	if (rmndr == 1)
	{
		temp = post_branch->value;
		post_branch->value = ft_strjoin(remainder, temp);
		free(temp);
	}
	else if (remainder[0] != '\0')
	{
		insert_token(node, remainder);
		node = node->next;
	}
	node->next = post_branch;
	if (post_branch != NULL)
		post_branch->prev = node;
}

void	split_word(t_token *token, char *expand_value, char *remainder)
{
	char	**split_expansion;
	char	*temp;
	int		join_back;
	int		i;

	if (expand_value[ft_strlen(expand_value) - 1] != ' ' && token->next != NULL)
		join_back = 1;
	split_expansion = ft_split(expand_value, ' ');
	i = 0;
	if (expand_value[0] != ' ' || *token->value == '\0')
	{
		temp = token->value;
		token->value = ft_strjoin(temp, split_expansion[i]);
		(free(temp), free(split_expansion[i]));
		i++;
	}
	if (split_expansion[i])
		split_branch(token, &split_expansion[i], remainder, join_back);
>>>>>>> skirwan
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
