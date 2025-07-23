/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:06:09 by cbitca            #+#    #+#             */
/*   Updated: 2025/07/14 14:06:11 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	find_word(t_lexer *lex)
{
	char	*s;

	lex->start = lex->pos;
	while (lex->pos < lex->size && !is_operator(lex))
		lex->pos++;
	s = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	append_token(&lex->first, new_token(s, WORD));
}

int	find_operator(t_lexer *lex)
{
	if (lex->line[lex->pos] == '&')
		append_token(&lex->first, new_token("&", OPERATOR));
	else if (lex->line[lex->pos] == '|')
		append_token(&lex->first, new_token("|", PIPE));
	else if (lex->line[lex->pos] == '>')
		append_token(&lex->first, new_token(">", REDIR_OUT));
	else if (lex->line[lex->pos] == '<')
		append_token(&lex->first, new_token("<", REDIR_IN));
	else if (lex->line[lex->pos] == '(')
		append_token(&lex->first, new_token("(", OPERATOR));
	else if (lex->line[lex->pos] == ')')
		append_token(&lex->first, new_token(")", OPERATOR));
	else if (lex->line[lex->pos] == ';' || lex->line[lex->pos] == '\n')
		append_token(&lex->first, new_token(">", OPERATOR));
	else if (lex->line[lex->pos] == 39 || lex->line[lex->pos] == '"')
		append_token(&lex->first, new_token("quate", OPERATOR));
	else if (lex->line[lex->pos] == '$')
		append_token(&lex->first, new_token("$", OPERATOR));
	else
		return (0);
	lex->pos++;
	return (1);
}

void	tokenize(t_lexer *lex)
{
	while (lex->pos < lex->size)
	{
		if (lex->line[lex->pos] == ' ')
			lex->pos++;
		if (find_operator(lex))
			continue ;
		else if (lex->line[lex->pos])
			find_word(lex);
		else
			break ;
	}
	append_token(&lex->first, new_token("EOF", EOF));
}
