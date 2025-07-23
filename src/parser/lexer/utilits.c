/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:20:42 by cbitca            #+#    #+#             */
/*   Updated: 2025/06/18 16:20:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_operator(t_lexer *lex)
{
	if (lex->line[lex->pos] == ' ')
		return (1);
	else if (lex->line[lex->pos] == '&')
		return (1);
	else if (lex->line[lex->pos] == '|')
		return (1);
	else if (lex->line[lex->pos] == '>')
		return (1);
	else if (lex->line[lex->pos] == '<')
		return (1);
	else if (lex->line[lex->pos] == 39 || lex->line[lex->pos] == '"')
		return (1);
	else if (lex->line[lex->pos] == '$')
		return (1);
	return (0);
}

void	append_redir(t_lexer *lex)
{
	if (lex->line[lex->pos] == '>')
	{
		if (lex->line[lex->pos + 1] == '>')
		{
			append_token(&lex->first, new_token(">>", REDIR_APPEND));
			lex->pos++;
		}
		else
			append_token(&lex->first, new_token(">", REDIR_OUT));
	}
	else if (lex->line[lex->pos] == '<')
	{
		if (lex->line[lex->pos + 1] == '<')
		{
			append_token(&lex->first, new_token("<<", REDIR_HEREDOC));
			lex->pos++;
		}
		else
			append_token(&lex->first, new_token("<", REDIR_IN));
	}
}

void	append_quote(t_lexer *lex)
{
	char	*s;
	char	quote;

	lex->start = lex->pos;
	quote = lex->line[lex->pos];
	lex->pos++;
	while (lex->pos < lex->size && lex->line[lex->pos] != quote)
		lex->pos++;
	s = ft_substr(lex->line, lex->start, lex->pos - lex->start + 1);
	if (!ft_strchr(&lex->line[lex->start + 1], quote))
		append_token(&lex->first, new_token(s, OPEN_QUATE));
	else if (quote == 39)
		append_token(&lex->first, new_token(s, S_QUATE));
	else if (quote == '"')
		append_token(&lex->first, new_token(s, D_QUATE));
}

void	append_var(t_lexer *lex)
{
	char	*s;

	lex->start = lex->pos;
	lex->pos++;
	while (lex->pos < lex->size && !is_operator(lex)
		&& lex->line[lex->pos] != ' ' && lex->line[lex->pos] != '?')
		lex->pos++;
	s = ft_substr(lex->line, lex->start, lex->pos - lex->start + 1);
	append_token(&lex->first, new_token(s, VAR));
}

void	append_option(t_lexer *lex)
{
	char	*s;

	lex->start = lex->pos;
	while (lex->pos < lex->size && !is_operator(lex) 
		&& lex->line[lex->pos] != ' ')
		lex->pos++;
	s = ft_substr(lex->line, lex->start, lex->pos - lex->start + 1);
	append_token(&lex->first, new_token(s, OPTION));
}