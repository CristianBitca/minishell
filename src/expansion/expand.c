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
#include "lexer.h"

void	free_exp_value(t_expand *exp)
{
	if (exp->expand)
		(free(exp->expand), exp->l_expand = 0);
	if (exp->after)
		(free(exp->after), exp->l_after = 0);
	if (exp->before)
		(free(exp->before), exp->l_before = 0);
}

void	check_exp_value(t_expand *exp)
{
	if (!exp->expand)
		(free(exp->expand), exp->l_expand = 0);
	if (!exp->after)
		(free(exp->after), exp->l_after = 0);
	if (!exp->before)
		(free(exp->before), exp->l_before = 0);
}

void	split_expand(char *input, t_expand *exp)
{
	exp->start = exp->pos++;
	while (input[exp->start] == '$' && input[exp->pos]
		&& input[exp->pos] != '$' && (ft_isalnum(input[exp->pos])
			|| input[exp->pos] == '_' || input[exp->pos] == '?'))
		exp->pos++;
	while (input[exp->start] == '\''
		&& input[exp->pos] != '\'' && input[exp->pos])
		exp->pos++;
	while (input[exp->start] == '"'
		&& input[exp->pos] != '"' && input[exp->pos])
		exp->pos++;
	if (input[exp->start] == '\'' || input[exp->start] == '"')
		exp->pos++;
	check_exp_value(exp);
	exp->l_expand = exp->pos - exp->start;
	exp->expand = ft_substr(&input[exp->start], 0, exp->l_expand);
	exp->l_after = ft_strlen(&input[exp->pos]);
	exp->after = ft_substr(input, exp->pos, exp->l_after);
	exp->l_before = exp->size - exp->l_after - exp->l_expand;
	exp->before = ft_substr(input, 0, exp->l_before);
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
			split_expand(token->value, exp);
			token->value = expand_env(data, token, exp);
		}
		else if (token->value[exp->pos] == '\'')
		{
			split_expand(token->value, exp);
			token->value = expand_s_quote(token, exp);
		}
		else if (token->value[exp->pos] == '"')
		{
			split_expand(token->value, exp);
			token->value = expand_d_quote(data, token, exp);
		}
		else
			exp->pos++;
	}
	free(exp);
}

void	expand(t_data *data)
{
	t_token	*token;
	t_token	*temp;

	token = data->tokens;
	while (token)
	{
		if (token->type == WORD
			&& (token->prev == NULL || token->prev->type != REDIR_HEREDOC))
			find_expansions(data, token);
		if (token->type == DELETE)
		{
			temp = token;
			token = data->tokens;
			if (!temp->value)
				free(temp->value);
			free(temp);
		}
		token = token->next;
	}
}
