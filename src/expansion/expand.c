/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:15:34 by skirwan           #+#    #+#             */
/*   Updated: 2025/08/19 15:05:35 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

void	split_expand(t_token *token, t_expand *exp)
{
	int	after_len;
	int	comb_len;

	exp->start = exp->pos;
	if (token->value[exp->start] == '$')
		while (token->value[exp->pos] != ' ' && token->value[exp->pos]
			&& token->value[exp->pos] != '\'' && token->value[exp->pos] != '"')
			exp->pos++;
	else if (token->value[exp->start] == '\'')
		while (token->value[exp->pos] != '\'')
			exp->pos++;
	else if (token->value[exp->start] == '"')
		while (token->value[exp->pos] != '"')
			exp->pos++;
	after_len = ft_strlen(&token->value[exp->pos]);
	comb_len = ft_strlen(&token->value[exp->start]);
	exp->expand = ft_substr(token->value, exp->start, exp->pos - exp->start);
	exp->after = ft_substr(token->value, exp->pos, after_len);
	exp->before = ft_substr(token->value, 0, exp->size - comb_len);
	printf("------------------------\n");
	printf("ONe by one: %s: \n", exp->after);
	printf("ONe by one: %s: \n", exp->before);
	printf("ONe by one: %s: \n", exp->expand);
	printf("------------------------\n");
}

void	find_expansions(t_data *data, t_token *token)
{
	t_expand	*exp;

	exp = ft_calloc(sizeof(t_expand), 1);
	exp->size = ft_strlen(token->value);
	while (token->value[exp->pos])
	{
		if (token->value[exp->pos] == '$' && token->value[exp->pos + 1])
		{
			if (token->prev == NULL || token->prev->type != REDIR_HEREDOC)
			{
				split_expand(token, exp);
				expand_env(data, token, exp);
			}
		}
		else if (token->value[exp->pos] == '\'')
		{
			split_expand(token, exp);
			// expand_s_quote(token, exp);
		}
		else
			exp->pos++;
		// else if (word[i] == '"')
		// 	i = -1; //expand dbl
		// else if (word[i] == '\'')
		// {
		// 	expand_s_quote(token, &word[i]);
		// 	word = token->value;
		// }
	}
	(void)data;
}

void	expand(t_data *data)
{
	t_token	*token_node;

	token_node = data->tokens;
	while (token_node)
	{
		if (token_node->type == WORD)
			find_expansions(data, token_node);
		token_node = token_node->next;
	}
}
