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

void	append_word(t_lexer *lex)
{
	char	*s;

	lex->start = lex->pos;
	while (lex->pos < lex->size && !is_operator(lex)
		&& lex->line[lex->pos] != ' ')
	{
		if (lex->line[lex->pos] == '\'' || lex->line[lex->pos] == '"')
		{
			lex->pos++;
			while (lex->line[lex->pos] != '\'' && lex->line[lex->pos] != '"'
				&& lex->pos < lex->size)
				lex->pos++;
		}
		else
			lex->pos++;
	}
	s = ft_substr(lex->line, lex->start, lex->pos - lex->start);
	append_token(&lex->first, new_token(s, WORD));
}

int	append_operator(t_lexer *lex)
{
	if (lex->line[lex->pos] == '|')
		append_token(&lex->first, new_token("|", PIPE));
	else if (lex->line[lex->pos] == '>')
		append_redir(lex);
	else if (lex->line[lex->pos] == '<')
		append_redir(lex);
	else if (lex->line[lex->pos] == 39 || lex->line[lex->pos] == '"')
		append_quote(lex);
	else if (lex->line[lex->pos] == '$')
		append_var(lex);
	else if (lex->line[lex->pos] == '-')
		append_option(lex);
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
		if (append_operator(lex))
			continue ;
		else if (lex->line[lex->pos])
			append_word(lex);
		else
			break ;
	}
	append_token(&lex->first, new_token("EOF", EOF));
}
