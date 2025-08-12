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
#include "minishell.h"
#include <stdlib.h>

void	insert_token(t_token *node, char *value)
{
	t_token	*new_token;

	new_token = create_token(value, WORD);
	node->next = new_token;
	new_token->prev = node;
}

void	tok_branch(t_token *node, char **expansion, char *post_expand, int join_back)
{
	t_token	*post_branch;
	char	*temp;

	post_branch = node->next;
	while (*expansion)
	{
		insert_token(node, *expansion);
		expansion++;
		node = node->next;
	}
	if (join_back == 1)
	{
		temp = node->value;
		node->value = ft_strjoin(temp, post_expand);
		free(temp);
	}
	else
	{
		insert_token(node, post_expand);
		node = node->next;
	}
	node->next = post_branch;
	post_branch->prev = node;
}

void	split_word(t_token *token, char *expand_value, char *post_expand)
{
	char	**split_expansion;
	char	*temp;
	int		join_back;

	if (expand_value[ft_strlen(expand_value) - 1] == ' ')
		join_back = 1;
	split_expansion = ft_split(expand_value, ' ');
	if (expand_value[0] != ' ')
	{
		temp = token->value;
		token->value = ft_strjoin(temp, *split_expansion);
		(free(temp), free(*split_expansion));
		split_expansion++;
	}
	if (*split_expansion)
		tok_branch(token, split_expansion, post_expand, join_back);
	free(split_expansion);
}
