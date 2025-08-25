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

void	free_exp(t_expand *exp)
{
	if (!exp)
	{
		if (!exp->after)
			free(exp->after);
		if (!exp->before)
			free(exp->before);
		if (!exp->expand)
			free(exp->expand);
		free(exp);
	}
}

void	split_expand(t_token *tok, t_expand *exp)
{
	exp->start = exp->pos++;
	while (tok->value[exp->start] == '$' && tok->value[exp->pos]
		&& tok->value[exp->pos] != '$' && (ft_isalnum(tok->value[exp->pos])
			|| tok->value[exp->pos] == '_' || tok->value[exp->pos] == '?'))
		exp->pos++;
	while (tok->value[exp->start] == '\''
		&& tok->value[exp->pos] != '\'' && tok->value[exp->pos])
		exp->pos++;
	while (tok->value[exp->start] == '"'
		&& tok->value[exp->pos] != '"' && tok->value[exp->pos])
		exp->pos++;
	if (tok->value[exp->start] == '\'' || tok->value[exp->start] == '"')
		exp->pos++;
	if (!exp->expand)
		(free(exp->expand), exp->l_expand = 0);
	exp->l_expand = exp->pos - exp->start;
	exp->expand = ft_substr(tok->value, exp->start, exp->l_expand);
	if (!exp->after)
		(free(exp->after), exp->l_after = 0);
	exp->l_after = ft_strlen(&tok->value[exp->pos]);
	exp->after = ft_substr(tok->value, exp->pos, exp->l_after);
	if (!exp->before)
		(free(exp->before), exp->l_before = 0);
	exp->l_before = exp->size - exp->l_after - exp->l_expand;
	exp->before = ft_substr(tok->value, 0, exp->l_before);
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
			split_expand(token, exp);
			expand_env(data, token, exp);
		}
		else if (token->value[exp->pos] == '\'')
		{
			split_expand(token, exp);
			expand_s_quote(token, exp);
		}
		else if (token->value[exp->pos] == '"')
		{
			split_expand(token, exp);
			expand_d_quote(token, exp);
		}
		else
			exp->pos++;
	}
	free_exp(exp);
}

void	expand(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (token->type == WORD
			&& (token->prev == NULL || token->prev->type != REDIR_HEREDOC))
			find_expansions(data, token);
		token = token->next;
	}
}
